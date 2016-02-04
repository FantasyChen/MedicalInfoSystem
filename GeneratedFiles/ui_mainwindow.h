/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_mainwindowClass
{
public:
    QAction *actionOpenFile;
    QAction *actionExit;
    QAction *actionSave;
    QAction *actionAbout;
    QWidget *centralWidget;
    QTableWidget *infoTable;
    QGroupBox *groupBox;
    QCheckBox *ThickModeBox;
    QCheckBox *ResliceModeBox;
    QCheckBox *ColorModeBox;
    QPushButton *resetButton;
    QPushButton *addSeedButton;
    QLabel *label;
    QTextBrowser *seedTextBrowser;
    QPushButton *removeSeedButton;
    QGroupBox *SegmentationGroupBox;
    QRadioButton *regionRadioButton;
    QRadioButton *thresholdRadioButton;
    QPushButton *segStartButton;
    QGroupBox *groupBox_2;
    QVTKWidget *qvtkWidget_4;
    QVTKWidget *qvtkWidget_3;
    QVTKWidget *qvtkWidget;
    QVTKWidget *qvtkWidget_2;
    QGroupBox *groupBox_3;
    QRadioButton *pointRadioButton;
    QRadioButton *boxStencilRadioButton;
    QPushButton *segStartButton_2;
    QRadioButton *ElliStencilRadioButton;
    QTableWidget *stateTable;
    QCommandLinkButton *calcHerterButton;
    QMenuBar *menuBar;
    QMenu *menuStart;
    QMenu *menuAbout;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *mainwindowClass)
    {
        if (mainwindowClass->objectName().isEmpty())
            mainwindowClass->setObjectName(QStringLiteral("mainwindowClass"));
        mainwindowClass->resize(1596, 900);
        mainwindowClass->setMinimumSize(QSize(1596, 900));
        mainwindowClass->setMaximumSize(QSize(1596, 900));
        QIcon icon;
        icon.addFile(QStringLiteral("Resources/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        mainwindowClass->setWindowIcon(icon);
        actionOpenFile = new QAction(mainwindowClass);
        actionOpenFile->setObjectName(QStringLiteral("actionOpenFile"));
        actionOpenFile->setEnabled(true);
        actionExit = new QAction(mainwindowClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionSave = new QAction(mainwindowClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionAbout = new QAction(mainwindowClass);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        centralWidget = new QWidget(mainwindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        infoTable = new QTableWidget(centralWidget);
        if (infoTable->columnCount() < 1)
            infoTable->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        infoTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (infoTable->rowCount() < 9)
            infoTable->setRowCount(9);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        infoTable->setVerticalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        infoTable->setVerticalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        infoTable->setVerticalHeaderItem(2, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        infoTable->setVerticalHeaderItem(3, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        infoTable->setVerticalHeaderItem(4, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        infoTable->setVerticalHeaderItem(5, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        infoTable->setVerticalHeaderItem(6, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        infoTable->setVerticalHeaderItem(7, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        infoTable->setVerticalHeaderItem(8, __qtablewidgetitem9);
        infoTable->setObjectName(QStringLiteral("infoTable"));
        infoTable->setGeometry(QRect(40, 30, 291, 301));
        infoTable->horizontalHeader()->setDefaultSectionSize(200);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(1260, 30, 161, 91));
        ThickModeBox = new QCheckBox(groupBox);
        ThickModeBox->setObjectName(QStringLiteral("ThickModeBox"));
        ThickModeBox->setGeometry(QRect(20, 20, 81, 16));
        ThickModeBox->setTristate(false);
        ResliceModeBox = new QCheckBox(groupBox);
        ResliceModeBox->setObjectName(QStringLiteral("ResliceModeBox"));
        ResliceModeBox->setGeometry(QRect(20, 40, 111, 16));
        ColorModeBox = new QCheckBox(groupBox);
        ColorModeBox->setObjectName(QStringLiteral("ColorModeBox"));
        ColorModeBox->setGeometry(QRect(20, 60, 101, 16));
        resetButton = new QPushButton(centralWidget);
        resetButton->setObjectName(QStringLiteral("resetButton"));
        resetButton->setGeometry(QRect(1450, 50, 75, 23));
        addSeedButton = new QPushButton(centralWidget);
        addSeedButton->setObjectName(QStringLiteral("addSeedButton"));
        addSeedButton->setGeometry(QRect(1260, 140, 131, 23));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(1260, 170, 101, 16));
        seedTextBrowser = new QTextBrowser(centralWidget);
        seedTextBrowser->setObjectName(QStringLiteral("seedTextBrowser"));
        seedTextBrowser->setGeometry(QRect(1270, 190, 256, 192));
        removeSeedButton = new QPushButton(centralWidget);
        removeSeedButton->setObjectName(QStringLiteral("removeSeedButton"));
        removeSeedButton->setGeometry(QRect(1400, 140, 131, 23));
        SegmentationGroupBox = new QGroupBox(centralWidget);
        SegmentationGroupBox->setObjectName(QStringLiteral("SegmentationGroupBox"));
        SegmentationGroupBox->setGeometry(QRect(1270, 400, 251, 161));
        regionRadioButton = new QRadioButton(SegmentationGroupBox);
        regionRadioButton->setObjectName(QStringLiteral("regionRadioButton"));
        regionRadioButton->setGeometry(QRect(20, 30, 141, 21));
        regionRadioButton->setChecked(true);
        thresholdRadioButton = new QRadioButton(SegmentationGroupBox);
        thresholdRadioButton->setObjectName(QStringLiteral("thresholdRadioButton"));
        thresholdRadioButton->setGeometry(QRect(20, 70, 101, 16));
        segStartButton = new QPushButton(SegmentationGroupBox);
        segStartButton->setObjectName(QStringLiteral("segStartButton"));
        segStartButton->setGeometry(QRect(40, 110, 131, 23));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(440, 20, 781, 851));
        qvtkWidget_4 = new QVTKWidget(groupBox_2);
        qvtkWidget_4->setObjectName(QStringLiteral("qvtkWidget_4"));
        qvtkWidget_4->setGeometry(QRect(400, 430, 351, 381));
        qvtkWidget_3 = new QVTKWidget(groupBox_2);
        qvtkWidget_3->setObjectName(QStringLiteral("qvtkWidget_3"));
        qvtkWidget_3->setGeometry(QRect(20, 430, 351, 381));
        qvtkWidget = new QVTKWidget(groupBox_2);
        qvtkWidget->setObjectName(QStringLiteral("qvtkWidget"));
        qvtkWidget->setGeometry(QRect(20, 30, 351, 381));
        qvtkWidget_2 = new QVTKWidget(groupBox_2);
        qvtkWidget_2->setObjectName(QStringLiteral("qvtkWidget_2"));
        qvtkWidget_2->setGeometry(QRect(400, 30, 351, 381));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(1270, 590, 251, 201));
        pointRadioButton = new QRadioButton(groupBox_3);
        pointRadioButton->setObjectName(QStringLiteral("pointRadioButton"));
        pointRadioButton->setGeometry(QRect(20, 30, 141, 21));
        pointRadioButton->setChecked(false);
        boxStencilRadioButton = new QRadioButton(groupBox_3);
        boxStencilRadioButton->setObjectName(QStringLiteral("boxStencilRadioButton"));
        boxStencilRadioButton->setGeometry(QRect(20, 70, 141, 21));
        boxStencilRadioButton->setChecked(false);
        segStartButton_2 = new QPushButton(groupBox_3);
        segStartButton_2->setObjectName(QStringLiteral("segStartButton_2"));
        segStartButton_2->setGeometry(QRect(50, 150, 131, 23));
        ElliStencilRadioButton = new QRadioButton(groupBox_3);
        ElliStencilRadioButton->setObjectName(QStringLiteral("ElliStencilRadioButton"));
        ElliStencilRadioButton->setGeometry(QRect(20, 110, 141, 21));
        ElliStencilRadioButton->setChecked(true);
        stateTable = new QTableWidget(centralWidget);
        if (stateTable->columnCount() < 1)
            stateTable->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        stateTable->setHorizontalHeaderItem(0, __qtablewidgetitem10);
        if (stateTable->rowCount() < 8)
            stateTable->setRowCount(8);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        stateTable->setVerticalHeaderItem(0, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        stateTable->setVerticalHeaderItem(1, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        stateTable->setVerticalHeaderItem(2, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        stateTable->setVerticalHeaderItem(3, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        stateTable->setVerticalHeaderItem(4, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        stateTable->setVerticalHeaderItem(5, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        stateTable->setVerticalHeaderItem(6, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        stateTable->setVerticalHeaderItem(7, __qtablewidgetitem18);
        stateTable->setObjectName(QStringLiteral("stateTable"));
        stateTable->setGeometry(QRect(40, 420, 331, 271));
        stateTable->horizontalHeader()->setDefaultSectionSize(200);
        calcHerterButton = new QCommandLinkButton(centralWidget);
        calcHerterButton->setObjectName(QStringLiteral("calcHerterButton"));
        calcHerterButton->setGeometry(QRect(60, 730, 251, 41));
        calcHerterButton->setLayoutDirection(Qt::LeftToRight);
        mainwindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(mainwindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1596, 23));
        menuStart = new QMenu(menuBar);
        menuStart->setObjectName(QStringLiteral("menuStart"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        mainwindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(mainwindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainwindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(mainwindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        mainwindowClass->setStatusBar(statusBar);

        menuBar->addAction(menuStart->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuStart->addAction(actionOpenFile);
        menuStart->addAction(actionSave);
        menuStart->addAction(actionExit);
        menuAbout->addAction(actionAbout);

        retranslateUi(mainwindowClass);

        QMetaObject::connectSlotsByName(mainwindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *mainwindowClass)
    {
        mainwindowClass->setWindowTitle(QApplication::translate("mainwindowClass", "Medical Image Computing System", 0));
        actionOpenFile->setText(QApplication::translate("mainwindowClass", "Open Files", 0));
        actionOpenFile->setShortcut(QApplication::translate("mainwindowClass", "Ctrl+O", 0));
        actionExit->setText(QApplication::translate("mainwindowClass", "Exit", 0));
        actionSave->setText(QApplication::translate("mainwindowClass", "Save As", 0));
        actionSave->setShortcut(QApplication::translate("mainwindowClass", "Ctrl+S", 0));
        actionAbout->setText(QApplication::translate("mainwindowClass", "About", 0));
        actionAbout->setShortcut(QApplication::translate("mainwindowClass", "Ctrl+A", 0));
        QTableWidgetItem *___qtablewidgetitem = infoTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("mainwindowClass", "Value", 0));
        QTableWidgetItem *___qtablewidgetitem1 = infoTable->verticalHeaderItem(0);
        ___qtablewidgetitem1->setText(QApplication::translate("mainwindowClass", "patientName", 0));
        QTableWidgetItem *___qtablewidgetitem2 = infoTable->verticalHeaderItem(1);
        ___qtablewidgetitem2->setText(QApplication::translate("mainwindowClass", "patientID", 0));
        QTableWidgetItem *___qtablewidgetitem3 = infoTable->verticalHeaderItem(2);
        ___qtablewidgetitem3->setText(QApplication::translate("mainwindowClass", "patientSex", 0));
        QTableWidgetItem *___qtablewidgetitem4 = infoTable->verticalHeaderItem(3);
        ___qtablewidgetitem4->setText(QApplication::translate("mainwindowClass", "patientAge", 0));
        QTableWidgetItem *___qtablewidgetitem5 = infoTable->verticalHeaderItem(4);
        ___qtablewidgetitem5->setText(QApplication::translate("mainwindowClass", "studyDate", 0));
        QTableWidgetItem *___qtablewidgetitem6 = infoTable->verticalHeaderItem(5);
        ___qtablewidgetitem6->setText(QApplication::translate("mainwindowClass", "modality", 0));
        QTableWidgetItem *___qtablewidgetitem7 = infoTable->verticalHeaderItem(6);
        ___qtablewidgetitem7->setText(QApplication::translate("mainwindowClass", "manufacturer", 0));
        QTableWidgetItem *___qtablewidgetitem8 = infoTable->verticalHeaderItem(7);
        ___qtablewidgetitem8->setText(QApplication::translate("mainwindowClass", "institution", 0));
        QTableWidgetItem *___qtablewidgetitem9 = infoTable->verticalHeaderItem(8);
        ___qtablewidgetitem9->setText(QApplication::translate("mainwindowClass", "model", 0));
        groupBox->setTitle(QApplication::translate("mainwindowClass", "Mode Selection", 0));
        ThickModeBox->setText(QApplication::translate("mainwindowClass", "Thick Mode", 0));
        ResliceModeBox->setText(QApplication::translate("mainwindowClass", "Reslice Mode", 0));
        ColorModeBox->setText(QApplication::translate("mainwindowClass", "Color Mode", 0));
        resetButton->setText(QApplication::translate("mainwindowClass", "Reset", 0));
        addSeedButton->setText(QApplication::translate("mainwindowClass", "Add Point", 0));
        label->setText(QApplication::translate("mainwindowClass", "Current Point:", 0));
        removeSeedButton->setText(QApplication::translate("mainwindowClass", "Remove Point", 0));
        SegmentationGroupBox->setTitle(QApplication::translate("mainwindowClass", "Auto-Segmentation Toolbox", 0));
        regionRadioButton->setText(QApplication::translate("mainwindowClass", "Growing Region", 0));
        thresholdRadioButton->setText(QApplication::translate("mainwindowClass", "Thresholding", 0));
        segStartButton->setText(QApplication::translate("mainwindowClass", "Start Segmentation", 0));
        groupBox_2->setTitle(QApplication::translate("mainwindowClass", "Viewer", 0));
        groupBox_3->setTitle(QApplication::translate("mainwindowClass", "Mannual-Segmentation Toolbox", 0));
        pointRadioButton->setText(QApplication::translate("mainwindowClass", "Point By Point", 0));
        boxStencilRadioButton->setText(QApplication::translate("mainwindowClass", "Box Stencil", 0));
        segStartButton_2->setText(QApplication::translate("mainwindowClass", "Start Segmentation", 0));
        ElliStencilRadioButton->setText(QApplication::translate("mainwindowClass", "Ellipsoid Stencil", 0));
        QTableWidgetItem *___qtablewidgetitem10 = stateTable->horizontalHeaderItem(0);
        ___qtablewidgetitem10->setText(QApplication::translate("mainwindowClass", "Value", 0));
        QTableWidgetItem *___qtablewidgetitem11 = stateTable->verticalHeaderItem(0);
        ___qtablewidgetitem11->setText(QApplication::translate("mainwindowClass", "Min", 0));
        QTableWidgetItem *___qtablewidgetitem12 = stateTable->verticalHeaderItem(1);
        ___qtablewidgetitem12->setText(QApplication::translate("mainwindowClass", "Max", 0));
        QTableWidgetItem *___qtablewidgetitem13 = stateTable->verticalHeaderItem(2);
        ___qtablewidgetitem13->setText(QApplication::translate("mainwindowClass", "Mean", 0));
        QTableWidgetItem *___qtablewidgetitem14 = stateTable->verticalHeaderItem(3);
        ___qtablewidgetitem14->setText(QApplication::translate("mainwindowClass", "StandardDeviation", 0));
        QTableWidgetItem *___qtablewidgetitem15 = stateTable->verticalHeaderItem(4);
        ___qtablewidgetitem15->setText(QApplication::translate("mainwindowClass", "Voxel Count", 0));
        QTableWidgetItem *___qtablewidgetitem16 = stateTable->verticalHeaderItem(5);
        ___qtablewidgetitem16->setText(QApplication::translate("mainwindowClass", "Current Voxel", 0));
        QTableWidgetItem *___qtablewidgetitem17 = stateTable->verticalHeaderItem(6);
        ___qtablewidgetitem17->setText(QApplication::translate("mainwindowClass", "Current Voxel Value", 0));
        QTableWidgetItem *___qtablewidgetitem18 = stateTable->verticalHeaderItem(7);
        ___qtablewidgetitem18->setText(QApplication::translate("mainwindowClass", "Heterogeneity", 0));
        calcHerterButton->setText(QApplication::translate("mainwindowClass", "Calculate Heterogeneity", 0));
        menuStart->setTitle(QApplication::translate("mainwindowClass", "Start", 0));
        menuAbout->setTitle(QApplication::translate("mainwindowClass", "About", 0));
    } // retranslateUi

};

namespace Ui {
    class mainwindowClass: public Ui_mainwindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
