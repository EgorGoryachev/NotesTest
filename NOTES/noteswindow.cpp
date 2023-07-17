#include "noteswindow.h"
#include "ui_noteswindow.h"
#include "mainwindow.h"
#include "myfunction.h"

QString ButtonNow;
QString directoryPathNotes = QDir::currentPath();

int GeometryButton = 0;

NotesWindow::NotesWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NotesWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("QWidget { background-color: #171717; }");
    ui->ButtonNew->setStyleSheet("background-color: #B0C4DE; color: white; font-size: 16px; border-radius: 5px;");
    ui->ButtonSaveFile->setStyleSheet("background-color: #B0C4DE; color: white; font-size: 16px; border-radius: 5px;");
    ui->ButtonLoadFile->setStyleSheet("background-color: #B0C4DE; color: white; font-size: 16px; border-radius: 5px;");
    ui->ButtonSaveED->setStyleSheet("background-color: #B0C4DE; color: white; font-size: 16px; border-radius: 5px;");
    ui->ButtonMenu->setStyleSheet("background-color: #B0C4DE; color: white; font-size: 16px; border-radius: 5px;");
    ui->ButtonRemove->setStyleSheet("background-color: #B0C4DE; color: white; font-size: 16px; border-radius: 5px;");
    ui->checkBox->setStyleSheet("background-color: Pastel Colors; color: white; font-size: 16px; border-radius: 5px;");
    ui->checkBox_2->setStyleSheet("background-color: Pastel Colors; color: white; font-size: 16px; border-radius: 5px;");
    ui->textEdit->setStyleSheet("background-color: Pastel Colors; color: black; font-size: 16px; border-radius: 5px;");
    ui->label->setStyleSheet("color: White;font-size: 22px;");
}

NotesWindow::~NotesWindow()
{
    delete ui;

}



QString NotesWindow::createNewButton(QString text)
{
    GeometryButton += 65;
    QString buttonName = text;
    QPushButton *newButton = new QPushButton(this);
    newButton->setText(text);
    connect(newButton, &QPushButton::clicked, this, [this, buttonName]() {
            ButtonNow = buttonName;
            creteNotex(buttonName);
        });
    newButton->setStyleSheet("background-color: #B0C4DE; color: white; font-size: 16px; border-radius: 5px;");
    newButton->setGeometry(ui->ButtonNew->geometry().translated(ui->ButtonNew->width() + GeometryButton, 0));
    newButton->setFixedSize(61,31);
    newButton->setObjectName(buttonName);
    newButton->show();
    return buttonName;
}

void NotesWindow::SaveNotexNew(){
 QString path = QFileDialog::getOpenFileName(0,QObject::tr("Укажите файл"),QDir::homePath(), QObject::tr("Файл SQLite (*.db);;Все файлы (*.*)"));
 QFile file(path);
 if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
     QTextStream out(&file);
     out << ui->textEdit->toPlainText();
     file.close();
 }
}

void NotesWindow::LoadNotex(){
    QString path = QFileDialog::getOpenFileName(0,QObject::tr("Укажите файл базы данных"),QDir::homePath(), QObject::tr("Файл SQLite (*.db);;Все файлы (*.*)"));
    QFile file(path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString text = in.readAll();
        ui->textEdit->setPlainText(text);
        file.close();
    }
}

void NotesWindow::creteNotex(QString notex){
  QFile file(directoryPathNotes + "/" + ui->label->text() + "/" + ui->label->text() + "_" + notex + ".txt");
   if (!file.exists()) {
       if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
           Save_to_config();
           QTextStream out(&file);
           file.close();
       } else {
           // Error creating file
       }
   }
   if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
       QTextStream in(&file);
       QString text = in.readAll();
       ui->textEdit->setPlainText(text);
       file.close();
   }
}

