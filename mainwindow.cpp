<<<<<<< HEAD
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "sortvisualizer.h"
#include "graphvisualizer.h"
#include "treevisualizer.h"
#include <QtWidgets>
#include <QPalette>
#include <QInputDialog>
#include <QStringList>
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sortVisualizer=new SortVisualizer;
    graphVisualizer=new GraphVisualizer;
    treeVisualizer=new TreeVisualizer;

    QWidget *controlContainer = new QWidget;
    controlContainer->setLayout(ui->verticalLayout);
    QHBoxLayout *mainLayout = new QHBoxLayout;

    mainLayout->addWidget(sortVisualizer, 4);
    mainLayout->addWidget(controlContainer, 1);
    ui->sortingPage->setLayout(mainLayout);

    QWidget *controlContainer2 = new QWidget;
    controlContainer2->setLayout(ui->verticalLayout_2);
    QHBoxLayout *mainLayout2 = new QHBoxLayout;

    mainLayout2->addWidget(graphVisualizer, 4);
    mainLayout2->addWidget(controlContainer2, 1);
    ui->ShorthstPathPage->setLayout(mainLayout2);

    QWidget *controlContainer3 = new QWidget;
    controlContainer3->setLayout(ui->verticalLayout_3);
    QHBoxLayout *mainLayout3 = new QHBoxLayout;

    mainLayout3->addWidget(treeVisualizer, 4);
    mainLayout3->addWidget(controlContainer3, 1);
    ui->TreePage->setLayout(mainLayout3);

    setCentralWidget(ui->mainStackWidget);
    connect(sortVisualizer, &SortVisualizer::enableSortButtons, this, &MainWindow::enableSortButtons);
    connect(sortVisualizer, &SortVisualizer::disableButtons, this, &MainWindow::disableSortButtons);
    connect(ui->randomButton, &QPushButton::clicked, this, &MainWindow::randomize);
    connect(sortVisualizer, &SortVisualizer::setTimeElapsed, this, &MainWindow::setElapsedTime);
    connect(ui->numberOfEle, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::numRectsChanged);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::start);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stop);
    connect(ui->inputButton, &QPushButton::clicked, this, &MainWindow::promptForRectCount);
    connect(ui->inputHeightButton, &QPushButton::clicked, this, &MainWindow::promptForHeights);
    connect(ui->SortingButton, &QPushButton::clicked, this, &MainWindow::showSortingPage);
    connect(ui->ShorthestPathButton, &QPushButton::clicked, this, &MainWindow::showGraphPage);
    connect(ui->TreeButton, &QPushButton::clicked, this, &MainWindow::showTreePage);
    connect(ui->BackButton, &QPushButton::clicked, this, &MainWindow::showSelectionPage);
    connect(ui->BackButton_2, &QPushButton::clicked, this, &MainWindow::showSelectionPage);
    connect(ui->BackButton_3, &QPushButton::clicked, this, &MainWindow::showSelectionPage);
    connect(ui->inputNONButton, &QPushButton::clicked, this, &MainWindow::promptForNumberOfNodes);
    connect(ui->createEdgeButton, &QPushButton::clicked,this,&MainWindow::enableEdgeCreationMode);
    connect(ui->edgeValueButton, &QPushButton::clicked, this, &MainWindow::toggleEdgeValueMode);
    connect(graphVisualizer, &GraphVisualizer::requestEdgeValueInput, this, &MainWindow::handleEdgeValueInput);
    connect(ui->startButton_2, &QPushButton::clicked, this, &MainWindow::start);
    connect(ui->stopButton_2, &QPushButton::clicked, this, &MainWindow::stop);
    connect(graphVisualizer, &GraphVisualizer::enableGraphButtons, this, &MainWindow::enableGraphButtons);
    connect(graphVisualizer, &GraphVisualizer::disableGraphButtons, this, &MainWindow::disableGraphButtons);
    connect(ui->startButton_3, &QPushButton::clicked, this, &MainWindow::start);
    connect(ui->stopButton_3, &QPushButton::clicked, this, &MainWindow::stop);
    connect(ui->inputNONButton_2, &QPushButton::clicked, this, &MainWindow::promptForTreeNodes);
    connect(treeVisualizer, &TreeVisualizer::enableTreeButtons, this, &MainWindow::enableTreeButtons);
    connect(treeVisualizer, &TreeVisualizer::disableTreeButtons, this, &MainWindow::disableTreeButtons);
    connect(graphVisualizer, &GraphVisualizer::setTimeElapsed, this, &MainWindow::setElapsedTime);
    connect(treeVisualizer, &TreeVisualizer::setTimeElapsed, this, &MainWindow::setElapsedTime);
    ui->mainStackWidget->setCurrentIndex(0);
}

