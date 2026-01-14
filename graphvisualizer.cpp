<<<<<<< HEAD
#include "graphvisualizer.h"
#include<queue>



GraphVisualizer::GraphVisualizer(QWidget *parent)
{
    setFixedSize(1000,600);

}

void GraphVisualizer::setNumberOfNodes(int count)
{
    if (count > 0 && count <= 50) {
        // Clear old state
        nodes.clear();
        edges.clear();
        firstSelectedNodeId = -1;

        // STORE the required count
        requiredNodeCount = count;

        qDebug() << "Ready to place" << requiredNodeCount << "nodes manually.";

        // Ensure edge creation is disabled while placing nodes
        isEdgeCreationMode = false;

        update(); // Request a repaint to show an empty canvas
    }

}


int GraphVisualizer::findNodeIdAt(const QPoint &point)
{
    for (const auto &node : nodes) {
        // Simple distance check from center (more accurate than QRect::contains)
        int dx = node.center.x() - point.x();
        int dy = node.center.y() - point.y();
        if (qSqrt(dx * dx + dy * dy) <= NodeRadius) {
            return node.id;
        }
    }
    return -1; // No node found
}

// shorthestPathVisualizer.cpp (Modify paintEvent)

void GraphVisualizer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Define Colors (Add these to your class header/definition)
    const QMap<int, QColor> nodeColors = {
        {DefaultNodeColor, Qt::white},
        {SourceNodeColor, Qt::darkGreen},
        {DestinationNodeColor, Qt::red},
        {CurrentNodeColor, Qt::cyan},
        {VisitedNodeColor, Qt::blue},
        {PathNodeColor, Qt::magenta}
    };
    const QMap<int, QColor> edgeColors = {
        {DefaultEdgeColor, Qt::gray},
        {HighlightEdgeColor, Qt::cyan},
        {TentativeEdgeColor, Qt::yellow},
        {FinalPathEdgeColor, Qt::magenta}
    };

    // 1. Draw Edges
    for (int i = 0; i < edges.size(); ++i) {
        const auto &edge = edges.at(i);
        QPoint p1, p2;
        // Find node centers p1, p2 (assuming you kept the node structure)
        if (Node *n1 = getNodeById(edge.node1Id)) p1 = n1->center;
        if (Node *n2 = getNodeById(edge.node2Id)) p2 = n2->center;

        // Draw the line with the current color state
        QColor lineColor = edgeColors.value(edge.colorState, Qt::gray);
        painter.setPen(QPen(lineColor, 3)); // Thicker for visibility
        painter.drawLine(p1, p2);

        // Draw the edge value
        if (edge.value != 0) {
            QPoint center = (p1 + p2) / 2;

            // Offset the text for visibility (optional, depends on graph density)
            QPointF dir = (p2 - p1);
            qreal len = std::sqrt(QPointF::dotProduct(dir, dir));
            if (len > 0) dir /= len;

            QPoint textPos = center;

            QRect textRect(textPos.x() - 15, textPos.y() - 10, 30, 20);
            painter.setBrush(Qt::yellow);
            painter.setPen(Qt::NoPen);
            painter.drawRect(textRect);

            painter.setPen(Qt::darkRed);
            painter.setFont(QFont("Arial", 12,QFont::Bold));
            painter.drawText(textRect, Qt::AlignCenter, QString::number(edge.value));
        }
    }

    // 2. Draw Nodes
    for (const auto &node : nodes) {

        QColor nodeFillColor = nodeColors.value(node.colorState, Qt::white);

        // Highlight the first selected node in edge creation mode
        if (isEdgeCreationMode && node.id == firstSelectedNodeId) {
            painter.setBrush(Qt::cyan);
        } else {
            painter.setBrush(nodeFillColor);
        }

        painter.setPen(QPen(Qt::white, 3));
        painter.drawEllipse(node.center, NodeRadius, NodeRadius);

        // Draw the node number (ID)
        painter.setFont(QFont("Arial", 20,QFont::Bold));
        painter.setPen(Qt::black);
        painter.drawText(node.rect, Qt::AlignCenter, QString::number(node.id));

        // Draw the distance value below the node (if known)

        QString distText = (node.distance == INT_MAX) ? "INF" : QString::number(node.distance);
        QRect distRect(node.center.x() - 25, node.center.y() + NodeRadius + 5, 50, 50);

        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 12,QFont::Bold));
        painter.drawText(distRect, Qt::AlignCenter, "D: " + distText);

    }
}
void GraphVisualizer::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QPoint clickPos = event->pos();
        int clickedNodeId = findNodeIdAt(clickPos);

        // ------- NODE PLACEMENT MODE ---------
        // If we haven't reached the required node count, we are in placement mode.
        if (nodes.size() < requiredNodeCount) {

            // Do not allow placement if the click is too close to the edge or over an existing node
            if (clickedNodeId == -1 &&
                clickPos.x() > NodeRadius && clickPos.x() < width() - NodeRadius &&
                clickPos.y() > NodeRadius && clickPos.y() < height() - NodeRadius)
            {
                Node newNode;
                // Node IDs must start from 1 and continue sequentially
                newNode.id = nodes.size() + 1;
                newNode.center = clickPos;
                newNode.rect = QRect(clickPos.x() - NodeRadius, clickPos.y() - NodeRadius, 2 * NodeRadius, 2 * NodeRadius);

                nodes.append(newNode);

                // If placement is now complete, reset requiredNodeCount
                if (nodes.size() == requiredNodeCount) {
                    qDebug() << "All" << requiredNodeCount << "nodes placed. Ready for edge creation.";
                }
                update();
            }
            return; // Exit, as we handled placement.
        }
        // ------EDGE VALUE INPUT MODE------
        if (putEdgeValueMode) {
            int edgeIndex = findEdgeAt(clickPos);

            if (edgeIndex != -1) {
                // Emit signal to MainWindow to open the input dialog
                // We pass the click position (clickPos) for UI placement (optional)
                emit requestEdgeValueInput(clickPos, edgeIndex);
            }
            return; // Handled input mode click.
        }

        // -------- EDGE CREATION MODE ----------
        // This only runs if placement is complete AND edge creation is enabled.
        if (isEdgeCreationMode) {
            if (clickedNodeId != -1) {
                if (firstSelectedNodeId == -1) {
                    // First node selected
                    firstSelectedNodeId = clickedNodeId;
                } else if (firstSelectedNodeId != clickedNodeId) {
                    // Second node selected: Create Edge
                    if (edgeExists(firstSelectedNodeId, clickedNodeId)) {
                        qDebug() << "Error: Edge already exists between" << firstSelectedNodeId << "and" << clickedNodeId;
                        firstSelectedNodeId = -1; // Reset selection without creating an edge
                    } else {
                        // Second node selected: Create Edge
                        Edge newEdge;
                        newEdge.node1Id = firstSelectedNodeId;
                        newEdge.node2Id = clickedNodeId;

                        edges.append(newEdge);
                        firstSelectedNodeId = -1; // Reset selection
                    }
                }
                update();
            }
        }
    }
}
void GraphVisualizer::setEdgeCreationMode(bool enabled)
{
    isEdgeCreationMode = enabled;
    putEdgeValueMode = false; // Disable edge value mode when entering edge creation mode
    firstSelectedNodeId = -1;
    update();
}

