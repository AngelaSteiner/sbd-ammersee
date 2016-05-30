#include "event_add.h"
#include "ui_event_add.h"

Event_add::Event_add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Event_add)
{
    ui->setupUi(this);
    setWindowTitle("Eingabe der Event-Bezeichnung");
}

Event_add::~Event_add()
{
    delete ui;
}

//Übernahme des Eventnamens bei Betätigung der Entertaste in die
//Datenbank
void Event_add::on_lineEdit_Event_Name_returnPressed()
{
    QString EventName = ui->lineEdit_Event_Name->text();
    DBank a;
    a.addEvent(EventName);

    emit(update_MainWindow_Listview());
    this->close();
}

//Übernahme des Eventnamens bei Betätigung des OK-Buttons in die
//Datenbank
void Event_add::on_pBtn_Event_Add_OK_clicked()
{
    on_lineEdit_Event_Name_returnPressed();
}