void MainWindow::promptForTreeNodes() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Tree Nodes"),
                                         tr("Enter integers (comma separated, max 50):"),
                                         QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
        QStringList parts = text.split(',', Qt::SkipEmptyParts);
        QList<int> values;
        for (int i = 0; i < qMin(parts.size(), 50); ++i) {
            bool conv;
            int val = parts[i].trimmed().toInt(&conv);
            if (conv) values.append(val);
        }
        treeVisualizer->constructTree(values);
    }
}

void MainWindow::promptForRectCount()
{
    if (!sortVisualizer) {
        qDebug() << "Error: SortVisualizer is null.";
        return;
    }

    bool ok;


    int currentCount = sortVisualizer->getNumberOfElements();


    int newCount = QInputDialog::getInt(
        this,
        tr("Set Rectangle Count"),
        tr("Number of Rectangles (2-1000):"),
        currentCount,
        2,
        1000,
        1,
        &ok
        );

    if (ok) {

        sortVisualizer->changeNumberOfRectangles(newCount);
        ui->numberOfEle->insertItem(0, QString::number(newCount), newCount);
        ui->numberOfEle->setCurrentIndex(0);
        // sortVisualizer->randomize();
        ui->lcdNumber->display(0);
        qDebug() << "Number of elements set to:" << newCount;
    }
}
// mainwindow.cpp

void MainWindow::promptForHeights()
{
    if (!sortVisualizer) {
        QMessageBox::critical(this, tr("Error"), tr("Visualizer is not initialized."));
        return;
    }
    bool ok;
    int expectedCount = sortVisualizer->getNumberOfElements();
    int maxBarHeight =height();
    QString heightsString = QInputDialog::getText(
        this,
        tr("Set Custom Array Heights"),
        tr("Enter %1 comma-separated heights (Max: %2):").arg(expectedCount).arg(maxBarHeight), // <-- Updated text
        QLineEdit::Normal,
        tr("e.g., 50, 100, 250... (Max: %1)").arg(maxBarHeight), // <-- Updated default text
        &ok
        );
    if (ok && !heightsString.isEmpty()) {
        QVector<int> customHeights;
        QStringList parts = heightsString.split(',', Qt::SkipEmptyParts);
        for (const QString &part : parts) {
            bool conversionOk;
            int height = part.trimmed().toInt(&conversionOk);

            // Validate: Must be a number, non-negative, AND within the pixel height limit
            if (conversionOk && height >= 0 && height <= maxBarHeight) { // <-- ADDED maxBarHeight check
                customHeights.append(height);
            } else {
                QMessageBox::warning(this, tr("Input Error"),
                                     tr("Invalid value or height (%1) is outside the valid range (0-%2).")
                                         .arg(height).arg(maxBarHeight));
                return;
            }
        }
        if (customHeights.count() != expectedCount) {
            QMessageBox::warning(this, tr("Input Error"),
                                 tr("Expected %1 heights, but received %2. The array size was not changed.")
                                     .arg(expectedCount).arg(customHeights.count())
                                 );
            return;
        }
        sortVisualizer->setCustomHeights(customHeights);
    }
}