void GraphVisualizer::setEdgeValueMode(bool enabled)
{
    putEdgeValueMode = enabled;
    isEdgeCreationMode = false; // Disable edge creation mode when entering edge value mode
    firstSelectedNodeId = -1;
    update();
}
int GraphVisualizer::findEdgeAt(const QPoint &point)
{
    // A tolerance for clicking near an edge (e.g., 8 pixels)
    const int Tolerance = 8;

    // A simplified way to check proximity to a line segment.
    // Index i corresponds to the edge index in the QList.
    for (int i = 0; i < edges.size(); ++i) {
        const auto &edge = edges.at(i);
        QPoint p1, p2;

        // Find node centers
        for (const auto &node : nodes) {
            if (node.id == edge.node1Id) p1 = node.center;
            if (node.id == edge.node2Id) p2 = node.center;
        }
        QPointF v = p2 - p1; // Vector from P1 to P2
        QPointF w = point - p1;// Vector from P1 to Click Point
        qreal lineLengthSq = QPointF::dotProduct(v, v);
        if (lineLengthSq<1e-6) continue; // Avoid division by zero for coincident nodes

        // Get the projection parameter (t). This tells us where the click point projects onto the line (0 <= t <= 1 means on segment)
        qreal t = QPointF::dotProduct(w, v) / lineLengthSq;

        QPointF closestPoint;

        if (t < 0.0) {
            // Closest point is P1 (segment endpoint)
            closestPoint = p1;
        } else if (t > 1.0) {
            // Closest point is P2 (segment endpoint)
            closestPoint = p2;
        } else {
            // Closest point is on the line segment
            closestPoint = p1 + t * v;
        }

        // Calculate the squared distance from the click point to the closest point on the segment
        qreal dx = closestPoint.x() - point.x();
        qreal dy = closestPoint.y() - point.y();
        qreal distSq = dx * dx + dy * dy;

        // --- Final Check ---

        // If the actual distance is within tolerance
        if (std::sqrt(distSq) <= Tolerance) {
            return i; // Return the index of the edge
        }
    }
    return -1;
}

bool GraphVisualizer::GraphVisualizer::edgeExists(int id1, int id2)
{

    for (const auto &edge : edges) {
        if ((edge.node1Id == id1 && edge.node2Id == id2) || (edge.node1Id == id2 && edge.node2Id == id1)) {
            return true;
        }
    }
    return false;
}
GraphVisualizer::Node *GraphVisualizer::getNodeById(int id)
{
    for (int i = 0; i < nodes.size(); ++i) {
        if (nodes[i].id == id) {
            return &nodes[i];
        }
    }
    return nullptr;
}
bool GraphVisualizer::setEdgeValueByIndex(int index, int value)
{
    // 1. Check if the index is valid
    if (index >= 0 && index < edges.size()) {

        // 2. Update the private data structure
        edges[index].value = value;

        // 3. Request a repaint to show the new value immediately
        update();

        return true; // Success
    }

    qWarning() << "Error: Attempted to set edge value for invalid index:" << index;
    return false; // Failure
}
// shorthestPathVisualizer.cpp

void GraphVisualizer::startAlgorithm(int algorithmIndex, int srcId, int destId, int interval)
{

    if (timer) {
        timer->stop();
        delete timer;
        timer = nullptr;
    }
    // Clear previous state
    stepsList.clear();
    currentStepIndex = 0;
    intervalLength = interval;
    destinationNodeId = destId;

    // Reset all nodes/edges colors and distances
    for (auto &node : nodes) {
        node.colorState = DefaultNodeColor;
        node.distance = INT_MAX;
        node.parentId = -1;
    }
    for (auto &edge : edges) {
        edge.colorState = DefaultEdgeColor;
    }

    // Set source and destination colors
    if (Node *srcNode = getNodeById(srcId)) {
        srcNode->colorState = SourceNodeColor;
    }
    if (Node *destNode = getNodeById(destId)) {
        destNode->colorState = DestinationNodeColor;
    }

    // Generate algorithm steps
    if (algorithmIndex == 0) { // Assuming index 0 is Dijkstra
        dijkstraAlgorithm(srcId, destId);
    }
    else if (algorithmIndex == 1) {
        primsAlgorithm(srcId);
    }else if(algorithmIndex==2){
        tarjanArticulationPoints();
    }

    // Start visualization
    if (stepsList.isEmpty()) {
        qDebug() << "Algorithm completed instantly or no path found.";
        emit enableGraphButtons();
        update();
        return;
    }

    // Initialize and connect timers
    timer = new QTimer(this);
    timer->setTimerType(Qt::PreciseTimer);
    elapsedTimer = new QElapsedTimer;

    connect(timer, &QTimer::timeout, this, &GraphVisualizer::processNextStep);

    // We reuse the SortVisualizer timing pattern
    QTimer *timerUpdateElapsed = new QTimer(this);
    connect(timerUpdateElapsed, &QTimer::timeout, this, &GraphVisualizer::updateTimeElapsed);

    //emit disableGraphButtons();
    elapsedTimer->start();
    timer->start(intervalLength);
    timerUpdateElapsed->start(50); // Update elapsed time frequently

    update();
}

