#ifndef NOTESWINDOW_H
#define NOTESWINDOW_H
#include "myfunction.h"
#include "mainwindow.h"

namespace Ui {
class NotesWindow;
}

class NotesWindow : public QDialog
{
    Q_OBJECT


public:
    explicit NotesWindow(QWidget *parent = nullptr);
    ~NotesWindow();

    void setLoadedText(const QString& loadedText);

    void updateNotex();


private slots:

    QString createNewButton(QString text);

    QString inputField();

    void creteNotex(QString notex);

    void LoadNotex();

    void SaveNotexNew();

    void Save_to_config();

    void Delete_to_config();

    void on_ButtonNew_clicked();

    void on_ButtonMenu_clicked();

    void on_ButtonSaveED_clicked();

    void on_ButtonRemove_clicked();

    void on_ButtonSaveFile_clicked();

    void on_ButtonLoadFile_clicked();


private:
    Ui::NotesWindow *ui;
};

#endif // NOTESWINDOW_H