void MainWindow::promptForNumberOfNodes()
{
    bool ok;
    int nodeCount = QInputDialog::getInt(
        this,
        tr("Set Number of Nodes"),
        tr("Enter number of nodes (1-50):"),
        5, // Default value
        1, // Min value
        50, // Max value
        1, // Step
        &ok
        );

    if (ok) {
        if (graphVisualizer) {
            graphVisualizer->setNumberOfNodes(nodeCount);
        }
    }
}
void MainWindow::start() {
    if (ui->mainStackWidget->currentIndex() == 2) {
        disableGraphButtons();
        //if (ui->AlgoComboBox_2->currentIndex() == 0) {
        promptForSrcDest();
        //}
        // else if (ui->AlgoComboBox_2->currentIndex()==1) {
        //     primsAlgorithm(srcId);
        // }


    } else if (ui->mainStackWidget->currentIndex() == 1) {
        if (!ui || !ui->AlgoComboBox || !ui->radioIncreasing || !ui->spinBox) {
            qInfo() << "ERROR: One or more UI elements are null!";
            return; // Prevents crash
        }
        algorithmIndex = ui->AlgoComboBox->currentIndex();
        bool increasing = ui->radioIncreasing->isChecked();
        int interval = ui->spinBox->value();
        int numberOfRects = ui->numberOfEle->currentText().toInt();
        disableSortButtons();
        //qInfo()<<increasing<<interval<<numberOfRects;
        sortVisualizer->startSort(algorithmIndex, increasing, interval, numberOfRects);
    }else if(ui->mainStackWidget->currentIndex()==3){
        disableTreeButtons();
        int interval = ui->spinBox_3->value();
        int algo = ui->AlgoComboBox_3->currentIndex();
        treeVisualizer->startAlgorithm(algo, interval);

    }

}

void MainWindow::stop() {
    if (ui->mainStackWidget->currentIndex() == 2) {
        graphVisualizer->stopAlgorithm();
    } else if (ui->mainStackWidget->currentIndex() == 1) {
        sortVisualizer->stopSort();
    }else if(ui->mainStackWidget->currentIndex()==3){
        treeVisualizer->stopAlgorithm();
    }
}

void MainWindow::disableSortButtons() {
    ui->startButton->setDisabled(true);
    ui->stopButton->setDisabled(false);
    ui->randomButton->setDisabled(true);
    ui->numberOfEle->setDisabled(true);
    ui->inputButton->setDisabled(true);
    ui->inputHeightButton->setDisabled(true);
}

void MainWindow::enableSortButtons() {
    ui->startButton->setDisabled(false);
    ui->stopButton->setDisabled(true);
    ui->randomButton->setDisabled(false);
    ui->numberOfEle->setDisabled(false);
    ui->inputButton->setDisabled(false);
    ui->inputHeightButton->setDisabled(false);
}

void MainWindow::setElapsedTime(int time) {
    if (time/1000 != ui->lcdNumber->intValue()) {
        ui->lcdNumber->display(time/1000);

    }
    if (time!= ui->lcdNumber_2->intValue()) {
        ui->lcdNumber_2->display(double_t(time/1000.0));
    }
    if(time!=ui->lcdNumber_3->intValue()){
        ui->lcdNumber_3->display(double_t(time/1000.0));
    }
}

void MainWindow::randomize() {
    sortVisualizer->randomize();
}

void MainWindow::numRectsChanged() {
    int numRects = ui->numberOfEle->currentText().toInt();
    sortVisualizer->changeNumberOfRectangles(numRects);
}
void MainWindow::showSortingPage()
{
    // Index 1 is the Sorting Visualizer Page
    ui->mainStackWidget->setCurrentIndex(1);
}

void MainWindow::showSelectionPage()
{
    // Index 0 is the Selection Page
    ui->mainStackWidget->setCurrentIndex(0);
}

