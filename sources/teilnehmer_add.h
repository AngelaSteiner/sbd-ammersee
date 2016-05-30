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
#ifndef TEILNEHMER_ADD_H
#define TEILNEHMER_ADD_H

#include <QDialog>
#include "sources/teilnehmer.h"
#include "sources/dbank.h"
#include <QString>


namespace Ui {
class teilnehmer_add;
}

class teilnehmer_add : public QDialog
{
    Q_OBJECT

public:
    explicit teilnehmer_add(QWidget *parent = 0, QString Event_ID_ = "");
    ~teilnehmer_add();



signals:    
    void update_teilnehmer_TW();

private slots:
    //Übernahme der Teilnehmer-Daten bei Betätigung der Entertaste in die
    //Datenbank
    void on_buttonBox_accepted();

private:
    Ui::teilnehmer_add *ui;
    QString Event_ID;
};

#endif // TEILNEHMER_ADD_H
