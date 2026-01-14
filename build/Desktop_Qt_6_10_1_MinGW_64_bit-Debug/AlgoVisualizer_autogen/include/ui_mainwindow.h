/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *lbAlgos;
    QComboBox *AlgoComboBox;
    QRadioButton *radioIncreasing;
    QRadioButton *radioDecreasing;
    QLabel *lbAlgos_2;
    QSpinBox *spinBox;
    QLabel *lbAlgos_3;
    QComboBox *numberOfEle;
    QPushButton *inputButton;
    QPushButton *randomButton;
    QPushButton *inputHeightButton;
    QPushButton *startButton;
    QPushButton *stopButton;
    QLCDNumber *lcdNumber;
    QLabel *lbRandom;
    QPushButton *BackButton;
    QStackedWidget *mainStackWidget;
    QWidget *SelectionPage;
    QGridLayout *gridLayout_2;
    QPushButton *ShorthestPathButton;
    QSpacerItem *verticalSpacer_6;
    QPushButton *SortingButton;
    QSpacerItem *verticalSpacer_4;
    QLabel *label;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_7;
    QPushButton *TreeButton;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_2;
    QWidget *sortingPage;
    QWidget *ShorthstPathPage;
    QWidget *TreePage;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *lbAlgos_4;
    QComboBox *AlgoComboBox_2;
    QLabel *lbAlgos_5;
    QSpinBox *spinBox_2;
    QLabel *lbRandom_2;
    QPushButton *inputNONButton;
    QPushButton *createEdgeButton;
    QPushButton *edgeValueButton;
    QPushButton *startButton_2;
    QPushButton *stopButton_2;
    QLCDNumber *lcdNumber_2;
    QPushButton *BackButton_2;
    QWidget *layoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *lbAlgos_6;
    QComboBox *AlgoComboBox_3;
    QLabel *lbAlgos_7;
    QSpinBox *spinBox_3;
    QPushButton *inputNONButton_2;
    QLabel *lbRandom_3;
    QPushButton *startButton_3;
    QPushButton *stopButton_3;
    QLCDNumber *lcdNumber_3;
    QPushButton *BackButton_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1066, 600);
        QFont font;
        font.setPointSize(11);
        MainWindow->setFont(font);
        MainWindow->setIconSize(QSize(50, 50));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMaximumSize(QSize(800, 16777215));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(70, 330, 143, 111));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lbAlgos = new QLabel(layoutWidget);
        lbAlgos->setObjectName("lbAlgos");
        lbAlgos->setFont(font);

        verticalLayout->addWidget(lbAlgos);

        AlgoComboBox = new QComboBox(layoutWidget);
        AlgoComboBox->addItem(QString());
        AlgoComboBox->addItem(QString());
        AlgoComboBox->addItem(QString());
        AlgoComboBox->addItem(QString());
        AlgoComboBox->addItem(QString());
        AlgoComboBox->setObjectName("AlgoComboBox");
        AlgoComboBox->setFont(font);

        verticalLayout->addWidget(AlgoComboBox);

        radioIncreasing = new QRadioButton(layoutWidget);
        radioIncreasing->setObjectName("radioIncreasing");
        radioIncreasing->setFont(font);
        radioIncreasing->setChecked(true);

        verticalLayout->addWidget(radioIncreasing);

        radioDecreasing = new QRadioButton(layoutWidget);
        radioDecreasing->setObjectName("radioDecreasing");
        radioDecreasing->setFont(font);

        verticalLayout->addWidget(radioDecreasing);

        lbAlgos_2 = new QLabel(layoutWidget);
        lbAlgos_2->setObjectName("lbAlgos_2");
        lbAlgos_2->setFont(font);

        verticalLayout->addWidget(lbAlgos_2);

        spinBox = new QSpinBox(layoutWidget);
        spinBox->setObjectName("spinBox");
        spinBox->setMinimum(1);
        spinBox->setMaximum(5000);

        verticalLayout->addWidget(spinBox);

        lbAlgos_3 = new QLabel(layoutWidget);
        lbAlgos_3->setObjectName("lbAlgos_3");
        lbAlgos_3->setFont(font);

        verticalLayout->addWidget(lbAlgos_3);

        numberOfEle = new QComboBox(layoutWidget);
        numberOfEle->addItem(QString());
        numberOfEle->addItem(QString());
        numberOfEle->addItem(QString());
        numberOfEle->addItem(QString());
        numberOfEle->addItem(QString());
        numberOfEle->addItem(QString());
        numberOfEle->addItem(QString());
        numberOfEle->addItem(QString());
        numberOfEle->setObjectName("numberOfEle");

        verticalLayout->addWidget(numberOfEle);

        inputButton = new QPushButton(layoutWidget);
        inputButton->setObjectName("inputButton");

        verticalLayout->addWidget(inputButton);

        randomButton = new QPushButton(layoutWidget);
        randomButton->setObjectName("randomButton");

        verticalLayout->addWidget(randomButton);

        inputHeightButton = new QPushButton(layoutWidget);
        inputHeightButton->setObjectName("inputHeightButton");

        verticalLayout->addWidget(inputHeightButton);

        startButton = new QPushButton(layoutWidget);
        startButton->setObjectName("startButton");

        verticalLayout->addWidget(startButton);

        stopButton = new QPushButton(layoutWidget);
        stopButton->setObjectName("stopButton");

        verticalLayout->addWidget(stopButton);

        lcdNumber = new QLCDNumber(layoutWidget);
        lcdNumber->setObjectName("lcdNumber");
        lcdNumber->setContextMenuPolicy(Qt::ContextMenuPolicy::DefaultContextMenu);
        lcdNumber->setFrameShape(QFrame::Shape::StyledPanel);
        lcdNumber->setFrameShadow(QFrame::Shadow::Plain);
        lcdNumber->setSmallDecimalPoint(true);
        lcdNumber->setDigitCount(9);
        lcdNumber->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        verticalLayout->addWidget(lcdNumber);

        lbRandom = new QLabel(layoutWidget);
        lbRandom->setObjectName("lbRandom");
        lbRandom->setFont(font);
        lbRandom->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        lbRandom->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(lbRandom);

        BackButton = new QPushButton(layoutWidget);
        BackButton->setObjectName("BackButton");

        verticalLayout->addWidget(BackButton);

        mainStackWidget = new QStackedWidget(centralwidget);
        mainStackWidget->setObjectName("mainStackWidget");
        mainStackWidget->setGeometry(QRect(60, 20, 511, 251));
        SelectionPage = new QWidget();
        SelectionPage->setObjectName("SelectionPage");
        gridLayout_2 = new QGridLayout(SelectionPage);
        gridLayout_2->setObjectName("gridLayout_2");
        ShorthestPathButton = new QPushButton(SelectionPage);
        ShorthestPathButton->setObjectName("ShorthestPathButton");
        ShorthestPathButton->setMinimumSize(QSize(150, 50));
        QFont font1;
        font1.setPointSize(18);
        font1.setBold(true);
        ShorthestPathButton->setFont(font1);
        ShorthestPathButton->setIconSize(QSize(50, 50));

        gridLayout_2->addWidget(ShorthestPathButton, 8, 4, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_6, 0, 4, 1, 1);

        SortingButton = new QPushButton(SelectionPage);
        SortingButton->setObjectName("SortingButton");
        SortingButton->setMinimumSize(QSize(150, 50));
        SortingButton->setFont(font1);
        SortingButton->setIconSize(QSize(50, 50));

        gridLayout_2->addWidget(SortingButton, 4, 4, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 128, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_4, 11, 4, 1, 1);

        label = new QLabel(SelectionPage);
        label->setObjectName("label");
        QFont font2;
        font2.setPointSize(84);
        font2.setBold(true);
        font2.setItalic(true);
        label->setFont(font2);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_2->addWidget(label, 2, 0, 1, 7);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 3, 4, 1, 1);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_7, 1, 4, 1, 1);

        TreeButton = new QPushButton(SelectionPage);
        TreeButton->setObjectName("TreeButton");
        TreeButton->setMinimumSize(QSize(150, 50));
        TreeButton->setFont(font1);
        TreeButton->setIconSize(QSize(50, 50));

        gridLayout_2->addWidget(TreeButton, 10, 4, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(70, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 10, 3, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(110, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_8, 4, 3, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(70, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_9, 8, 3, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(110, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 4, 6, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(69, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 8, 6, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(69, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 10, 6, 1, 1);

        mainStackWidget->addWidget(SelectionPage);
        sortingPage = new QWidget();
        sortingPage->setObjectName("sortingPage");
        mainStackWidget->addWidget(sortingPage);
        ShorthstPathPage = new QWidget();
        ShorthstPathPage->setObjectName("ShorthstPathPage");
        mainStackWidget->addWidget(ShorthstPathPage);
        TreePage = new QWidget();
        TreePage->setObjectName("TreePage");
        mainStackWidget->addWidget(TreePage);
        layoutWidget_2 = new QWidget(centralwidget);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(300, 320, 175, 211));
        verticalLayout_2 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        lbAlgos_4 = new QLabel(layoutWidget_2);
        lbAlgos_4->setObjectName("lbAlgos_4");
        lbAlgos_4->setFont(font);

        verticalLayout_2->addWidget(lbAlgos_4);

        AlgoComboBox_2 = new QComboBox(layoutWidget_2);
        AlgoComboBox_2->addItem(QString());
        AlgoComboBox_2->addItem(QString());
        AlgoComboBox_2->addItem(QString());
        AlgoComboBox_2->setObjectName("AlgoComboBox_2");
        AlgoComboBox_2->setFont(font);

        verticalLayout_2->addWidget(AlgoComboBox_2);

        lbAlgos_5 = new QLabel(layoutWidget_2);
        lbAlgos_5->setObjectName("lbAlgos_5");
        lbAlgos_5->setFont(font);

        verticalLayout_2->addWidget(lbAlgos_5);

        spinBox_2 = new QSpinBox(layoutWidget_2);
        spinBox_2->setObjectName("spinBox_2");
        spinBox_2->setMinimum(100);
        spinBox_2->setMaximum(1000000);

        verticalLayout_2->addWidget(spinBox_2);

        lbRandom_2 = new QLabel(layoutWidget_2);
        lbRandom_2->setObjectName("lbRandom_2");
        lbRandom_2->setFont(font);
        lbRandom_2->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        lbRandom_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(lbRandom_2);

        inputNONButton = new QPushButton(layoutWidget_2);
        inputNONButton->setObjectName("inputNONButton");

        verticalLayout_2->addWidget(inputNONButton);

        createEdgeButton = new QPushButton(layoutWidget_2);
        createEdgeButton->setObjectName("createEdgeButton");

        verticalLayout_2->addWidget(createEdgeButton);

        edgeValueButton = new QPushButton(layoutWidget_2);
        edgeValueButton->setObjectName("edgeValueButton");

        verticalLayout_2->addWidget(edgeValueButton);

        startButton_2 = new QPushButton(layoutWidget_2);
        startButton_2->setObjectName("startButton_2");

        verticalLayout_2->addWidget(startButton_2);

        stopButton_2 = new QPushButton(layoutWidget_2);
        stopButton_2->setObjectName("stopButton_2");

        verticalLayout_2->addWidget(stopButton_2);

        lcdNumber_2 = new QLCDNumber(layoutWidget_2);
        lcdNumber_2->setObjectName("lcdNumber_2");
        lcdNumber_2->setContextMenuPolicy(Qt::ContextMenuPolicy::DefaultContextMenu);
        lcdNumber_2->setFrameShape(QFrame::Shape::StyledPanel);
        lcdNumber_2->setLineWidth(1);
        lcdNumber_2->setSmallDecimalPoint(true);
        lcdNumber_2->setDigitCount(5);
        lcdNumber_2->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        verticalLayout_2->addWidget(lcdNumber_2);

        BackButton_2 = new QPushButton(layoutWidget_2);
        BackButton_2->setObjectName("BackButton_2");

        verticalLayout_2->addWidget(BackButton_2);

        layoutWidget_3 = new QWidget(centralwidget);
        layoutWidget_3->setObjectName("layoutWidget_3");
        layoutWidget_3->setGeometry(QRect(500, 320, 201, 308));
        verticalLayout_3 = new QVBoxLayout(layoutWidget_3);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        lbAlgos_6 = new QLabel(layoutWidget_3);
        lbAlgos_6->setObjectName("lbAlgos_6");
        lbAlgos_6->setFont(font);

        verticalLayout_3->addWidget(lbAlgos_6);

        AlgoComboBox_3 = new QComboBox(layoutWidget_3);
        AlgoComboBox_3->addItem(QString());
        AlgoComboBox_3->addItem(QString());
        AlgoComboBox_3->addItem(QString());
        AlgoComboBox_3->setObjectName("AlgoComboBox_3");
        AlgoComboBox_3->setFont(font);

        verticalLayout_3->addWidget(AlgoComboBox_3);

        lbAlgos_7 = new QLabel(layoutWidget_3);
        lbAlgos_7->setObjectName("lbAlgos_7");
        lbAlgos_7->setFont(font);

        verticalLayout_3->addWidget(lbAlgos_7);

        spinBox_3 = new QSpinBox(layoutWidget_3);
        spinBox_3->setObjectName("spinBox_3");
        spinBox_3->setMinimum(100);
        spinBox_3->setMaximum(1000000);

        verticalLayout_3->addWidget(spinBox_3);

        inputNONButton_2 = new QPushButton(layoutWidget_3);
        inputNONButton_2->setObjectName("inputNONButton_2");

        verticalLayout_3->addWidget(inputNONButton_2);

        lbRandom_3 = new QLabel(layoutWidget_3);
        lbRandom_3->setObjectName("lbRandom_3");
        lbRandom_3->setFont(font);
        lbRandom_3->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        lbRandom_3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(lbRandom_3);

        startButton_3 = new QPushButton(layoutWidget_3);
        startButton_3->setObjectName("startButton_3");

        verticalLayout_3->addWidget(startButton_3);

        stopButton_3 = new QPushButton(layoutWidget_3);
        stopButton_3->setObjectName("stopButton_3");

        verticalLayout_3->addWidget(stopButton_3);

        lcdNumber_3 = new QLCDNumber(layoutWidget_3);
        lcdNumber_3->setObjectName("lcdNumber_3");
        lcdNumber_3->setContextMenuPolicy(Qt::ContextMenuPolicy::DefaultContextMenu);
        lcdNumber_3->setFrameShape(QFrame::Shape::StyledPanel);
        lcdNumber_3->setLineWidth(1);
        lcdNumber_3->setSmallDecimalPoint(true);
        lcdNumber_3->setDigitCount(6);
        lcdNumber_3->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

        verticalLayout_3->addWidget(lcdNumber_3);

        BackButton_3 = new QPushButton(layoutWidget_3);
        BackButton_3->setObjectName("BackButton_3");

        verticalLayout_3->addWidget(BackButton_3);

        MainWindow->setCentralWidget(centralwidget);
#if QT_CONFIG(shortcut)
        lbRandom->setBuddy(lbRandom);
        lbRandom_2->setBuddy(lbRandom);
        lbRandom_3->setBuddy(lbRandom);
#endif // QT_CONFIG(shortcut)
        QWidget::setTabOrder(AlgoComboBox, radioDecreasing);
        QWidget::setTabOrder(radioDecreasing, radioIncreasing);
        QWidget::setTabOrder(radioIncreasing, numberOfEle);

        retranslateUi(MainWindow);

        AlgoComboBox->setCurrentIndex(0);
        numberOfEle->setCurrentIndex(0);
        mainStackWidget->setCurrentIndex(0);
        AlgoComboBox_2->setCurrentIndex(0);
        AlgoComboBox_3->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lbAlgos->setText(QCoreApplication::translate("MainWindow", "Algorithms:", nullptr));
        AlgoComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Selection Sort", nullptr));
        AlgoComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Bubble Sort", nullptr));
        AlgoComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Insertion Sort", nullptr));
        AlgoComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "Merge Sort", nullptr));
        AlgoComboBox->setItemText(4, QCoreApplication::translate("MainWindow", "Quick Sort", nullptr));

        radioIncreasing->setText(QCoreApplication::translate("MainWindow", "Increasing", nullptr));
        radioDecreasing->setText(QCoreApplication::translate("MainWindow", "Decreasing", nullptr));
        lbAlgos_2->setText(QCoreApplication::translate("MainWindow", "Interval[ms]:", nullptr));
        lbAlgos_3->setText(QCoreApplication::translate("MainWindow", "Number Of Elements:", nullptr));
        numberOfEle->setItemText(0, QCoreApplication::translate("MainWindow", "10", nullptr));
        numberOfEle->setItemText(1, QCoreApplication::translate("MainWindow", "50", nullptr));
        numberOfEle->setItemText(2, QCoreApplication::translate("MainWindow", "100", nullptr));
        numberOfEle->setItemText(3, QCoreApplication::translate("MainWindow", "150", nullptr));
        numberOfEle->setItemText(4, QCoreApplication::translate("MainWindow", "20", nullptr));
        numberOfEle->setItemText(5, QCoreApplication::translate("MainWindow", "30", nullptr));
        numberOfEle->setItemText(6, QCoreApplication::translate("MainWindow", "40", nullptr));
        numberOfEle->setItemText(7, QCoreApplication::translate("MainWindow", "5", nullptr));

        inputButton->setText(QCoreApplication::translate("MainWindow", " Input NOE", nullptr));
        randomButton->setText(QCoreApplication::translate("MainWindow", "Random size", nullptr));
        inputHeightButton->setText(QCoreApplication::translate("MainWindow", "Input Size", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        stopButton->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        lbRandom->setText(QString());
        BackButton->setText(QCoreApplication::translate("MainWindow", "Back To Menu", nullptr));
        ShorthestPathButton->setText(QCoreApplication::translate("MainWindow", "Graph", nullptr));
        SortingButton->setText(QCoreApplication::translate("MainWindow", "Sorting", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Algorithm Visualizer", nullptr));
        TreeButton->setText(QCoreApplication::translate("MainWindow", "Tree", nullptr));
        lbAlgos_4->setText(QCoreApplication::translate("MainWindow", "Algorithms:", nullptr));
        AlgoComboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "Dijkstra", nullptr));
        AlgoComboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "Prim", nullptr));
        AlgoComboBox_2->setItemText(2, QCoreApplication::translate("MainWindow", "Tarjan", nullptr));

        lbAlgos_5->setText(QCoreApplication::translate("MainWindow", "Interval[ms]:", nullptr));
        lbRandom_2->setText(QString());
        inputNONButton->setText(QCoreApplication::translate("MainWindow", "Input Number Of Nodes", nullptr));
        createEdgeButton->setText(QCoreApplication::translate("MainWindow", "Create Edge", nullptr));
        edgeValueButton->setText(QCoreApplication::translate("MainWindow", "Edge Value", nullptr));
        startButton_2->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        stopButton_2->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        BackButton_2->setText(QCoreApplication::translate("MainWindow", "Back To Menu", nullptr));
        lbAlgos_6->setText(QCoreApplication::translate("MainWindow", "Algorithms:", nullptr));
        AlgoComboBox_3->setItemText(0, QCoreApplication::translate("MainWindow", "InOrder", nullptr));
        AlgoComboBox_3->setItemText(1, QCoreApplication::translate("MainWindow", "PreOrder", nullptr));
        AlgoComboBox_3->setItemText(2, QCoreApplication::translate("MainWindow", "PostOrder", nullptr));

        lbAlgos_7->setText(QCoreApplication::translate("MainWindow", "Interval[ms]:", nullptr));
        inputNONButton_2->setText(QCoreApplication::translate("MainWindow", "Input Nodes", nullptr));
        lbRandom_3->setText(QString());
        startButton_3->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        stopButton_3->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        BackButton_3->setText(QCoreApplication::translate("MainWindow", "Back To Menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
