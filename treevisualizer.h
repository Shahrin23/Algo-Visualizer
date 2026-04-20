
#ifndef TREEVISUALIZER_H
#define TREEVISUALIZER_H

#include <QObject>
#include <QWidget>
#include <QList>
#include <QTimer>
#include <QElapsedTimer>
#include <QPainter>

enum TreeCommand { HIGHLIGHT_NODE_TREE, HIGHLIGHT_EDGE_TREE, RESET_ALL };

struct TreeNodeUI {
    int val;
    int id;
    QPointF pos;
    int leftChildIdx = -1;
    int rightChildIdx = -1;
    QColor color = Qt::white;
};

struct TreeEdgeUI {
    int fromIdx;
    int toIdx;
    QColor color = Qt::gray;
};

class TreeVisualizer:public QWidget
{
    Q_OBJECT
public:
    explicit TreeVisualizer(QWidget* parent=nullptr);
    void constructTree(QList<int> values);
    void startAlgorithm(int algoIndex, int interval);
    void stopAlgorithm();
signals:
    void enableTreeButtons();
    void disableTreeButtons();
    void setTimeElapsed(int time);
protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void processNextStep();
    void updateTimeElapsed();
private:
    QList<TreeNodeUI> treeNodes;
    QList<TreeEdgeUI> treeEdges;
    QList<std::tuple<int, int, QColor>> stepsList; // command, index, color

    int currentStepIndex = 0;
    QTimer *timer = nullptr;
    QElapsedTimer *elapsedTimer = nullptr;
    int intervalLength = 500;

    void calculateCoordinates(int idx, int level, float x, float x_offset);
    void generatePreOrder();
    void generateInOrder();
    void generatePostOrder();
};

#endif // TREEVISUALIZER_H
