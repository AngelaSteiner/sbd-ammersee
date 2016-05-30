#ifndef DBANK_H
#define DBANK_H

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QMainWindow>
#include <QString>
#include <QtSql>
#include <QFileInfo>
#include <mainwindow.h>
#include <QMainWindow>
#include <QMessageBox>
#include <QDateTime>

class DBank
{
private:


public:
    QSqlDatabase myDB;
    //DBank(QString);
    DBank();
    //Verbindung zur Datenbank herstellen
    bool con_open();
    //Verbindung zur Datenbank trennen
    void con_closed();

    //Neuer Eintrag in Datenbank "Tabelle Event"
    //Übergabe-Parameter ist "Name des Events"
    void addEvent(QString);

    //Eintrag aus Datenbank "Tabelle Event" mit den zugehörigen
    //Teilnehmern aus "Tabelle Teilnehmer" entfernen
    //Übergabe-Parameter ist "ID des Events" in der Datenbank
    void removeEvent(QString);

    //Neuer Eintrag in Datenbank "Tabelle Teilnehmer"
    //Übergabe-Parameter ist "EventID, Vorname, Nachname, RFID"
    void addTeilnehmer(QString,QString,QString,QString);

    //Eintrag aus Datenbank "Tabelle Teilnehmer" entfernen
    //Übergabe-Parameter ist "ID des Events" in der Datenbank
    void removeTeilnehmer(QString);

    //Eintrag der Startzeit in Datenbank "Tabelle Event"
    //Übergabe-Parameter ist "ID des Events" in der Datenbank
    void setStartzeit(QString);    

    //Rückgabe von Datum und Startzeit als int (Sekunden seit 01.01.1970)
    //Übergabe-Parameter ist "ID des Events" in der Datenbank
    uint getDatumStartzeitfromEvent(QString);

    //Abfrage, ob das Event bereits vorbei ist, um gezielt Eingaben
    //zu sperren oder freizugeben
    //Übergabe-Parameter ist "ID des Events" in der Datenbank
    bool isEventDone(QString);

    //Das "Event" wird in der Datenbank gekennzeichnet, um
    //alle Eingaben zu sperren.
    //Übergabe-Parameter ist "ID des Events" in der Datenbank
    void setEventDone(QString);

    //Eintrag der Endzeit in Datenbank "Tabelle Teilnehmer"
    //Übergabe-Parameter ist "RFID" des Teilnehmers
    void setEndzeit(QString);

    //Rückgabe der Anzahl an Teilnehmer, die sich noch im Wasser befinden
    //Auswertung anhand Endzeit = 0
    //Übergabe-Parameter ist "ID des Events" in der Datenbank
    int getCountSchwimmerWithEndzeitNull(QString E_ID);
};

#endif // DBANK_H