void MainWindow::showGraphPage()
{
    ui->mainStackWidget->setCurrentIndex(2);
}

void MainWindow::showTreePage()
{
    ui->mainStackWidget->setCurrentIndex(3);
}

void MainWindow::enableEdgeCreationMode()
{
    graphVisualizer->setEdgeCreationMode(true);
    ui->inputNONButton->setDisabled(true);
}
void MainWindow::toggleEdgeValueMode()
{
    if (!graphVisualizer) return;
    bool isEnabled =graphVisualizer->isEdgeValueModeEnabled();
    graphVisualizer->setEdgeValueMode(!isEnabled);
    if (isEnabled)ui->createEdgeButton->setEnabled(true);
    else ui->createEdgeButton->setDisabled(true);
}

void MainWindow::handleEdgeValueInput(const QPoint &pos, int edgeIndex)
{
    if (!graphVisualizer) return;

    bool ok;
    int edgeValue=-1;
    if(ui->AlgoComboBox_2->currentIndex()!=2){
        edgeValue = QInputDialog::getInt(
            this,
            tr("Set Edge Weight"),
            tr("Enter weight for edge (index %1):").arg(edgeIndex),
            1,  // Default value
            1,  // Min value
            1000, // Max value
            1,
            &ok
            );

        if (ok) {
            graphVisualizer->setEdgeValueByIndex(edgeIndex, edgeValue);
        }
    }
}
void MainWindow::promptForSrcDest()
{
    bool ok;
    int srcId=-1;
    if(ui->AlgoComboBox_2->currentIndex()==0||ui->AlgoComboBox_2->currentIndex()==1){
    srcId = QInputDialog::getInt(
        this,
        tr("Source Node"),
        tr("Enter the ID of the Source Node (1 to %1):").arg(graphVisualizer->getNumberOfNodes()),
        1,
        1,
        graphVisualizer->getNumberOfNodes(), // Use helper to get max node ID
        1,
        &ok
        );

    if (!ok) return;
    }
    int destId=-1;
    if(ui->AlgoComboBox_2->currentIndex()==0){
    destId = QInputDialog::getInt(
        this,
        tr("Destination Node"),
        tr("Enter the ID of the Destination Node (1 to %1):").arg(graphVisualizer->getNumberOfNodes()),
        graphVisualizer->getNumberOfNodes(),
        1,
        graphVisualizer->getNumberOfNodes(),
        1,
        &ok
        );
    }
    if (ok) {
        int algorithmIndex = ui->AlgoComboBox_2->currentIndex();
        int interval = ui->spinBox_2->value();
        graphVisualizer->startAlgorithm(algorithmIndex, srcId, destId, interval);
    }
}

void MainWindow::enableTreeButtons()
{
    ui->startButton_3->setDisabled(false);
    ui->stopButton_3->setDisabled(true);
    ui->inputNONButton_2->setDisabled(false);
}

void MainWindow::disableTreeButtons()
{
    ui->startButton_3->setDisabled(true);
    ui->stopButton_3->setDisabled(false);
    ui->inputNONButton_2->setDisabled(true);
}
void MainWindow::disableGraphButtons() {
    ui->startButton_2->setDisabled(true);
    ui->stopButton_2->setDisabled(false);
    // Add other buttons specific to graph creation/setup
    ui->inputNONButton->setDisabled(true); // Number of Nodes
    ui->createEdgeButton->setDisabled(true);
    ui->edgeValueButton->setDisabled(true);
    // You might also need to disable AlgoComboBox_2
}

