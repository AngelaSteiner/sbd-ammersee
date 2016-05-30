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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sources/event_add.h"
#include "sources/teilnehmer.h"
#include <QMessageBox>
#include <QString>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:
    //Hinzufügen eines neuen Event-Eintrages über "+"-Button
    void on_pBtn_add_Event_clicked();

    //Nach Doppelklick auf einen Event-Eintrag öffnet
    //sich ein neues Fenster
    //  -a) entweder ohne Teilnehmer-Einträgen oder
    //  -b) schon mit bereits eingetragenen Teilnehmern
    void on_listView_doubleClicked(const QModelIndex &index);

    //Eintrag aus Datenbank "Tabelle Event" entfernen
    //inklusive der an diesem Event beteiligten Teilnehmern.
    void on_pBtn_remove_Event_clicked();

    //Der "-"-PBtn (remove_Event) wird erst aktiv,
    //wenn ein Eintrag ausgewählt wurde
    void on_listView_clicked(const QModelIndex &index);

public slots:
    /*
     * Diese Funktion gibt den aktuellen Inhalt der
     * Datenbank "Tabelle Event" für das ListView aus.
     * Also Ausgabe bestehender Event-Einträge
    */
    void updateListView();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
