/********************************************************************************
** Form generated from reading UI file 'qmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QMAINWINDOW_H
#define UI_QMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QMainWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *textEdit;
    QPushButton *pushButton;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *QMainWindow)
    {
        if (QMainWindow->objectName().isEmpty())
            QMainWindow->setObjectName("QMainWindow");
        QMainWindow->resize(800, 600);
        centralwidget = new QWidget(QMainWindow);
        centralwidget->setObjectName("centralwidget");
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(320, 240, 104, 70));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(330, 320, 80, 24));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(330, 220, 211, 16));
        QMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(QMainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        QMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(QMainWindow);
        statusbar->setObjectName("statusbar");
        QMainWindow->setStatusBar(statusbar);

        retranslateUi(QMainWindow);

        QMetaObject::connectSlotsByName(QMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *QMainWindow)
    {
        QMainWindow->setWindowTitle(QCoreApplication::translate("QMainWindow", "QMainWindow", nullptr));
        textEdit->setHtml(QCoreApplication::translate("QMainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("QMainWindow", "Login", nullptr));
        label->setText(QCoreApplication::translate("QMainWindow", "Enter your name:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QMainWindow: public Ui_QMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QMAINWINDOW_H