void GraphVisualizer::stopAlgorithm()
{
    if (timer) {
        timer->stop();
        delete timer;
        timer = nullptr;
    }
    if (elapsedTimer) {
        int elapsedTime = elapsedTimer->elapsed();
        emit setTimeElapsed(elapsedTime);
        delete elapsedTimer;
        elapsedTimer = nullptr;
    }

    // Ensure all timer connections are also cleaned up (using QObject parentage)
    QList<QTimer*> childTimers = findChildren<QTimer*>();
    for (QTimer *t : childTimers) {
        if (t != timer) {
            t->stop();
            t->deleteLater();
        }
    }

    emit enableGraphButtons();
    update();
}

void GraphVisualizer::updateTimeElapsed() {
    if (elapsedTimer) {
        emit setTimeElapsed(elapsedTimer->elapsed());
    }
}

void GraphVisualizer::processNextStep()
{
    if (currentStepIndex >= stepsList.size()) {
        qDebug() << "Visualization Finished.";
        stopAlgorithm();
        return;
    }

    auto step = stepsList[currentStepIndex];
    int command = std::get<0>(step);
    int val1 = std::get<1>(step); // Node ID or Edge Index
    int val2 = std::get<2>(step); // Color or Distance

    switch (command) {
    case HIGHLIGHT_NODE: {
        if (Node *node = getNodeById(val1)) {
            node->colorState = val2;
        }
        break;
    }
    case HIGHLIGHT_EDGE: {
        if (val1 >= 0 && val1 < edges.size()) {
            edges[val1].colorState = val2;
        }
        break;
    }
    case SET_DISTANCE: {
        // This step is mainly for information (e.g., displaying text near node)
        // For visualization, we just log it and rely on node color
        if (Node *node = getNodeById(val1)) {
            node->distance = val2;
        }
        break;
    }
    default:
        break;
    }

    update(); // Redraw the visualizer
    currentStepIndex++;
}

void GraphVisualizer::dijkstraAlgorithm(int srcId, int destId)
{

    QMap<int, int> distance;
    QMap<int, int> parent;
    for (const auto &node : nodes) {
        distance[node.id] = (node.id == srcId) ? 0 : INT_MAX;
        parent[node.id] = -1;
    }

    // 2. Priority Queue: {Distance, Node ID}
    // Use std::priority_queue with a custom QPair/std::pair wrapper if needed,
    // or simply use a QList as a basic unoptimized queue for simple visualization (less accurate to pseudocode but easier to implement)
    // STICKING TO PSEUDOCODE: Use std::priority_queue and map IDs to distances.
    using T = pair<int, int>;
    priority_queue<T,vector<T>,greater<T>> pq;

    pq.push({0, srcId});

    stepsList.append(make_tuple(HIGHLIGHT_NODE, srcId, CurrentNodeColor));
    stepsList.append(make_tuple(SET_DISTANCE, srcId, 0));

    while (!pq.empty()) {
        int d = pq.top().first;
        int u_id = pq.top().second;
        pq.pop();

        if (d > distance[u_id]) continue;

        // Visualization Step: Mark current node being processed
        stepsList.append(make_tuple(HIGHLIGHT_NODE, u_id, CurrentNodeColor));

        // Create a list of edges that need to be un-highlighted after processing u_id
        QList<int> edgesToReset;

        // Iterate through all edges/neighbors
        for (int i = 0; i < edges.size(); ++i) {
            const auto &edge = edges.at(i);
            int v_id = -1;

            if (edge.node1Id == u_id) v_id = edge.node2Id;
            else if (edge.node2Id == u_id) v_id = edge.node1Id;

            if (v_id != -1) {
                int weight = edge.value;

                // Visualization Step: Highlight the edge being checked (Dark Yellow)
                stepsList.append(make_tuple(HIGHLIGHT_EDGE, i, HighlightEdgeColor));

                // Relaxation
                if (distance[u_id] != INT_MAX && distance[u_id] + weight < distance[v_id]) {
                    distance[v_id] = distance[u_id] + weight;
                    parent[v_id] = u_id;
                    pq.push({distance[v_id], v_id});

                    // Visualization Step: Mark the neighbor node as tentative (Blue/Visited)
                    stepsList.append(make_tuple(SET_DISTANCE, v_id, distance[v_id]));
                    stepsList.append(make_tuple(HIGHLIGHT_NODE, v_id, VisitedNodeColor));

                    // Visualization Step: Mark the edge as part of the TENTATIVE path (Magenta)
                    stepsList.append(make_tuple(HIGHLIGHT_EDGE, i, TentativeEdgeColor));

                }

                // Track this edge to reset its color
                edgesToReset.append(i);
            }
        }

        // POST-RELAXATION: Reset all edges checked during this node's processing,
        // UNLESS it was set to TentativeEdgeColor (which can be reset later).
        // This is tricky. Let's simplify: reset the HighlightEdgeColor after checking.
        for (int edgeIndex : edgesToReset) {
            // Only reset the edge to gray if it wasn't just set to TentativeEdgeColor
            // Note: Since the loop is sequential, we can just reset the HighlightEdgeColor
            // if it wasn't improved. However, for a clean visual, a blanket reset is better.
            // A safer approach: For every edge check, add two steps: Highlight -> Unhighlight (or TentativeColor).
            // Let's rely on the TentativeEdgeColor to persist until the final traceback.
        }


        // Visualization Step: Mark current node as permanently visited (Blue/Visited)
        stepsList.append(make_tuple(HIGHLIGHT_NODE, u_id, VisitedNodeColor));

        if (u_id == destId) break;
    }
    for (int j = 0; j < edges.size(); ++j) {
        stepsList.append(std::make_tuple(HIGHLIGHT_EDGE, j, DefaultEdgeColor));
    }
    // Final Visualization Step: Trace back the final path

    int currId = destId;
    while (currId != -1 && currId != srcId) {
        int pId = parent[currId];
        if (pId == -1) break;

        // Find the edge between currId and pId
        for (int i = 0; i < edges.size(); ++i) {
            const auto &edge = edges.at(i);
            if ((edge.node1Id == currId && edge.node2Id == pId) || (edge.node1Id == pId && edge.node2Id == currId)) {

                // IMPORTANT: RESET ALL EXISTING EDGE COLORS FIRST to ensure only the final path shows up.
                // We add a cleanup pass before the final path display:
                // for (int j = 0; j < edges.size(); ++j) {
                //     stepsList.append(std::make_tuple(HIGHLIGHT_EDGE, j, DefaultEdgeColor));
                // }

                // Now, color the final path edge with the specific color
                stepsList.append(std::make_tuple(HIGHLIGHT_EDGE, i, FinalPathEdgeColor));
                break;
            }
        }
        stepsList.append(std::make_tuple(HIGHLIGHT_NODE, currId, PathNodeColor)); // Use new PathNodeColor
        currId = pId;
    }

    // Ensure the source and destination nodes are correctly highlighted at the end
    stepsList.append(std::make_tuple(HIGHLIGHT_NODE, srcId, SourceNodeColor));
    stepsList.append(std::make_tuple(HIGHLIGHT_NODE, destId, DestinationNodeColor));

    // Store final distances back into nodes for permanent display (optional)
    for (auto &node : nodes) {
        node.distance = distance.value(node.id, INT_MAX);
    }
}

