
#include "treevisualizer.h"
#include <stack>
#include <QtMath>
#include <QTextStream>

using namespace std;
TreeVisualizer::TreeVisualizer(QWidget *parent)
{

    setFixedSize(1000,600);
}

void TreeVisualizer::constructTree(QList<int> values) {
    treeNodes.clear();
    treeEdges.clear();
    if (values.isEmpty()) return;

    // Create UI Nodes
    for (int i = 0; i < values.size(); ++i) {
        TreeNodeUI node;
        node.val = values[i];
        node.id = i;
        treeNodes.append(node);
    }

    // Connect indices (2*i+1, 2*i+2) and calculate positions
    for (int i = 0; i < treeNodes.size(); ++i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < treeNodes.size()) {
            treeNodes[i].leftChildIdx = left;
            treeEdges.append({i, left, Qt::gray});
        }
        if (right < treeNodes.size()) {
            treeNodes[i].rightChildIdx = right;
            treeEdges.append({i, right, Qt::gray});
        }
    }

    // Recursive position calculation: Root at (width/2, 50)
    calculateCoordinates(0, 0, width() / 2, width() / 4);
    update();
}
void TreeVisualizer::calculateCoordinates(int idx, int level, float x, float x_offset) {
    if (idx >= treeNodes.size()) return;

    treeNodes[idx].pos = QPointF(x, 60 + (level * 80));

    if (treeNodes[idx].leftChildIdx != -1)
        calculateCoordinates(treeNodes[idx].leftChildIdx, level + 1, x - x_offset, x_offset / 2);
    if (treeNodes[idx].rightChildIdx != -1)
        calculateCoordinates(treeNodes[idx].rightChildIdx, level + 1, x + x_offset, x_offset / 2);
}
void TreeVisualizer::generatePreOrder() {
    if (treeNodes.isEmpty()) return;

    std::stack<int> s;
    s.push(0); // Start with root index
    QList<int> resultSequence;
    while (!s.empty()) {
        int currIdx = s.top();
        s.pop();

        // 1. Visit the node (Root)
        int value = treeNodes[currIdx].val;
        resultSequence.append(value);
        stepsList.append({HIGHLIGHT_NODE_TREE, currIdx, Qt::magenta});

        // 2. Push Right child first (so Left is processed first out of stack)
        int right = treeNodes[currIdx].rightChildIdx;
        if (right != -1 && right < treeNodes.size()) {
            stepsList.append({HIGHLIGHT_NODE_TREE, right, Qt::cyan}); // Highlight as "discovered"
            s.push(right);
        }

        // 3. Push Left child
        int left = treeNodes[currIdx].leftChildIdx;
        if (left != -1 && left < treeNodes.size()) {
            stepsList.append({HIGHLIGHT_NODE_TREE, left, Qt::cyan}); // Highlight as "discovered"
            s.push(left);
        }
    }
    qDebug()<<"PreOrder Traversal :";
    qDebug()<<resultSequence;

}

void TreeVisualizer::generateInOrder() {
    if (treeNodes.isEmpty()) return;

    std::stack<int> s;
    int currIdx = 0;
    QList<int> resultSequence;
    while (currIdx != -1 || !s.empty()) {
        // Reach the leftmost node of the current node
        while (currIdx != -1 && currIdx < treeNodes.size()) {
            stepsList.append({HIGHLIGHT_NODE_TREE, currIdx, Qt::cyan}); // Path finding
            s.push(currIdx);
            currIdx = treeNodes[currIdx].leftChildIdx;
        }

        currIdx = s.top();
        s.pop();

        // Visit the node
        int value = treeNodes[currIdx].val;
        resultSequence.append(value);
        stepsList.append({HIGHLIGHT_NODE_TREE, currIdx, Qt::magenta});

        // We have visited the node and its left subtree. Now, it's right subtree's turn
        currIdx = treeNodes[currIdx].rightChildIdx;
    }
    qDebug()<<"InOrder Traversal :";
    qDebug()<<resultSequence;
}

