#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "noteswindow.h"

QString directoryPath = QDir::currentPath();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("QWidget { background-color: #171717; }");
    ui->ButtonReg->setStyleSheet("background-color: #B0C4DE; color: white; font-size: 16px; border-radius: 5px;");
    ui->ButtonEntrance->setStyleSheet("background-color: #B0C4DE; color: white; font-size: 16px; border-radius: 5px;");
    ui->ButtonExit->setStyleSheet("background-color: #B0C4DE; color: white; font-size: 16px; border-radius: 5px;");
    ui->lineEditLog->setStyleSheet("background-color: #B0C4DE; color: black; font-size: 16px; border-radius: 5px;");
    ui->lineEditPass->setStyleSheet("background-color: #B0C4DE; color: black; font-size: 16px; border-radius: 5px;");
    ui->label->setStyleSheet("background-color: #171717; color: white; font-size: 16px; border-radius: 5px;");
    ui->label_2->setStyleSheet("background-color: #171717; color: white; font-size: 16px; border-radius: 5px;");


}

MainWindow::~MainWindow()
{
    delete ui;
}



user MainWindow::ReceiveLogPass(){
    if(ui->lineEditLog->text() != "" && ui->lineEditPass->text() != ""){
        user* OneUser = new user(ui->lineEditLog->text(), ui->lineEditPass->text());
        return *OneUser;
    }
    else{
        message("Поле логина/пароля посуто");
    }
}

bool MainWindow::CheckUser(QString fileName, user OneUser){
    QFile file(fileName);
    QString line;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        message("Пользователь не найден!");
        return false;
    }
    QTextStream in(&file);
    line = in.readLine();
    line = xorEncryptDecrypt(line, OneUser.name);
    if(line == OneUser.password){
        return true;
    }
    else{
        message("Пароль неверный!");
    }

    file.close();
    return false;
}

void MainWindow::message(const QString text){
    QMessageBox messageBox;
    messageBox.setText(text);
    messageBox.setStyleSheet("QMessageBox { background-color: #B0C4DE; color: black; }");
    messageBox.exec();
}


void MainWindow::on_ButtonEntrance_clicked()
{
    bool check = false;
    user ExisUser = ReceiveLogPass();
    if(ExisUser.name != ""){
        check = CheckUser(directoryPath + "/" + ui->lineEditLog->text() + ".txt",ExisUser);
        if(check == true){
           NotesWindow window;
           window.setModal(true);
           window.setLoadedText(ExisUser.name);
           window.updateNotex();
           window.exec();
        }

    }
}

void MainWindow::on_ButtonReg_clicked()
{
    user NewUser = ReceiveLogPass();
    if(NewUser.name != "" && NewUser.password != ""){
        QFile file(directoryPath + "/" + ui->lineEditLog->text() + ".txt");
        if (file.exists(directoryPath + "/" + ui->lineEditLog->text() + ".txt")) {
            message("Пользователь с таким именем существует");
        } else {
            NewUser.saveToFile(directoryPath + "/" + ui->lineEditLog->text() + ".txt", xorEncryptDecrypt(NewUser.password, NewUser.name));
        }
    }
}

