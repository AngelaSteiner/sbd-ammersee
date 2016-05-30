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
#include "sources/event_add.h"
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