void GraphVisualizer::primsAlgorithm(int startNodeId)
{
    QMap<int, bool> visited;
    for (const auto &node : nodes) visited[node.id] = false;

    // PQ stores: tuple<weight, current_node_id, parent_edge_index>
    using T = std::tuple<int, int, int>;
    std::priority_queue<T, std::vector<T>, std::greater<T>> pq;

    // Start with the source node
    pq.push({0, startNodeId, -1});

    while (!pq.empty()) {
        T top = pq.top();
        pq.pop();

        int weight = std::get<0>(top);
        int u_id = std::get<1>(top);
        int parentEdgeIdx = std::get<2>(top);

        if (visited[u_id])
            continue;

        visited[u_id] = true;

        // VISUAL: Highlight current node being added to MST
        if(parentEdgeIdx==-1)stepsList.append(std::make_tuple(HIGHLIGHT_NODE, u_id, PathNodeColor));

        // VISUAL: If this node came via an edge, color that edge as part of MST
        if (parentEdgeIdx != -1) {
            stepsList.append(std::make_tuple(HIGHLIGHT_EDGE, parentEdgeIdx, FinalPathEdgeColor));
        }

        // VISUAL: Set the "Distance" label to show the weight it was added with
        stepsList.append(std::make_tuple(SET_DISTANCE, u_id, weight));

        // Iterate neighbors
        for (int i = 0; i < edges.size(); ++i) {
            const auto &edge = edges.at(i);
            int v_id = -1;

            if (edge.node1Id == u_id) v_id = edge.node2Id;
            else if (edge.node2Id == u_id) v_id = edge.node1Id;

            if (v_id != -1 && !visited[v_id]) {
                // VISUAL: Briefly highlight the edge we are "probing"
                stepsList.append(std::make_tuple(HIGHLIGHT_EDGE, i, HighlightEdgeColor));

                pq.push({edge.value, v_id, i});

                // VISUAL: Mark neighbor as "Visited" (Tentative in PQ)
                stepsList.append(std::make_tuple(HIGHLIGHT_NODE, v_id, VisitedNodeColor));

                // VISUAL: Reset probing edge to default unless it's already MST
                // (This creates the 'scanning' effect)
                stepsList.append(std::make_tuple(HIGHLIGHT_EDGE, i, DefaultEdgeColor));
            }
        }


    }
}



void GraphVisualizer::dfsArticulation(int u, int p,
                                              QMap<int, bool> &visited,
                                              QMap<int, int> &disc,
                                              QMap<int, int> &low,
                                              QMap<int, QList<QPair<int, int>>> &adj,
                                              QSet<int> &articulationPoints) {
    visited[u] = true;
    disc[u] = low[u] = ++time;
    int children = 0;

    // VISUAL: Highlight current node being visited
    stepsList.append(std::make_tuple(HIGHLIGHT_NODE, u, CurrentNodeColor));
    stepsList.append(std::make_tuple(SET_DISTANCE, u, disc[u])); // Showing Discovery Time

    for (auto &edgePair : adj[u]) {
        int v = edgePair.first;
        int edgeIdx = edgePair.second;

        if (v == p) continue;

        if (visited[v]) {
            // BACK EDGE: Neighbor already visited and not parent
            low[u] = std::min(low[u], disc[v]);

            // VISUAL: Highlight back-edge briefly in Cyan
            stepsList.append(std::make_tuple(HIGHLIGHT_EDGE, edgeIdx, HighlightEdgeColor));
            stepsList.append(std::make_tuple(HIGHLIGHT_EDGE, edgeIdx, DefaultEdgeColor));
        } else {
            // TREE EDGE: Moving to a new node
            children++;

            // VISUAL: Highlight the edge being followed
            stepsList.append(std::make_tuple(HIGHLIGHT_EDGE, edgeIdx, TentativeEdgeColor));

            dfsArticulation(v, u, visited, disc, low, adj, articulationPoints);

            // Backtracking
            low[u] = std::min(low[u], low[v]);

            // Check Articulation Point Condition
            if (p != -1 && low[v] >= disc[u]) {
                articulationPoints.insert(u);
                // VISUAL: Mark node as Articulation Point (using Red/Destination color)
                stepsList.append(std::make_tuple(HIGHLIGHT_NODE, u, DestinationNodeColor));
            }
        }
    }

    // Root case
    if (p == -1 && children > 1) {
        articulationPoints.insert(u);
        stepsList.append(std::make_tuple(HIGHLIGHT_NODE, u, DestinationNodeColor));
    }

    // VISUAL: Mark node as fully processed (Blue/Visited)
    // Only if it's not already marked as an Articulation Point
    if (!articulationPoints.contains(u)) {
        stepsList.append(std::make_tuple(HIGHLIGHT_NODE, u, VisitedNodeColor));
    }
}
void GraphVisualizer::tarjanArticulationPoints()
{
    int n = nodes.size();
    if (n == 0) return;

    // 1. Prepare Data Structures
    QMap<int, int> disc, low;
    QMap<int, bool> visited;
    QSet<int> articulationPoints;
    // Build Adjacency List for faster lookup: NodeID -> List of <NeighborID, EdgeIndex>
    QMap<int, QList<QPair<int, int>>> adj;
    for (int i = 0; i < edges.size(); ++i) {
        int u = edges[i].node1Id;
        int v = edges[i].node2Id;
        adj[u].append({v, i});
        adj[v].append({u, i});
    }

    // Initialize values
    for (const auto &node : nodes) {
        visited[node.id] = false;
        disc[node.id] = -1;
        low[node.id] = -1;
    }

    // Run DFS for each component
    for (const auto &node : nodes) {
        if (!visited[node.id]) {
            dfsArticulation(node.id, -1, visited, disc, low, adj, articulationPoints);
        }
    }
}
=======
#include "graphvisualizer.h"
#include<queue>



