#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tester.h"

class Client;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonLink_clicked();

    void on_pushButtonSend_clicked();
    void on_radioButton_clicked();

public:
    void setMsg(QString msg);

private:
    Ui::MainWindow *ui;
    Client *client_;
};

#endif // MAINWINDOW_H
