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
#ifndef AUSWERTUNG_H
#define AUSWERTUNG_H

#include <QDialog>
#include <teilnehmer.h>
#include <dbank.h>


namespace Ui {
class auswertung;
}

class auswertung : public QDialog
{
    Q_OBJECT

public:
    explicit auswertung(QWidget *parent = 0);
    ~auswertung();

public slots:
    void receiveEIDinDuringEvent(QString);

private:
    Ui::auswertung *ui;
};

#endif // AUSWERTUNG_H