GraphVisualizer::GraphVisualizer(QWidget *parent)
{
    setFixedSize(1000,600);

}

void GraphVisualizer::setNumberOfNodes(int count)
{
    if (count > 0 && count <= 50) {
        // Clear old state
        nodes.clear();
        edges.clear();
        firstSelectedNodeId = -1;

        // STORE the required count
        requiredNodeCount = count;

        qDebug() << "Ready to place" << requiredNodeCount << "nodes manually.";

        // Ensure edge creation is disabled while placing nodes
        isEdgeCreationMode = false;

        update(); // Request a repaint to show an empty canvas
    }

}


int GraphVisualizer::findNodeIdAt(const QPoint &point)
{
    for (const auto &node : nodes) {
        // Simple distance check from center (more accurate than QRect::contains)
        int dx = node.center.x() - point.x();
        int dy = node.center.y() - point.y();
        if (qSqrt(dx * dx + dy * dy) <= NodeRadius) {
            return node.id;
        }
    }
    return -1; // No node found
}

// shorthestPathVisualizer.cpp (Modify paintEvent)

void GraphVisualizer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Define Colors (Add these to your class header/definition)
    const QMap<int, QColor> nodeColors = {
        {DefaultNodeColor, Qt::white},
        {SourceNodeColor, Qt::darkGreen},
        {DestinationNodeColor, Qt::red},
        {CurrentNodeColor, Qt::cyan},
        {VisitedNodeColor, Qt::blue},
        {PathNodeColor, Qt::magenta}
    };
    const QMap<int, QColor> edgeColors = {
        {DefaultEdgeColor, Qt::gray},
        {HighlightEdgeColor, Qt::cyan},
        {TentativeEdgeColor, Qt::yellow},
        {FinalPathEdgeColor, Qt::magenta}
    };

    // 1. Draw Edges
    for (int i = 0; i < edges.size(); ++i) {
        const auto &edge = edges.at(i);
        QPoint p1, p2;
        // Find node centers p1, p2 (assuming you kept the node structure)
        if (Node *n1 = getNodeById(edge.node1Id)) p1 = n1->center;
        if (Node *n2 = getNodeById(edge.node2Id)) p2 = n2->center;

        // Draw the line with the current color state
        QColor lineColor = edgeColors.value(edge.colorState, Qt::gray);
        painter.setPen(QPen(lineColor, 3)); // Thicker for visibility
        painter.drawLine(p1, p2);

        // Draw the edge value
        if (edge.value != 0) {
            QPoint center = (p1 + p2) / 2;

            // Offset the text for visibility (optional, depends on graph density)
            QPointF dir = (p2 - p1);
            qreal len = std::sqrt(QPointF::dotProduct(dir, dir));
            if (len > 0) dir /= len;

            QPoint textPos = center;

            QRect textRect(textPos.x() - 15, textPos.y() - 10, 30, 20);
            painter.setBrush(Qt::yellow);
            painter.setPen(Qt::NoPen);
            painter.drawRect(textRect);

            painter.setPen(Qt::darkRed);
            painter.setFont(QFont("Arial", 12,QFont::Bold));
            painter.drawText(textRect, Qt::AlignCenter, QString::number(edge.value));
        }
    }

    // 2. Draw Nodes
    for (const auto &node : nodes) {

        QColor nodeFillColor = nodeColors.value(node.colorState, Qt::white);

        // Highlight the first selected node in edge creation mode
        if (isEdgeCreationMode && node.id == firstSelectedNodeId) {
            painter.setBrush(Qt::cyan);
        } else {
            painter.setBrush(nodeFillColor);
        }

        painter.setPen(QPen(Qt::white, 3));
        painter.drawEllipse(node.center, NodeRadius, NodeRadius);

        // Draw the node number (ID)
        painter.setFont(QFont("Arial", 20,QFont::Bold));
        painter.setPen(Qt::black);
        painter.drawText(node.rect, Qt::AlignCenter, QString::number(node.id));

        // Draw the distance value below the node (if known)

        QString distText = (node.distance == INT_MAX) ? "INF" : QString::number(node.distance);
        QRect distRect(node.center.x() - 25, node.center.y() + NodeRadius + 5, 50, 50);

        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 12,QFont::Bold));
        painter.drawText(distRect, Qt::AlignCenter, "D: " + distText);

    }
}
void GraphVisualizer::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QPoint clickPos = event->pos();
        int clickedNodeId = findNodeIdAt(clickPos);

        // ------- NODE PLACEMENT MODE ---------
        // If we haven't reached the required node count, we are in placement mode.
        if (nodes.size() < requiredNodeCount) {

            // Do not allow placement if the click is too close to the edge or over an existing node
            if (clickedNodeId == -1 &&
                clickPos.x() > NodeRadius && clickPos.x() < width() - NodeRadius &&
                clickPos.y() > NodeRadius && clickPos.y() < height() - NodeRadius)
            {
                Node newNode;
                // Node IDs must start from 1 and continue sequentially
                newNode.id = nodes.size() + 1;
                newNode.center = clickPos;
                newNode.rect = QRect(clickPos.x() - NodeRadius, clickPos.y() - NodeRadius, 2 * NodeRadius, 2 * NodeRadius);

                nodes.append(newNode);

                // If placement is now complete, reset requiredNodeCount
                if (nodes.size() == requiredNodeCount) {
                    qDebug() << "All" << requiredNodeCount << "nodes placed. Ready for edge creation.";
                }
                update();
            }
            return; // Exit, as we handled placement.
        }
        // ------EDGE VALUE INPUT MODE------
        if (putEdgeValueMode) {
            int edgeIndex = findEdgeAt(clickPos);

            if (edgeIndex != -1) {
                // Emit signal to MainWindow to open the input dialog
                // We pass the click position (clickPos) for UI placement (optional)
                emit requestEdgeValueInput(clickPos, edgeIndex);
            }
            return; // Handled input mode click.
        }

        // -------- EDGE CREATION MODE ----------
        // This only runs if placement is complete AND edge creation is enabled.
        if (isEdgeCreationMode) {
            if (clickedNodeId != -1) {
                if (firstSelectedNodeId == -1) {
                    // First node selected
                    firstSelectedNodeId = clickedNodeId;
                } else if (firstSelectedNodeId != clickedNodeId) {
                    // Second node selected: Create Edge
                    if (edgeExists(firstSelectedNodeId, clickedNodeId)) {
                        qDebug() << "Error: Edge already exists between" << firstSelectedNodeId << "and" << clickedNodeId;
                        firstSelectedNodeId = -1; // Reset selection without creating an edge
                    } else {
                        // Second node selected: Create Edge
                        Edge newEdge;
                        newEdge.node1Id = firstSelectedNodeId;
                        newEdge.node2Id = clickedNodeId;

                        edges.append(newEdge);
                        firstSelectedNodeId = -1; // Reset selection
                    }
                }
                update();
            }
        }
    }
}
void GraphVisualizer::setEdgeCreationMode(bool enabled)
{
    isEdgeCreationMode = enabled;
    putEdgeValueMode = false; // Disable edge value mode when entering edge creation mode
    firstSelectedNodeId = -1;
    update();
}