QString NotesWindow::inputField(){
    QWidget *win = new QWidget();
    QLineEdit *inputField = new QLineEdit(win);
    inputField->setGeometry(10, 10, 200, 30);
    inputField->show();
    win->setWindowModality(Qt::WindowModal);
    win->show();
    QEventLoop loop;
    QObject::connect(inputField, &QLineEdit::returnPressed, [win, &loop]() {
        loop.quit();
    });

    loop.exec();
    win->close();
    return inputField->text();

}

void NotesWindow::setLoadedText(const QString& loadedText) {
    ui->label->setText(loadedText);
    QDir dir(QDir::cleanPath(directoryPathNotes) + "/");
    if (!dir.exists(loadedText)) {
        dir.mkdir(loadedText);
    }
}

void NotesWindow::Save_to_config(){
    QFile file(directoryPathNotes + "/" + ui->label->text() + ".txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << "\n" << "$notext$" << ButtonNow;
        file.close();
    }
}

void NotesWindow::Delete_to_config(){
    QString filename = directoryPathNotes + "/" + ui->label->text() + ".txt";
        QFile file(filename);
        if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            QTextStream in(&file);
            QString content = in.readAll();
            file.resize(0);
            QTextStream out(&file);
            QStringList lines = content.split("\n");
            for (int i = 0; i < lines.size(); i++) {
                QString line = lines.at(i);
                if (!line.contains("$notext$" + ButtonNow)) {
                    out << line << "\n";
                }
            }
            file.close();
        }
}

void NotesWindow::updateNotex(){
    QFile file(directoryPathNotes + "/" + ui->label->text() + ".txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line.contains("$notext$")) {
                line.remove("$notext$");
                createNewButton(line);
            }
        }
        file.close();
    }
}


void NotesWindow::on_ButtonNew_clicked()
{
    createNewButton(inputField());
}

void NotesWindow::on_ButtonMenu_clicked()
{
    GeometryButton = 0;
    this->close();
}

void NotesWindow::on_ButtonRemove_clicked()
{
    QPushButton* button = findChild<QPushButton*>(ButtonNow);
    button->deleteLater();
    QFile file(directoryPathNotes + "/" + ui->label->text() + "/" + ui->label->text() + "_" + ButtonNow + ".txt");
    if (file.exists()) {
        file.remove();
    }
    Delete_to_config();
}

void NotesWindow::on_ButtonSaveED_clicked()
{
    QFile file_conf(directoryPathNotes + "/" + ui->label->text() + ".txt");
    QString line;
    if (!file_conf.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to open input file."));
        return;
    }
    QTextStream in(&file_conf);
    line = in.readLine();
    line = xorEncryptDecrypt(line, ui->label->text());
    file_conf.close();
    QFile file(directoryPathNotes + "/" + ui->label->text() + "/" + ui->label->text() + "_" + ButtonNow + ".txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        if(ui->checkBox->isChecked() && !ui->checkBox_2->isChecked()){
            QString XOR_String = xorEncryptDecrypt(ui->textEdit->toPlainText(), line);
            out << XOR_String;
            file.close();
        }
        if(!ui->checkBox->isChecked() && ui->checkBox_2->isChecked()){
            QMessageBox messageBox;
            messageBox.setText("Для корректновго шифрования,нужно использовать тот язык кодового слова,на котором написаны заметки");
            messageBox.setStyleSheet("QMessageBox { background-color: #B0C4DE; color: black; }");
            messageBox.exec();
            QString XOR_String = xorEncryptDecrypt(ui->textEdit->toPlainText(), inputField());
            out << XOR_String;
            file.close();
        }
        if(!ui->checkBox->isChecked() && !ui->checkBox_2->isChecked()){
            out << ui->textEdit->toPlainText();
            file.close();
        }
    }
    else{
        QMessageBox::critical(this, tr("Error"), tr("Failed to open input file."));
        return;
    }
}

void NotesWindow::on_ButtonLoadFile_clicked()
{
     LoadNotex();
}

void NotesWindow::on_ButtonSaveFile_clicked()
{
    SaveNotexNew();
}
