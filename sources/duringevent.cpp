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
#include "sources/duringevent.h"
#include "ui_duringevent.h"

duringevent::duringevent(QWidget *parent, QString Event_ID_) :
    QDialog(parent),
    ui(new Ui::duringevent)
{
    ui->setupUi(this);

    //aktuelle Systemzeit festhalten
    time.start();
    //Display Anzeige aktualisieren
    updateTimeDisplay();
    //Timeout Signal aktualisiert alle 1000ms das Display
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateTimeDisplay()));
    //alle 1000ms ein timeout
    timer.start(1000);

    Event_ID = Event_ID_;

    setWindowTitle("Event-Status");
    AnzSchwimmerImWasser();
}

duringevent::~duringevent()
{
    delete ui;
}

//Errechnung der verstrichenen Zeit seit Start
//und Anzeige auf dem lbl_ZeitAnzeige
void duringevent::updateTimeDisplay()
{
    //Vergangene Zeit seit time.start() Zeitpunkt
    int secs = time.elapsed() / 1000;
    int mins = (secs / 60) % 60;
    int hours = (secs / 3600);
    secs = secs % 60;
    ui->lbl_ZeitAnzeige->setText(QString("%1:%2:%3").arg(hours, 2, 10,
                        QLatin1Char('0')).arg(mins, 2, 10,
                        QLatin1Char('0')).arg(secs, 2, 10,
                        QLatin1Char('0')));
}

//Abfrage in der Datenbank, wieviel Teiln. ohne Endzeit vorhanden sind.
//Das Ergebnis wird auf dem lbl_AnzeigeTeilnehmerimWasser angezeigt
void duringevent::AnzSchwimmerImWasser()
{
    DBank a;
    int count = 0;
    count = a.getCountSchwimmerWithEndzeitNull(Event_ID);
    ui->lbl_AnzeigeTeilnehmerimWasser->setText(QString("%1").arg(count));
}

//RFID einlesen vom Teilnehmer und in Datenbank "Tabelle Teilnehmer"
//die Endzeit des Teilnehmers eintrsgen
void duringevent::on_lineEdit_RFID_returnPressed()
{
    DBank a;
    a.setEndzeit(ui->lineEdit_RFID->text());
    ui->lineEdit_RFID->clear();
    AnzSchwimmerImWasser();

}

//Wenn Event beendet wird, dann In Datenbank "Tabelle Event"
//das Event als beendet markieren, damit keine Eingaben
//mehr getätigt werden können und abschließend die
//Auswertung angezeigt werden kann.
void duringevent::on_pBtn_Event_beenden_clicked()
{
    DBank a;
    QMessageBox msg;
    msg.setText("Wollen Sie das Event wirklich beenden?");
    msg.setWindowTitle("Programm beenden");
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg.setIcon(QMessageBox::Critical);
    msg.setButtonText(QMessageBox::Yes, "Ja");
    msg.setButtonText(QMessageBox::No, "Nein");
    msg.setDefaultButton(QMessageBox::No);

    int msg_return =  msg.exec();

    switch (msg_return)
    {
        case QMessageBox::Yes:

            //Das "Event" wird in der Datenbank
            //gekennzeichnet, um alle Eingaben zu sperren.
            a.setEventDone(Event_ID);

            //Signal ausgelösen um das TableView
            //im Teilnehmer.cpp upzudaten
            emit(update_TW_Finish());

            //Fenster "duringevent" schließen
            this->close();
        break;

        case QMessageBox::No:
      // nichts machen
        break;

        default:
      // wenn garnichts geht ;-)
        break;
    }

}

//Abfangen, wenn das Fenster über "X"-beendet wird
void duringevent::on_duringevent_rejected()
{
    on_pBtn_Event_beenden_clicked();
}
