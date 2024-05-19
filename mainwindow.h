#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ring_object_manager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ring_object_manager ring_object_manager;

    ~MainWindow();

private slots:
    void on_recount_button_clicked();

    void on_initialization_button_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
