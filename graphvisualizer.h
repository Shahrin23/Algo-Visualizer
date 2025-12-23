#ifndef GRAPHVISUALIZER_H
#define GRAPHVISUALIZER_H

#include <QWidget>
#include <QDebug>
#include <QRandomGenerator>
#include <QColor>
#include <QMessageBox>
#include <QPainter>
#include <QElapsedTimer>
#include <QMouseEvent>
#include <QTime>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <QTimer>
#include <QPair>
#include <QList>
#include <tuple>


using namespace std;

enum PathColors {
    DefaultNodeColor,
    SourceNodeColor,
    DestinationNodeColor,
    CurrentNodeColor,
    VisitedNodeColor,
    TentativeEdgeColor,
    PathNodeColor,
    // Add colors for edges
    DefaultEdgeColor, // Assuming Qt::gray
    HighlightEdgeColor, // e.g., Qt::yellow or Qt::red
    FinalPathEdgeColor
};
enum PathStepCommand {
    HIGHLIGHT_NODE, // Value1: Node ID, Value2: Color
    HIGHLIGHT_EDGE, // Value1: Edge Index, Value2: Color
    SET_DISTANCE    // Value1: Node ID, Value2: Distance (not used for coloring, just info)
};

class GraphVisualizer: public QWidget
{
    Q_OBJECT
    struct Node {
        int id;         // The number (1, 2, 3...)
        QPoint center;  // The center position of the circle
        QRect rect;     // The bounding box for mouse click detection
        int distance = INT_MAX; // Distance from source (INT_MAX initially)
        int colorState = DefaultNodeColor; // Current color state
        int parentId = -1; // Parent node in the shortest path
    };

    // Structure to hold Edge data
    struct Edge {
        int node1Id;
        int node2Id;
        int value = 0; // Default edge weight
        int colorState = DefaultEdgeColor; // Current color state
    };
public:
    GraphVisualizer(QWidget* parent=nullptr);
    void setNumberOfNodes(int count);
    void setEdgeCreationMode(bool enabled);
    void setEdgeValueMode(bool enabled);
    bool isEdgeCreationModeEnabled() const { return isEdgeCreationMode; }
    bool isEdgeValueModeEnabled() const { return putEdgeValueMode; }
    bool setEdgeValueByIndex(int index, int value);
    int getNumberOfNodes()const {return nodes.size();}
    void startAlgorithm(int algorithmIndex, int srcId, int destId, int interval);
    void stopAlgorithm();

    void dijkstraAlgorithm(int srcId, int destId);
    void primsAlgorithm(int startNodeId);
    void dfsArticulation(int u, int p,QMap<int, bool> &visited,QMap<int, int> &disc,QMap<int, int> &low,QMap<int, QList<QPair<int, int>>> &adj,QSet<int> &articulationPoints);
    void tarjanArticulationPoints();

signals:
    void requestEdgeValueInput(const QPoint &pos, int edgeIndex);
    void enableGraphButtons();
    void disableGraphButtons();
    void setTimeElapsed(int time);

private slots:
    void processNextStep(); // Executes one step of the visualization
    void updateTimeElapsed();
protected:
    void paintEvent(QPaintEvent *event) override;// Override the paint event to draw nodes and edges
    void mousePressEvent(QMouseEvent *event) override;// Override mouse events for interaction

private:

    // Data structures for the graph
    QTimer *timer = nullptr;
    QElapsedTimer *elapsedTimer = nullptr;

    QList<Node> nodes;
    QList<Edge> edges;
    QList<tuple<int, int, int>> stepsList;
    // State variables for interaction
    bool isEdgeCreationMode = false;
    int firstSelectedNodeId = -1;
    int requiredNodeCount = 0;
    bool putEdgeValueMode = false;
    int currentStepIndex = 0;
    int destinationNodeId = -1;
    int intervalLength = 50;
    int time=0;
    // Constants
    const int NodeRadius = 30;
    // Helper functions
    int findNodeIdAt(const QPoint &point);
    int findEdgeAt(const QPoint &point);
    Node* getNodeById(int id);
    bool edgeExists(int id1, int id2);
};

#endif // GRAPHVISUALIZER_H