void TreeVisualizer::generatePostOrder() {
    if (treeNodes.isEmpty()) return;

    // Post-order is trickier iteratively.
    // We use two stacks or a "modified pre-order" (Root-Right-Left) and reverse it.
    std::stack<int> s1, s2;
    s1.push(0);
    QList<int> resultSequence;
    while (!s1.empty()) {
        int currIdx = s1.top();
        s1.pop();
        s2.push(currIdx);

        stepsList.append({HIGHLIGHT_NODE_TREE, currIdx, Qt::cyan}); // Traversing

        int left = treeNodes[currIdx].leftChildIdx;
        if (left != -1) s1.push(left);

        int right = treeNodes[currIdx].rightChildIdx;
        if (right != -1) s1.push(right);
    }

    // Now s2 contains nodes in Post-order. We add them to stepsList to show "completion"
    while (!s2.empty()) {
        int finalIdx = s2.top();
        s2.pop();
        int value = treeNodes[finalIdx].val;
        resultSequence.append(value);
        stepsList.append({HIGHLIGHT_NODE_TREE, finalIdx, Qt::magenta}); // Final Visit
    }
    qDebug()<<"PostOrder Traversal :";
    qDebug()<<resultSequence;
}
void TreeVisualizer::startAlgorithm(int algoIndex, int interval) {
    stopAlgorithm();
    stepsList.clear();
    currentStepIndex = 0;
    intervalLength = interval;
    for (int i = 0; i < treeNodes.size(); ++i) {
        treeNodes[i].color = Qt::white;
    }
    if (algoIndex == 0) generateInOrder();
    // Add logic for 1 (PreOrder) and 2 (PostOrder) similarly...
    else if(algoIndex==1)generatePreOrder();
    else if(algoIndex==2)generatePostOrder();

    timer = new QTimer(this);
    elapsedTimer = new QElapsedTimer;
    connect(timer, &QTimer::timeout, this, &TreeVisualizer::processNextStep);

    QTimer *timeTimer = new QTimer(this);
    connect(timeTimer, &QTimer::timeout, this, &TreeVisualizer::updateTimeElapsed);

    elapsedTimer->start();
    timer->start(intervalLength);
    timeTimer->start(50);

    emit disableTreeButtons();
}
void TreeVisualizer::processNextStep() {
    if (currentStepIndex >= stepsList.size()) {
        stopAlgorithm();
        return;
    }
    auto [cmd, idx, color] = stepsList[currentStepIndex++];
    if (cmd == HIGHLIGHT_NODE_TREE) treeNodes[idx].color = color;
    update();
}
void TreeVisualizer::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    for (const auto& edge : treeEdges) {
        painter.setPen(QPen(edge.color, 2));
        painter.drawLine(treeNodes[edge.fromIdx].pos, treeNodes[edge.toIdx].pos);
    }

    for (const auto& node : treeNodes) {
        painter.setBrush(node.color);
        painter.setPen(Qt::black);
        painter.drawEllipse(node.pos, 20, 20);
        painter.drawText(QRectF(node.pos.x()-20, node.pos.y()-20, 40, 40), Qt::AlignCenter, QString::number(node.val));
    }
}
void TreeVisualizer::updateTimeElapsed() {
    if (elapsedTimer) {
        emit setTimeElapsed(elapsedTimer->elapsed());
    }
}

void TreeVisualizer::stopAlgorithm() {
    if (timer) {
        timer->stop();
        delete timer;
        timer = nullptr;
    }
    if (elapsedTimer) {
        // Emit final time before deleting
        emit setTimeElapsed(elapsedTimer->elapsed());
        delete elapsedTimer;
        elapsedTimer = nullptr;
    }

    // Clean up any remaining helper timers
    QList<QTimer*> childTimers = findChildren<QTimer*>();
    for (QTimer *t : childTimers) {
        t->stop();
        t->deleteLater();
    }

    emit enableTreeButtons();
    update();
}
