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
#include "auswertung.h"
#include "ui_auswertung.h"

auswertung::auswertung(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::auswertung)
{
    ui->setupUi(this);
}

auswertung::~auswertung()
{
    delete ui;
}

void auswertung::receiveEIDinDuringEvent(QString EvID)
{
    DBank a;
    a.con_open();

    QSqlQueryModel *model = new QSqlQueryModel();
   // QSqlQueryModel *oldModell = NULL;

    QSqlQuery qry = QSqlQuery(a.myDB);
    qry.prepare("select Vorname, Nachname, IDTAG from Teilnehmer where Event_ID = '"+EvID+"' ORDER BY Endzeit ASC ");
    qry.exec();
    model->setQuery(qry);

    //oldModell = (QSqlQueryModel*)ui->tableView->model();
    ui->tableView_Auswertung->setModel(model);
    //ui->tableView->setColumnHidden(0,true);

   // if(oldModell)
    //    delete oldModell;
}
