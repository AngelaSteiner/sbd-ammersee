#ifndef EVENT_ADD_H
#define EVENT_ADD_H

#include <QDialog>
#include <mainwindow.h>
#include <QString>
#include <dbank.h>

namespace Ui {
class Event_add;
}

class Event_add : public QDialog
{
    Q_OBJECT

public:
    explicit Event_add(QWidget *parent = 0);
    ~Event_add();

signals:
    void update_MainWindow_Listview();

private slots:
    //Übernahme des Eventnamens bei Betätigung der Entertaste in die
    //Datenbank
    void on_lineEdit_Event_Name_returnPressed();

    //Übernahme des Eventnamens bei Betätigung des OK-Buttons in die
    //Datenbank
    void on_pBtn_Event_Add_OK_clicked();

private:
    Ui::Event_add *ui;
};

#endif // EVENT_ADD_H
