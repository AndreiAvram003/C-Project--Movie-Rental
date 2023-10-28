/********************************************************************************
** Form generated from reading UI file 'l10bun.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_L10BUN_H
#define UI_L10BUN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_l10bunClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *l10bunClass)
    {
        if (l10bunClass->objectName().isEmpty())
            l10bunClass->setObjectName("l10bunClass");
        l10bunClass->resize(600, 400);
        menuBar = new QMenuBar(l10bunClass);
        menuBar->setObjectName("menuBar");
        l10bunClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(l10bunClass);
        mainToolBar->setObjectName("mainToolBar");
        l10bunClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(l10bunClass);
        centralWidget->setObjectName("centralWidget");
        l10bunClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(l10bunClass);
        statusBar->setObjectName("statusBar");
        l10bunClass->setStatusBar(statusBar);

        retranslateUi(l10bunClass);

        QMetaObject::connectSlotsByName(l10bunClass);
    } // setupUi

    void retranslateUi(QMainWindow *l10bunClass)
    {
        l10bunClass->setWindowTitle(QCoreApplication::translate("l10bunClass", "l10bun", nullptr));
    } // retranslateUi

};

namespace Ui {
    class l10bunClass: public Ui_l10bunClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_L10BUN_H
