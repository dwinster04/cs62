#include "qmainwindow.h"
#include "ui_qmainwindow.h"

QMainWindow::QMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QMainWindow)
{
    ui->setupUi(this);
}

QMainWindow::~QMainWindow()
{
    delete ui;
}