void GraphVisualizer::setEdgeValueMode(bool enabled)
{
    putEdgeValueMode = enabled;
    isEdgeCreationMode = false; // Disable edge creation mode when entering edge value mode
    firstSelectedNodeId = -1;
    update();
}
int GraphVisualizer::findEdgeAt(const QPoint &point)
{
    // A tolerance for clicking near an edge (e.g., 8 pixels)
    const int Tolerance = 8;

    // A simplified way to check proximity to a line segment.
    // Index i corresponds to the edge index in the QList.
    for (int i = 0; i < edges.size(); ++i) {
        const auto &edge = edges.at(i);
        QPoint p1, p2;

        // Find node centers
        for (const auto &node : nodes) {
            if (node.id == edge.node1Id) p1 = node.center;
            if (node.id == edge.node2Id) p2 = node.center;
        }
        QPointF v = p2 - p1; // Vector from P1 to P2
        QPointF w = point - p1;// Vector from P1 to Click Point
        qreal lineLengthSq = QPointF::dotProduct(v, v);
        if (lineLengthSq<1e-6) continue; // Avoid division by zero for coincident nodes

        // Get the projection parameter (t). This tells us where the click point projects onto the line (0 <= t <= 1 means on segment)
        qreal t = QPointF::dotProduct(w, v) / lineLengthSq;

        QPointF closestPoint;

        if (t < 0.0) {
            // Closest point is P1 (segment endpoint)
            closestPoint = p1;
        } else if (t > 1.0) {
            // Closest point is P2 (segment endpoint)
            closestPoint = p2;
        } else {
            // Closest point is on the line segment
            closestPoint = p1 + t * v;
        }

        // Calculate the squared distance from the click point to the closest point on the segment
        qreal dx = closestPoint.x() - point.x();
        qreal dy = closestPoint.y() - point.y();
        qreal distSq = dx * dx + dy * dy;

        // --- Final Check ---

        // If the actual distance is within tolerance
        if (std::sqrt(distSq) <= Tolerance) {
            return i; // Return the index of the edge
        }
    }
    return -1;
}

bool GraphVisualizer::GraphVisualizer::edgeExists(int id1, int id2)
{

    for (const auto &edge : edges) {
        if ((edge.node1Id == id1 && edge.node2Id == id2) || (edge.node1Id == id2 && edge.node2Id == id1)) {
            return true;
        }
    }
    return false;
}
GraphVisualizer::Node *GraphVisualizer::getNodeById(int id)
{
    for (int i = 0; i < nodes.size(); ++i) {
        if (nodes[i].id == id) {
            return &nodes[i];
        }
    }
    return nullptr;
}
bool GraphVisualizer::setEdgeValueByIndex(int index, int value)
{
    // 1. Check if the index is valid
    if (index >= 0 && index < edges.size()) {

        // 2. Update the private data structure
        edges[index].value = value;

        // 3. Request a repaint to show the new value immediately
        update();

        return true; // Success
    }

    qWarning() << "Error: Attempted to set edge value for invalid index:" << index;
    return false; // Failure
}
// shorthestPathVisualizer.cpp

void GraphVisualizer::startAlgorithm(int algorithmIndex, int srcId, int destId, int interval)
{

    if (timer) {
        timer->stop();
        delete timer;
        timer = nullptr;
    }
    // Clear previous state
    stepsList.clear();
    currentStepIndex = 0;
    intervalLength = interval;
    destinationNodeId = destId;

    // Reset all nodes/edges colors and distances
    for (auto &node : nodes) {
        node.colorState = DefaultNodeColor;
        node.distance = INT_MAX;
        node.parentId = -1;
    }
    for (auto &edge : edges) {
        edge.colorState = DefaultEdgeColor;
    }

    // Set source and destination colors
    if (Node *srcNode = getNodeById(srcId)) {
        srcNode->colorState = SourceNodeColor;
    }
    if (Node *destNode = getNodeById(destId)) {
        destNode->colorState = DestinationNodeColor;
    }

    // Generate algorithm steps
    if (algorithmIndex == 0) { // Assuming index 0 is Dijkstra
        dijkstraAlgorithm(srcId, destId);
    }
    else if (algorithmIndex == 1) {
        primsAlgorithm(srcId);
    }else if(algorithmIndex==2){
        tarjanArticulationPoints();
    }

    // Start visualization
    if (stepsList.isEmpty()) {
        qDebug() << "Algorithm completed instantly or no path found.";
        emit enableGraphButtons();
        update();
        return;
    }

    // Initialize and connect timers
    timer = new QTimer(this);
    timer->setTimerType(Qt::PreciseTimer);
    elapsedTimer = new QElapsedTimer;

    connect(timer, &QTimer::timeout, this, &GraphVisualizer::processNextStep);

    // We reuse the SortVisualizer timing pattern
    QTimer *timerUpdateElapsed = new QTimer(this);
    connect(timerUpdateElapsed, &QTimer::timeout, this, &GraphVisualizer::updateTimeElapsed);

    //emit disableGraphButtons();
    elapsedTimer->start();
    timer->start(intervalLength);
    timerUpdateElapsed->start(50); // Update elapsed time frequently

    update();
}

void GraphVisualizer::stopAlgorithm()
{
    if (timer) {
        timer->stop();
        delete timer;
        timer = nullptr;
    }
    if (elapsedTimer) {
        int elapsedTime = elapsedTimer->elapsed();
        emit setTimeElapsed(elapsedTime);
        delete elapsedTimer;
        elapsedTimer = nullptr;
    }

    // Ensure all timer connections are also cleaned up (using QObject parentage)
    QList<QTimer*> childTimers = findChildren<QTimer*>();
    for (QTimer *t : childTimers) {
        if (t != timer) {
            t->stop();
            t->deleteLater();
        }
    }

    emit enableGraphButtons();
    update();
}

