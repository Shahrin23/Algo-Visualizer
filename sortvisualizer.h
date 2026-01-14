<<<<<<< HEAD
#ifndef SORTVISUALIZER_H
#define SORTVISUALIZER_H

#include <QWidget>
#include <QElapsedTimer>
#include<QTimer>
class SortVisualizer:public QWidget
{
    Q_OBJECT
public:
    explicit SortVisualizer(QWidget  *parent=nullptr);
    void startSort(int algorithmIndex, bool increasing, int interval, int numRects);
    void stopSort();
    void randomize();
    int getNumberOfElements() const { return numberOfElements; }
    void setCustomHeights(const QVector<int>& heights);
    void changeNumberOfRectangles(int newNumberOfRectangles);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QVector<int> numbersArray;
    QVector<int> sortArray;
    QVector<QRect> rectanglesArray;
    QVector<short int> rectangleColors;
    QString currentStatus;
    void generateArray();
    void generateRectangles();
    void setNumberOfElements(int newNumberOfElements);
    void setRectangleWidth(int newRectWidth);
    void swapRectangles(int i, int j);
    void setRectangle(int i, int j);
    void setRectangle(int i, QRect rect);
    void setRectangleToHeight(int i, int height);
    void colorRectangle(int i, QPainter *painter, QColor color);
    void copyNumbersArray();

    int numberOfElements;
    int rectangleWidth;
    int intervalLength;
    bool isIncreasingSort = false;

    QTimer *timer;
    QTimer *timerUpdateElapsed;
    QElapsedTimer *elapsedTimer;

    QVector<std::tuple<short int, short int, short int>> stepsVector;
    int currIndex = 0;


    enum Colors {
        DefaultFillColor = 0,
        DefaultBorderColor = 1,
        HighlightColor = 2,
        HighlightRangeColor = 3,
        HighlightSwapColor=4
    };
    QVector<QColor> colors = {
        QColor(Qt::red), // 0
        QColor(Qt::black),  // 1
        QColor(Qt::magenta),   // 2
        QColor(Qt::darkCyan),// 3
        QColor(Qt::cyan),
        QColor(Qt::gray)
    };

    void connectTimers();

    void processHighlight(int i, int j);
    void processSwapHighlight(int i,int j);
    void processSwap(int i, int j);
    void processSetHeight(int i, int height);
    void processSet(int i, int j);
    void processInsertionSet(int i, int j);
    void processHighlightRange(int begin, int end);

    void unHighlight(int prevCommand, int i, int j);
    void unHighlightRange(int begin, int end);

    void startSelectionSort();
    void startBubbleSort();
    void startInsertionSort();
    void startMergeSort(); // todo
    void startQuickSort();

    void selectionSortIncreasing();
    void selectionSortDecreasing();
    void bubbleSortIncreasing();
    void bubbleSortDecreasing();
    void insertionSortIncreasing(); // todo
    void insertionSortDecreasing(); // todo
    void mergeSortIncreasing(int begin, int end); // todo
    void mergeSortDecreasing(int begin, int end); // todo
    void mergeIncreasing(int left, int mid, int right);
    void mergeDecreasing(int left, int mid, int right);
    void quickSortIncreasing(int low, int high);
    void quickSortDecreasing(int low, int high);
    int partitionIncreasing(int low, int high);
    int partitionDecreasing(int low, int high);

private slots:
    void processCurrentStep();
    void updateTimeElapsed();

signals:
    void enableSortButtons();
    void disableButtons();
    void setTimeElapsed(int time);
};

#endif // SORTVISUALIZER_H
=======
#ifndef SORTVISUALIZER_H
#define SORTVISUALIZER_H

#include <QWidget>
#include <QElapsedTimer>
#include<QTimer>
class SortVisualizer:public QWidget
{
    Q_OBJECT
public:
    explicit SortVisualizer(QWidget  *parent=nullptr);
    void startSort(int algorithmIndex, bool increasing, int interval, int numRects);
    void stopSort();
    void randomize();
    int getNumberOfElements() const { return numberOfElements; }
    void setCustomHeights(const QVector<int>& heights);
    void changeNumberOfRectangles(int newNumberOfRectangles);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QVector<int> numbersArray;
    QVector<int> sortArray;
    QVector<QRect> rectanglesArray;
    QVector<short int> rectangleColors;

    void generateArray();
    void generateRectangles();
    void setNumberOfElements(int newNumberOfElements);
    void setRectangleWidth(int newRectWidth);
    void swapRectangles(int i, int j);
    void setRectangle(int i, int j);
    void setRectangle(int i, QRect rect);
    void setRectangleToHeight(int i, int height);
    void colorRectangle(int i, QPainter *painter, QColor color);
    void copyNumbersArray();

    int numberOfElements;
    int rectangleWidth;
    int intervalLength;
    bool isIncreasingSort = false;

    QTimer *timer;
    QTimer *timerUpdateElapsed;
    QElapsedTimer *elapsedTimer;

    QVector<std::tuple<short int, short int, short int>> stepsVector;
    int currIndex = 0;


    enum Colors {
        DefaultFillColor = 0,
        DefaultBorderColor = 1,
        HighlightColor = 2,
        HighlightRangeColor = 3
    };
    QVector<QColor> colors = {
        QColor(Qt::red), // 0
        QColor(Qt::black),  // 1
        QColor(Qt::magenta),   // 2
        QColor(Qt::darkCyan),// 3
        QColor(Qt::gray)
    };

    void connectTimers();

    void processHighlight(int i, int j);
    void processSwap(int i, int j);
    void processSetHeight(int i, int height);
    void processSet(int i, int j);
    void processInsertionSet(int i, int j);
    void processHighlightRange(int begin, int end);

    void unHighlight(int prevCommand, int i, int j);
    void unHighlightRange(int begin, int end);

    void startSelectionSort();
    void startBubbleSort();
    void startInsertionSort();
    void startMergeSort(); // todo
    void startQuickSort();

    void selectionSortIncreasing();
    void selectionSortDecreasing();
    void bubbleSortIncreasing();
    void bubbleSortDecreasing();
    void insertionSortIncreasing(); // todo
    void insertionSortDecreasing(); // todo
    void mergeSortIncreasing(int begin, int end); // todo
    void mergeSortDecreasing(int begin, int end); // todo
    void mergeIncreasing(int left, int mid, int right);
    void mergeDecreasing(int left, int mid, int right);
    void quickSortIncreasing(int low, int high);
    void quickSortDecreasing(int low, int high);
    int partitionIncreasing(int low, int high);
    int partitionDecreasing(int low, int high);

private slots:
    void processCurrentStep();
    void updateTimeElapsed();

signals:
    void enableSortButtons();
    void disableButtons();
    void setTimeElapsed(int time);
};

#endif // SORTVISUALIZER_H
>>>>>>> 04a9751158f621a6df50fbe7c01dfb93f96e7baa