void MainWindow::enableGraphButtons() {
    ui->startButton_2->setDisabled(false);
    ui->stopButton_2->setDisabled(true);
    ui->inputNONButton->setDisabled(false);
    ui->createEdgeButton->setDisabled(false);
    ui->edgeValueButton->setDisabled(false);
}
MainWindow::~MainWindow()
{
    delete ui;
}
=======
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "sortvisualizer.h"
#include "graphvisualizer.h"
#include "treevisualizer.h"
#include <QtWidgets>
#include <QPalette>
#include <QInputDialog>
#include <QStringList>
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sortVisualizer=new SortVisualizer;
    graphVisualizer=new GraphVisualizer;
    treeVisualizer=new TreeVisualizer;

    QWidget *controlContainer = new QWidget;
    controlContainer->setLayout(ui->verticalLayout);
    QHBoxLayout *mainLayout = new QHBoxLayout;

    mainLayout->addWidget(sortVisualizer, 4);
    mainLayout->addWidget(controlContainer, 1);
    ui->sortingPage->setLayout(mainLayout);

    QWidget *controlContainer2 = new QWidget;
    controlContainer2->setLayout(ui->verticalLayout_2);
    QHBoxLayout *mainLayout2 = new QHBoxLayout;

    mainLayout2->addWidget(graphVisualizer, 4);
    mainLayout2->addWidget(controlContainer2, 1);
    ui->ShorthstPathPage->setLayout(mainLayout2);

    QWidget *controlContainer3 = new QWidget;
    controlContainer3->setLayout(ui->verticalLayout_3);
    QHBoxLayout *mainLayout3 = new QHBoxLayout;

    mainLayout3->addWidget(treeVisualizer, 4);
    mainLayout3->addWidget(controlContainer3, 1);
    ui->TreePage->setLayout(mainLayout3);

    setCentralWidget(ui->mainStackWidget);
    connect(sortVisualizer, &SortVisualizer::enableSortButtons, this, &MainWindow::enableSortButtons);
    connect(sortVisualizer, &SortVisualizer::disableButtons, this, &MainWindow::disableSortButtons);
    connect(ui->randomButton, &QPushButton::clicked, this, &MainWindow::randomize);
    connect(sortVisualizer, &SortVisualizer::setTimeElapsed, this, &MainWindow::setElapsedTime);
    connect(ui->numberOfEle, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::numRectsChanged);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::start);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stop);
    connect(ui->inputButton, &QPushButton::clicked, this, &MainWindow::promptForRectCount);
    connect(ui->inputHeightButton, &QPushButton::clicked, this, &MainWindow::promptForHeights);
    connect(ui->SortingButton, &QPushButton::clicked, this, &MainWindow::showSortingPage);
    connect(ui->ShorthestPathButton, &QPushButton::clicked, this, &MainWindow::showGraphPage);
    connect(ui->TreeButton, &QPushButton::clicked, this, &MainWindow::showTreePage);
    connect(ui->BackButton, &QPushButton::clicked, this, &MainWindow::showSelectionPage);
    connect(ui->BackButton_2, &QPushButton::clicked, this, &MainWindow::showSelectionPage);
    connect(ui->BackButton_3, &QPushButton::clicked, this, &MainWindow::showSelectionPage);
    connect(ui->inputNONButton, &QPushButton::clicked, this, &MainWindow::promptForNumberOfNodes);
    connect(ui->createEdgeButton, &QPushButton::clicked,this,&MainWindow::enableEdgeCreationMode);
    connect(ui->edgeValueButton, &QPushButton::clicked, this, &MainWindow::toggleEdgeValueMode);
    connect(graphVisualizer, &GraphVisualizer::requestEdgeValueInput, this, &MainWindow::handleEdgeValueInput);
    connect(ui->startButton_2, &QPushButton::clicked, this, &MainWindow::start);
    connect(ui->stopButton_2, &QPushButton::clicked, this, &MainWindow::stop);
    connect(graphVisualizer, &GraphVisualizer::enableGraphButtons, this, &MainWindow::enableGraphButtons);
    connect(graphVisualizer, &GraphVisualizer::disableGraphButtons, this, &MainWindow::disableGraphButtons);
    connect(ui->startButton_3, &QPushButton::clicked, this, &MainWindow::start);
    connect(ui->stopButton_3, &QPushButton::clicked, this, &MainWindow::stop);
    connect(ui->inputNONButton_2, &QPushButton::clicked, this, &MainWindow::promptForTreeNodes);
    connect(treeVisualizer, &TreeVisualizer::enableTreeButtons, this, &MainWindow::enableTreeButtons);
    connect(treeVisualizer, &TreeVisualizer::disableTreeButtons, this, &MainWindow::disableTreeButtons);
    connect(graphVisualizer, &GraphVisualizer::setTimeElapsed, this, &MainWindow::setElapsedTime);
    connect(treeVisualizer, &TreeVisualizer::setTimeElapsed, this, &MainWindow::setElapsedTime);
    ui->mainStackWidget->setCurrentIndex(0);
}

