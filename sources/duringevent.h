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
#ifndef DURINGEVENT_H
#define DURINGEVENT_H

#include <QDialog>
#include "sources/teilnehmer.h"
#include <QTime>
#include <QTimer>
#include <QString>
#include <QMessageBox>
#include <QDebug>



namespace Ui {
class duringevent;
}

class duringevent : public QDialog
{
    Q_OBJECT

public:
    //Bei Anlage des Objektes wird auch gleich die Variable Event-ID mit angelegt
    explicit duringevent(QWidget *parent = 0, QString Event_ID = "");
    ~duringevent();


signals:
    //void update_teilnehmer_TW();

    //Das Signal wird ausgelöst, nachdem das Event beendet wurde,
    //um das TableView im Teilnehmer.cpp upzudaten
    void update_TW_Finish();


public slots:
    //Errechnung der verstrichenen Zeit seit Start
    //und Anzeige auf dem lbl_ZeitAnzeige
    void updateTimeDisplay();

    //Abfrage in der Datenbank, wieviel Teiln. ohne Endzeit vorhanden sind.
    //Das Ergebnis wird auf dem lbl_AnzeigeTeilnehmerimWasser angezeigt
    void AnzSchwimmerImWasser();

private slots:
    //RFID einlesen vom Teilnehmer und in Datenbank "Tabelle Teilnehmer"
    //die Endzeit des Teilnehmers eintrsgen
    void on_lineEdit_RFID_returnPressed();

    //Wenn Event beendet wird, dann In Datenbank "Tabelle Event"
    //das Event als beendet markieren, damit keine Eingaben
    //mehr getätigt werden können und abschließend die
    //Auswertung angezeigt werden kann.
    void on_pBtn_Event_beenden_clicked();

    //Abfangen, wenn das Fenster über "X"-beendet wird
    void on_duringevent_rejected();

private:
    Ui::duringevent *ui;
    QString Event_ID;

    QTime time; //benötigt um vergangene Zeit zu berechnen
    QTimer timer;  //Sekundentimer für timeout-Signal
};

#endif // DURINGEVENT_H
