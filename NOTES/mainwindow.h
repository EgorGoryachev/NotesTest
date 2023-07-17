#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myfunction.h"
#include "noteswindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    user ReceiveLogPass();

    bool CheckUser(QString fileName, user OneUser);

    void message(const QString text);

    void on_ButtonEntrance_clicked();

    void on_ButtonReg_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
