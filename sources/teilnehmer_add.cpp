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