void GraphVisualizer::updateTimeElapsed() {
    if (elapsedTimer) {
        emit setTimeElapsed(elapsedTimer->elapsed());
    }
}

void GraphVisualizer::processNextStep()
{
    if (currentStepIndex >= stepsList.size()) {
        qDebug() << "Visualization Finished.";
        stopAlgorithm();
        return;
    }

    auto step = stepsList[currentStepIndex];
    int command = std::get<0>(step);
    int val1 = std::get<1>(step); // Node ID or Edge Index
    int val2 = std::get<2>(step); // Color or Distance

    switch (command) {
    case HIGHLIGHT_NODE: {
        if (Node *node = getNodeById(val1)) {
            node->colorState = val2;
        }
        break;
    }
    case HIGHLIGHT_EDGE: {
        if (val1 >= 0 && val1 < edges.size()) {
            edges[val1].colorState = val2;
        }
        break;
    }
    case SET_DISTANCE: {
        // This step is mainly for information (e.g., displaying text near node)
        // For visualization, we just log it and rely on node color
        if (Node *node = getNodeById(val1)) {
            node->distance = val2;
        }
        break;
    }
    default:
        break;
    }

    update(); // Redraw the visualizer
    currentStepIndex++;
}

void GraphVisualizer::dijkstraAlgorithm(int srcId, int destId)
{

    QMap<int, int> distance;
    QMap<int, int> parent;
    for (const auto &node : nodes) {
        distance[node.id] = (node.id == srcId) ? 0 : INT_MAX;
        parent[node.id] = -1;
    }

    // 2. Priority Queue: {Distance, Node ID}
    // Use std::priority_queue with a custom QPair/std::pair wrapper if needed,
    // or simply use a QList as a basic unoptimized queue for simple visualization (less accurate to pseudocode but easier to implement)
    // STICKING TO PSEUDOCODE: Use std::priority_queue and map IDs to distances.
    using T = pair<int, int>;
    priority_queue<T,vector<T>,greater<T>> pq;

    pq.push({0, srcId});

    stepsList.append(make_tuple(HIGHLIGHT_NODE, srcId, CurrentNodeColor));
    stepsList.append(make_tuple(SET_DISTANCE, srcId, 0));

    while (!pq.empty()) {
        int d = pq.top().first;
        int u_id = pq.top().second;
        pq.pop();

        if (d > distance[u_id]) continue;

        // Visualization Step: Mark current node being processed
        stepsList.append(make_tuple(HIGHLIGHT_NODE, u_id, CurrentNodeColor));

        // Create a list of edges that need to be un-highlighted after processing u_id
        QList<int> edgesToReset;

        // Iterate through all edges/neighbors
        for (int i = 0; i < edges.size(); ++i) {
            const auto &edge = edges.at(i);
            int v_id = -1;

            if (edge.node1Id == u_id) v_id = edge.node2Id;
            else if (edge.node2Id == u_id) v_id = edge.node1Id;

            if (v_id != -1) {
                int weight = edge.value;

                // Visualization Step: Highlight the edge being checked (Dark Yellow)
                stepsList.append(make_tuple(HIGHLIGHT_EDGE, i, HighlightEdgeColor));

                // Relaxation
                if (distance[u_id] != INT_MAX && distance[u_id] + weight < distance[v_id]) {
                    distance[v_id] = distance[u_id] + weight;
                    parent[v_id] = u_id;
                    pq.push({distance[v_id], v_id});

                    // Visualization Step: Mark the neighbor node as tentative (Blue/Visited)
                    stepsList.append(make_tuple(SET_DISTANCE, v_id, distance[v_id]));
                    stepsList.append(make_tuple(HIGHLIGHT_NODE, v_id, VisitedNodeColor));

                    // Visualization Step: Mark the edge as part of the TENTATIVE path (Magenta)
                    stepsList.append(make_tuple(HIGHLIGHT_EDGE, i, TentativeEdgeColor));

                }

                // Track this edge to reset its color
                edgesToReset.append(i);
            }
        }

        // POST-RELAXATION: Reset all edges checked during this node's processing,
        // UNLESS it was set to TentativeEdgeColor (which can be reset later).
        // This is tricky. Let's simplify: reset the HighlightEdgeColor after checking.
        for (int edgeIndex : edgesToReset) {
            // Only reset the edge to gray if it wasn't just set to TentativeEdgeColor
            // Note: Since the loop is sequential, we can just reset the HighlightEdgeColor
            // if it wasn't improved. However, for a clean visual, a blanket reset is better.
            // A safer approach: For every edge check, add two steps: Highlight -> Unhighlight (or TentativeColor).
            // Let's rely on the TentativeEdgeColor to persist until the final traceback.
        }


        // Visualization Step: Mark current node as permanently visited (Blue/Visited)
        stepsList.append(make_tuple(HIGHLIGHT_NODE, u_id, VisitedNodeColor));

        if (u_id == destId) break;
    }
    for (int j = 0; j < edges.size(); ++j) {
        stepsList.append(std::make_tuple(HIGHLIGHT_EDGE, j, DefaultEdgeColor));
    }
    // Final Visualization Step: Trace back the final path

    int currId = destId;
    while (currId != -1 && currId != srcId) {
        int pId = parent[currId];
        if (pId == -1) break;

        // Find the edge between currId and pId
        for (int i = 0; i < edges.size(); ++i) {
            const auto &edge = edges.at(i);
            if ((edge.node1Id == currId && edge.node2Id == pId) || (edge.node1Id == pId && edge.node2Id == currId)) {

                // IMPORTANT: RESET ALL EXISTING EDGE COLORS FIRST to ensure only the final path shows up.
                // We add a cleanup pass before the final path display:
                // for (int j = 0; j < edges.size(); ++j) {
                //     stepsList.append(std::make_tuple(HIGHLIGHT_EDGE, j, DefaultEdgeColor));
                // }

                // Now, color the final path edge with the specific color
                stepsList.append(std::make_tuple(HIGHLIGHT_EDGE, i, FinalPathEdgeColor));
                break;
            }
        }
        stepsList.append(std::make_tuple(HIGHLIGHT_NODE, currId, PathNodeColor)); // Use new PathNodeColor
        currId = pId;
    }

    // Ensure the source and destination nodes are correctly highlighted at the end
    stepsList.append(std::make_tuple(HIGHLIGHT_NODE, srcId, SourceNodeColor));
    stepsList.append(std::make_tuple(HIGHLIGHT_NODE, destId, DestinationNodeColor));

    // Store final distances back into nodes for permanent display (optional)
    for (auto &node : nodes) {
        node.distance = distance.value(node.id, INT_MAX);
    }
}

