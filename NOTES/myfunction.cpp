#include "myfunction.h"

QString xorEncryptDecrypt(QString input, QString key) {
    QString output = "";
    for (int i = 0; i < input.length(); i++) {
        QChar inputChar = input[i];
        QChar keyChar = key[i % key.length()];
        QChar encryptedChar = inputChar.unicode() ^ keyChar.unicode();
        output += encryptedChar;
    }
    return output;
}

