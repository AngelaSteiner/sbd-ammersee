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
#ifndef EVENT_ADD_H
#define EVENT_ADD_H

#include <QDialog>
#include <mainwindow.h>
#include <QString>
#include <dbank.h>

namespace Ui {
class Event_add;
}

class Event_add : public QDialog
{
    Q_OBJECT

public:
    explicit Event_add(QWidget *parent = 0);
    ~Event_add();

signals:
    void update_MainWindow_Listview();

private slots:
    //Übernahme des Eventnamens bei Betätigung der Entertaste in die
    //Datenbank
    void on_lineEdit_Event_Name_returnPressed();

    //Übernahme des Eventnamens bei Betätigung des OK-Buttons in die
    //Datenbank
    void on_pBtn_Event_Add_OK_clicked();

private:
    Ui::Event_add *ui;
};

#endif // EVENT_ADD_H
