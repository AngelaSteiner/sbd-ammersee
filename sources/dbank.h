/*
 * SBDelphin 03 - Ammerseeschwimmen - RFID Manager
 * Copyright (C) 2016 Steiner Angela,
 * 				   Cestonaro Thilo
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef DBANK_H
#define DBANK_H

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QMainWindow>
#include <QString>
#include <QtSql>
#include <QFileInfo>
#include "sources/mainwindow.h"
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