void MainWindow::promptForTreeNodes() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Tree Nodes"),
                                         tr("Enter integers (comma separated, max 50):"),
                                         QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
        QStringList parts = text.split(',', Qt::SkipEmptyParts);
        QList<int> values;
        for (int i = 0; i < qMin(parts.size(), 50); ++i) {
            bool conv;
            int val = parts[i].trimmed().toInt(&conv);
            if (conv) values.append(val);
        }
        treeVisualizer->constructTree(values);
    }
}

void MainWindow::promptForRectCount()
{
    if (!sortVisualizer) {
        qDebug() << "Error: SortVisualizer is null.";
        return;
    }

    bool ok;


    int currentCount = sortVisualizer->getNumberOfElements();


    int newCount = QInputDialog::getInt(
        this,
        tr("Set Rectangle Count"),
        tr("Number of Rectangles (2-1000):"),
        currentCount,
        2,
        1000,
        1,
        &ok
        );

    if (ok) {

        sortVisualizer->changeNumberOfRectangles(newCount);
        ui->numberOfEle->insertItem(0, QString::number(newCount), newCount);
        ui->numberOfEle->setCurrentIndex(0);
        // sortVisualizer->randomize();
        ui->lcdNumber->display(0);
        qDebug() << "Number of elements set to:" << newCount;
    }
}
// mainwindow.cpp

void MainWindow::promptForHeights()
{
    if (!sortVisualizer) {
        QMessageBox::critical(this, tr("Error"), tr("Visualizer is not initialized."));
        return;
    }
    bool ok;
    int expectedCount = sortVisualizer->getNumberOfElements();
    int maxBarHeight =height();
    QString heightsString = QInputDialog::getText(
        this,
        tr("Set Custom Array Heights"),
        tr("Enter %1 comma-separated heights (Max: %2):").arg(expectedCount).arg(maxBarHeight), // <-- Updated text
        QLineEdit::Normal,
        tr("e.g., 50, 100, 250... (Max: %1)").arg(maxBarHeight), // <-- Updated default text
        &ok
        );
    if (ok && !heightsString.isEmpty()) {
        QVector<int> customHeights;
        QStringList parts = heightsString.split(',', Qt::SkipEmptyParts);
        for (const QString &part : parts) {
            bool conversionOk;
            int height = part.trimmed().toInt(&conversionOk);

            // Validate: Must be a number, non-negative, AND within the pixel height limit
            if (conversionOk && height >= 0 && height <= maxBarHeight) { // <-- ADDED maxBarHeight check
                customHeights.append(height);
            } else {
                QMessageBox::warning(this, tr("Input Error"),
                                     tr("Invalid value or height (%1) is outside the valid range (0-%2).")
                                         .arg(height).arg(maxBarHeight));
                return;
            }
        }
        if (customHeights.count() != expectedCount) {
            QMessageBox::warning(this, tr("Input Error"),
                                 tr("Expected %1 heights, but received %2. The array size was not changed.")
                                     .arg(expectedCount).arg(customHeights.count())
                                 );
            return;
        }
        sortVisualizer->setCustomHeights(customHeights);
    }
}

