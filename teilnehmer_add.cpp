#include "teilnehmer_add.h"
#include "ui_teilnehmer_add.h"

teilnehmer_add::teilnehmer_add(QWidget *parent,  QString Event_ID_) :
    QDialog(parent),

    ui(new Ui::teilnehmer_add)
{
    ui->setupUi(this);
    Event_ID = Event_ID_;
    setWindowTitle("Teilnehmer hinzufügen");
}

teilnehmer_add::~teilnehmer_add()
{
    delete ui;
}

//Übernahme der Teilnehmer-Daten bei Betätigung der Entertaste in die
//Datenbank
void teilnehmer_add::on_buttonBox_accepted()
{
    DBank a;
    a.addTeilnehmer(Event_ID,ui->lineEdit_Vorname->text(),ui->lineEdit_Nachname->text(),ui->lineEdit_RFID->text());

    emit(update_teilnehmer_TW());
    this->close();
}


