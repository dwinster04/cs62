#ifndef QMAINWINDOW_H
#define QMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class QMainWindow;
}
QT_END_NAMESPACE

class QMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QMainWindow(QWidget *parent = nullptr);
    ~QMainWindow();

private:
    Ui::QMainWindow *ui;
};
#endif // QMAINWINDOW_H