void MainWindow::promptForNumberOfNodes()
{
    bool ok;
    int nodeCount = QInputDialog::getInt(
        this,
        tr("Set Number of Nodes"),
        tr("Enter number of nodes (1-50):"),
        5, // Default value
        1, // Min value
        50, // Max value
        1, // Step
        &ok
        );

    if (ok) {
        if (graphVisualizer) {
            graphVisualizer->setNumberOfNodes(nodeCount);
        }
    }
}
void MainWindow::start() {
    if (ui->mainStackWidget->currentIndex() == 2) {
        disableGraphButtons();
        //if (ui->AlgoComboBox_2->currentIndex() == 0) {
        promptForSrcDest();
        //}
        // else if (ui->AlgoComboBox_2->currentIndex()==1) {
        //     primsAlgorithm(srcId);
        // }


    } else if (ui->mainStackWidget->currentIndex() == 1) {
        if (!ui || !ui->AlgoComboBox || !ui->radioIncreasing || !ui->spinBox) {
            qInfo() << "ERROR: One or more UI elements are null!";
            return; // Prevents crash
        }
        algorithmIndex = ui->AlgoComboBox->currentIndex();
        bool increasing = ui->radioIncreasing->isChecked();
        int interval = ui->spinBox->value();
        int numberOfRects = ui->numberOfEle->currentText().toInt();
        disableSortButtons();
        //qInfo()<<increasing<<interval<<numberOfRects;
        sortVisualizer->startSort(algorithmIndex, increasing, interval, numberOfRects);
    }else if(ui->mainStackWidget->currentIndex()==3){
        disableTreeButtons();
        int interval = ui->spinBox_3->value();
        int algo = ui->AlgoComboBox_3->currentIndex();
        treeVisualizer->startAlgorithm(algo, interval);

    }

}

void MainWindow::stop() {
    if (ui->mainStackWidget->currentIndex() == 2) {
        graphVisualizer->stopAlgorithm();
    } else if (ui->mainStackWidget->currentIndex() == 1) {
        sortVisualizer->stopSort();
    }else if(ui->mainStackWidget->currentIndex()==3){
        treeVisualizer->stopAlgorithm();
    }
}

void MainWindow::disableSortButtons() {
    ui->startButton->setDisabled(true);
    ui->stopButton->setDisabled(false);
    ui->randomButton->setDisabled(true);
    ui->numberOfEle->setDisabled(true);
    ui->inputButton->setDisabled(true);
    ui->inputHeightButton->setDisabled(true);
}

void MainWindow::enableSortButtons() {
    ui->startButton->setDisabled(false);
    ui->stopButton->setDisabled(true);
    ui->randomButton->setDisabled(false);
    ui->numberOfEle->setDisabled(false);
    ui->inputButton->setDisabled(false);
    ui->inputHeightButton->setDisabled(false);
}

void MainWindow::setElapsedTime(int time) {
    if (time/1000 != ui->lcdNumber->intValue()) {
        ui->lcdNumber->display(time/1000);

    }
    if (time!= ui->lcdNumber_2->intValue()) {
        ui->lcdNumber_2->display(double_t(time/1000.0));
    }
    if(time!=ui->lcdNumber_3->intValue()){
        ui->lcdNumber_3->display(double_t(time/1000.0));
    }
}

void MainWindow::randomize() {
    sortVisualizer->randomize();
}

void MainWindow::numRectsChanged() {
    int numRects = ui->numberOfEle->currentText().toInt();
    sortVisualizer->changeNumberOfRectangles(numRects);
}
void MainWindow::showSortingPage()
{
    // Index 1 is the Sorting Visualizer Page
    ui->mainStackWidget->setCurrentIndex(1);
}

void MainWindow::showSelectionPage()
{
    // Index 0 is the Selection Page
    ui->mainStackWidget->setCurrentIndex(0);
}

void MainWindow::showGraphPage()
{
    ui->mainStackWidget->setCurrentIndex(2);
}

