/********************************************************************************
** Form generated from reading ui file 'mainwindow.ui'
**
** Created: Wed Jun 10 16:21:50 2009
**      by: Qt User Interface Compiler version 4.5.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include <linenumber.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_open;
    QAction *action_new;
    QAction *action_Save;
    QAction *actionC_lose;
    QAction *actionComment;
    QAction *actionUncomment;
    QAction *actionIndent;
    QAction *actionUnindent;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionCut;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionSave_as;
    QAction *actionQuit;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    lineNumber *codeEditor;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(600, 400);
        action_open = new QAction(MainWindow);
        action_open->setObjectName(QString::fromUtf8("action_open"));
        QIcon icon;
        icon.addPixmap(QPixmap(QString::fromUtf8(":/img/img/open.png")), QIcon::Normal, QIcon::On);
        action_open->setIcon(icon);
        action_new = new QAction(MainWindow);
        action_new->setObjectName(QString::fromUtf8("action_new"));
        QIcon icon1;
        icon1.addPixmap(QPixmap(QString::fromUtf8(":/img/img/new.png")), QIcon::Normal, QIcon::Off);
        action_new->setIcon(icon1);
        action_Save = new QAction(MainWindow);
        action_Save->setObjectName(QString::fromUtf8("action_Save"));
        QIcon icon2;
        icon2.addPixmap(QPixmap(QString::fromUtf8(":/img/img/save.png")), QIcon::Normal, QIcon::Off);
        action_Save->setIcon(icon2);
        actionC_lose = new QAction(MainWindow);
        actionC_lose->setObjectName(QString::fromUtf8("actionC_lose"));
        QIcon icon3;
        icon3.addPixmap(QPixmap(QString::fromUtf8(":/img/img/closeall.png")), QIcon::Normal, QIcon::Off);
        actionC_lose->setIcon(icon3);
        actionComment = new QAction(MainWindow);
        actionComment->setObjectName(QString::fromUtf8("actionComment"));
        QIcon icon4;
        icon4.addPixmap(QPixmap(QString::fromUtf8(":/img/img/comment.png")), QIcon::Normal, QIcon::Off);
        actionComment->setIcon(icon4);
        actionUncomment = new QAction(MainWindow);
        actionUncomment->setObjectName(QString::fromUtf8("actionUncomment"));
        QIcon icon5;
        icon5.addPixmap(QPixmap(QString::fromUtf8(":/img/img/uncomment.png")), QIcon::Normal, QIcon::Off);
        actionUncomment->setIcon(icon5);
        actionIndent = new QAction(MainWindow);
        actionIndent->setObjectName(QString::fromUtf8("actionIndent"));
        QIcon icon6;
        icon6.addPixmap(QPixmap(QString::fromUtf8(":/img/img/indent.png")), QIcon::Normal, QIcon::Off);
        actionIndent->setIcon(icon6);
        actionUnindent = new QAction(MainWindow);
        actionUnindent->setObjectName(QString::fromUtf8("actionUnindent"));
        QIcon icon7;
        icon7.addPixmap(QPixmap(QString::fromUtf8(":/img/img/unindent.png")), QIcon::Normal, QIcon::Off);
        actionUnindent->setIcon(icon7);
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        QIcon icon8;
        icon8.addPixmap(QPixmap(QString::fromUtf8(":/img/img/copy.png")), QIcon::Normal, QIcon::Off);
        actionCopy->setIcon(icon8);
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        QIcon icon9;
        icon9.addPixmap(QPixmap(QString::fromUtf8(":/img/img/paste.png")), QIcon::Normal, QIcon::Off);
        actionPaste->setIcon(icon9);
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName(QString::fromUtf8("actionCut"));
        QIcon icon10;
        icon10.addPixmap(QPixmap(QString::fromUtf8(":/img/img/cut.png")), QIcon::Normal, QIcon::Off);
        actionCut->setIcon(icon10);
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        QIcon icon11;
        icon11.addPixmap(QPixmap(QString::fromUtf8(":/img/img/undo.png")), QIcon::Normal, QIcon::Off);
        actionUndo->setIcon(icon11);
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        QIcon icon12;
        icon12.addPixmap(QPixmap(QString::fromUtf8(":/img/img/redo.png")), QIcon::Normal, QIcon::Off);
        actionRedo->setIcon(icon12);
        actionSave_as = new QAction(MainWindow);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        QIcon icon13;
        icon13.addPixmap(QPixmap(QString::fromUtf8(":/img/img/saveas.png")), QIcon::Normal, QIcon::Off);
        actionSave_as->setIcon(icon13);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        QIcon icon14;
        icon14.addPixmap(QPixmap(QString::fromUtf8(":/img/img/exit.png")), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon14);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setMargin(11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        codeEditor = new lineNumber(centralWidget);
        codeEditor->setObjectName(QString::fromUtf8("codeEditor"));

        horizontalLayout->addWidget(codeEditor);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuFile->addAction(action_new);
        menuFile->addAction(action_open);
        menuFile->addAction(action_Save);
        menuFile->addAction(actionSave_as);
        menuFile->addAction(actionC_lose);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);
        menuEdit->addSeparator();
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addSeparator();
        menuEdit->addAction(actionIndent);
        menuEdit->addAction(actionUnindent);
        menuEdit->addSeparator();
        menuEdit->addAction(actionComment);
        menuEdit->addAction(actionUncomment);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        action_open->setText(QApplication::translate("MainWindow", "&open", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action_open->setToolTip(QApplication::translate("MainWindow", "Open file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        action_new->setText(QApplication::translate("MainWindow", "&new", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action_new->setToolTip(QApplication::translate("MainWindow", "New file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        action_Save->setText(QApplication::translate("MainWindow", "&Save", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action_Save->setToolTip(QApplication::translate("MainWindow", "Save the file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionC_lose->setText(QApplication::translate("MainWindow", "close", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionC_lose->setToolTip(QApplication::translate("MainWindow", "Close file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionComment->setText(QApplication::translate("MainWindow", "Comment", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionComment->setToolTip(QApplication::translate("MainWindow", "Comment selection", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionUncomment->setText(QApplication::translate("MainWindow", "Uncomment", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionUncomment->setToolTip(QApplication::translate("MainWindow", "Uncomment selection", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionIndent->setText(QApplication::translate("MainWindow", "Indent", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionIndent->setToolTip(QApplication::translate("MainWindow", "Indent selection", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionUnindent->setText(QApplication::translate("MainWindow", "Unindent", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionUnindent->setToolTip(QApplication::translate("MainWindow", "Unindent selection", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionCopy->setText(QApplication::translate("MainWindow", "copy", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionCopy->setToolTip(QApplication::translate("MainWindow", "Copy selected text", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionPaste->setText(QApplication::translate("MainWindow", "Paste", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionPaste->setToolTip(QApplication::translate("MainWindow", "Paste copied text", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionCut->setText(QApplication::translate("MainWindow", "Cut", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionCut->setToolTip(QApplication::translate("MainWindow", "Cut selected text", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionUndo->setText(QApplication::translate("MainWindow", "Undo", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionUndo->setToolTip(QApplication::translate("MainWindow", "Undo", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionRedo->setText(QApplication::translate("MainWindow", "Redo", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionRedo->setToolTip(QApplication::translate("MainWindow", "Redo", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSave_as->setText(QApplication::translate("MainWindow", "Save as...", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
