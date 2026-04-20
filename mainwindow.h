
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sortvisualizer.h"
#include "graphvisualizer.h"
#include "treevisualizer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void disableSortButtons();
    void enableSortButtons();

private:
    Ui::MainWindow *ui;
    SortVisualizer *sortVisualizer;
    GraphVisualizer *graphVisualizer;
    TreeVisualizer *treeVisualizer;
    int algorithmIndex;
    void promptForAStarSrcDest();
private slots:
    void start();
    void stop();
    void randomize();
    void numRectsChanged();
    void promptForRectCount();
    void promptForHeights();
    void promptForNumberOfNodes();
    void showSortingPage();
    void showSelectionPage();
    void showGraphPage();
    void showTreePage();
    void enableEdgeCreationMode();
    void toggleEdgeValueMode();
    void handleEdgeValueInput(const QPoint &pos, int edgeIndex);
    void enableGraphButtons();
    void disableGraphButtons();
    void handleAStarNodeInput(const QPoint &clickPos);
    void promptForSrcDest();
    void enableTreeButtons();
    void disableTreeButtons();
    void promptForTreeNodes();
    void onAlgoComboChanged(int index);

public slots:
    void setElapsedTime(int time);
};
#endif // MAINWINDOW_H