void MainWindow::showTreePage()
{
    ui->mainStackWidget->setCurrentIndex(3);
}

void MainWindow::enableEdgeCreationMode()
{
    graphVisualizer->setEdgeCreationMode(true);
    ui->inputNONButton->setDisabled(true);
}
void MainWindow::toggleEdgeValueMode()
{
    if (!graphVisualizer) return;
    bool isEnabled =graphVisualizer->isEdgeValueModeEnabled();
    graphVisualizer->setEdgeValueMode(!isEnabled);
    if (isEnabled)ui->createEdgeButton->setEnabled(true);
    else ui->createEdgeButton->setDisabled(true);
}

void MainWindow::handleEdgeValueInput(const QPoint &pos, int edgeIndex)
{
    if (!graphVisualizer) return;

    bool ok;
    int edgeValue=-1;
    if(ui->AlgoComboBox_2->currentIndex()!=2){
        edgeValue = QInputDialog::getInt(
            this,
            tr("Set Edge Weight"),
            tr("Enter weight for edge (index %1):").arg(edgeIndex),
            1,  // Default value
            1,  // Min value
            1000, // Max value
            1,
            &ok
            );

        if (ok) {
            graphVisualizer->setEdgeValueByIndex(edgeIndex, edgeValue);
        }
    }
}
void MainWindow::promptForSrcDest()
{
    bool ok;
    int srcId=-1;
    if(ui->AlgoComboBox_2->currentIndex()==0||ui->AlgoComboBox_2->currentIndex()==1){
    srcId = QInputDialog::getInt(
        this,
        tr("Source Node"),
        tr("Enter the ID of the Source Node (1 to %1):").arg(graphVisualizer->getNumberOfNodes()),
        1,
        1,
        graphVisualizer->getNumberOfNodes(), // Use helper to get max node ID
        1,
        &ok
        );

    if (!ok) return;
    }
    int destId=-1;
    if(ui->AlgoComboBox_2->currentIndex()==0){
    destId = QInputDialog::getInt(
        this,
        tr("Destination Node"),
        tr("Enter the ID of the Destination Node (1 to %1):").arg(graphVisualizer->getNumberOfNodes()),
        graphVisualizer->getNumberOfNodes(),
        1,
        graphVisualizer->getNumberOfNodes(),
        1,
        &ok
        );
    }
    if (ok) {
        int algorithmIndex = ui->AlgoComboBox_2->currentIndex();
        int interval = ui->spinBox_2->value();
        graphVisualizer->startAlgorithm(algorithmIndex, srcId, destId, interval);
    }
}

void MainWindow::enableTreeButtons()
{
    ui->startButton_3->setDisabled(false);
    ui->stopButton_3->setDisabled(true);
    ui->inputNONButton_2->setDisabled(false);
}

void MainWindow::disableTreeButtons()
{
    ui->startButton_3->setDisabled(true);
    ui->stopButton_3->setDisabled(false);
    ui->inputNONButton_2->setDisabled(true);
}
void MainWindow::disableGraphButtons() {
    ui->startButton_2->setDisabled(true);
    ui->stopButton_2->setDisabled(false);
    // Add other buttons specific to graph creation/setup
    ui->inputNONButton->setDisabled(true); // Number of Nodes
    ui->createEdgeButton->setDisabled(true);
    ui->edgeValueButton->setDisabled(true);
    // You might also need to disable AlgoComboBox_2
}

void MainWindow::enableGraphButtons() {
    ui->startButton_2->setDisabled(false);
    ui->stopButton_2->setDisabled(true);
    ui->inputNONButton->setDisabled(false);
    ui->createEdgeButton->setDisabled(false);
    ui->edgeValueButton->setDisabled(false);
}
MainWindow::~MainWindow()
{
    delete ui;
}
>>>>>>> 04a9751158f621a6df50fbe7c01dfb93f96e7baa
