#ifndef MYFUNCTION_H
#define MYFUNCTION_H
#include <QMainWindow>
#include <QString>
#include <QByteArray>
#include <QFile>
#include <QDataStream>
#include <QTextStream>
#include <QTextEdit>
#include <QMessageBox>
#include <QBoxLayout>
#include <QLineEdit>
#include <QFileDialog>
#include <QDir>
#include <QApplication>
#include <QLabel>
#include <QTextBrowser>



class user{
public:
    QString name, password;

    user(QString log, QString pass) {
        name = log;
        password = pass;
    }

    void Registration(QString log, QString pass) {
        name = log;
        password = pass;
    }

    void saveToFile(QString fileName, QString password) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream out(&file);
            out << password;

            file.close();
        }
    }

    ~user() {
        // Destructor code here
    }
};

#endif // MYFUNCTION_H

QString xorEncryptDecrypt(QString input, QString key);




