/********************************************************************************
** Form generated from reading UI file 'ITM_OBJ_Auto_SCAN.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ITM_OBJ_AUTO_SCAN_H
#define UI_ITM_OBJ_AUTO_SCAN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_OBJMainWindow
{
public:
    QWidget *centralWidget;
    QVTKWidget *_cloudQVTKWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *OBJMainWindow)
    {
        if (OBJMainWindow->objectName().isEmpty())
            OBJMainWindow->setObjectName(QStringLiteral("OBJMainWindow"));
        OBJMainWindow->resize(600, 400);
        centralWidget = new QWidget(OBJMainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        _cloudQVTKWidget = new QVTKWidget(centralWidget);
        _cloudQVTKWidget->setObjectName(QStringLiteral("_cloudQVTKWidget"));
        _cloudQVTKWidget->setGeometry(QRect(20, 20, 300, 300));
        OBJMainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(OBJMainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        OBJMainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(OBJMainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        OBJMainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(OBJMainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        OBJMainWindow->setStatusBar(statusBar);

        retranslateUi(OBJMainWindow);

        QMetaObject::connectSlotsByName(OBJMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *OBJMainWindow)
    {
        OBJMainWindow->setWindowTitle(QApplication::translate("OBJMainWindow", "ITM_OBJ_Auto_SCAN", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class OBJMainWindow: public Ui_OBJMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ITM_OBJ_AUTO_SCAN_H