void GraphVisualizer::primsAlgorithm(int startNodeId)
{
    QMap<int, bool> visited;
    for (const auto &node : nodes) visited[node.id] = false;

    // PQ stores: tuple<weight, current_node_id, parent_edge_index>
    using T = std::tuple<int, int, int>;
    std::priority_queue<T, std::vector<T>, std::greater<T>> pq;

    // Start with the source node
    pq.push({0, startNodeId, -1});

    while (!pq.empty()) {
        T top = pq.top();
        pq.pop();

        int weight = std::get<0>(top);
        int u_id = std::get<1>(top);
        int parentEdgeIdx = std::get<2>(top);

        if (visited[u_id])
            continue;

        visited[u_id] = true;

        // VISUAL: Highlight current node being added to MST
        if(parentEdgeIdx==-1)stepsList.append(std::make_tuple(HIGHLIGHT_NODE, u_id, PathNodeColor));

        // VISUAL: If this node came via an edge, color that edge as part of MST
        if (parentEdgeIdx != -1) {
            stepsList.append(std::make_tuple(HIGHLIGHT_EDGE, parentEdgeIdx, FinalPathEdgeColor));
        }

        // VISUAL: Set the "Distance" label to show the weight it was added with
        stepsList.append(std::make_tuple(SET_DISTANCE, u_id, weight));

        // Iterate neighbors
        for (int i = 0; i < edges.size(); ++i) {
            const auto &edge = edges.at(i);
            int v_id = -1;

            if (edge.node1Id == u_id) v_id = edge.node2Id;
            else if (edge.node2Id == u_id) v_id = edge.node1Id;

            if (v_id != -1 && !visited[v_id]) {
                // VISUAL: Briefly highlight the edge we are "probing"
                stepsList.append(std::make_tuple(HIGHLIGHT_EDGE, i, HighlightEdgeColor));

                pq.push({edge.value, v_id, i});

                // VISUAL: Mark neighbor as "Visited" (Tentative in PQ)
                stepsList.append(std::make_tuple(HIGHLIGHT_NODE, v_id, VisitedNodeColor));

                // VISUAL: Reset probing edge to default unless it's already MST
                // (This creates the 'scanning' effect)
                stepsList.append(std::make_tuple(HIGHLIGHT_EDGE, i, DefaultEdgeColor));
            }
        }


    }
}



void GraphVisualizer::dfsArticulation(int u, int p,
                                              QMap<int, bool> &visited,
                                              QMap<int, int> &disc,
                                              QMap<int, int> &low,
                                              QMap<int, QList<QPair<int, int>>> &adj,
                                              QSet<int> &articulationPoints) {
    visited[u] = true;
    disc[u] = low[u] = ++time;
    int children = 0;

    // VISUAL: Highlight current node being visited
    stepsList.append(std::make_tuple(HIGHLIGHT_NODE, u, CurrentNodeColor));
    stepsList.append(std::make_tuple(SET_DISTANCE, u, disc[u])); // Showing Discovery Time

    for (auto &edgePair : adj[u]) {
        int v = edgePair.first;
        int edgeIdx = edgePair.second;

        if (v == p) continue;

        if (visited[v]) {
            // BACK EDGE: Neighbor already visited and not parent
            low[u] = std::min(low[u], disc[v]);

            // VISUAL: Highlight back-edge briefly in Cyan
            stepsList.append(std::make_tuple(HIGHLIGHT_EDGE, edgeIdx, HighlightEdgeColor));
            stepsList.append(std::make_tuple(HIGHLIGHT_EDGE, edgeIdx, DefaultEdgeColor));
        } else {
            // TREE EDGE: Moving to a new node
            children++;

            // VISUAL: Highlight the edge being followed
            stepsList.append(std::make_tuple(HIGHLIGHT_EDGE, edgeIdx, TentativeEdgeColor));

            dfsArticulation(v, u, visited, disc, low, adj, articulationPoints);

            // Backtracking
            low[u] = std::min(low[u], low[v]);

            // Check Articulation Point Condition
            if (p != -1 && low[v] >= disc[u]) {
                articulationPoints.insert(u);
                // VISUAL: Mark node as Articulation Point (using Red/Destination color)
                stepsList.append(std::make_tuple(HIGHLIGHT_NODE, u, DestinationNodeColor));
            }
        }
    }

    // Root case
    if (p == -1 && children > 1) {
        articulationPoints.insert(u);
        stepsList.append(std::make_tuple(HIGHLIGHT_NODE, u, DestinationNodeColor));
    }

    // VISUAL: Mark node as fully processed (Blue/Visited)
    // Only if it's not already marked as an Articulation Point
    if (!articulationPoints.contains(u)) {
        stepsList.append(std::make_tuple(HIGHLIGHT_NODE, u, VisitedNodeColor));
    }
}
void GraphVisualizer::tarjanArticulationPoints()
{
    int n = nodes.size();
    if (n == 0) return;

    // 1. Prepare Data Structures
    QMap<int, int> disc, low;
    QMap<int, bool> visited;
    QSet<int> articulationPoints;
    // Build Adjacency List for faster lookup: NodeID -> List of <NeighborID, EdgeIndex>
    QMap<int, QList<QPair<int, int>>> adj;
    for (int i = 0; i < edges.size(); ++i) {
        int u = edges[i].node1Id;
        int v = edges[i].node2Id;
        adj[u].append({v, i});
        adj[v].append({u, i});
    }

    // Initialize values
    for (const auto &node : nodes) {
        visited[node.id] = false;
        disc[node.id] = -1;
        low[node.id] = -1;
    }

    // Run DFS for each component
    for (const auto &node : nodes) {
        if (!visited[node.id]) {
            dfsArticulation(node.id, -1, visited, disc, low, adj, articulationPoints);
        }
    }
}
>>>>>>> 04a9751158f621a6df50fbe7c01dfb93f96e7baa
