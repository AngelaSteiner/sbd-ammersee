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
#include "sources/mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Ammersee-Schwimmen");
    updateListView();  //bei FensterÖffnung wird das ListView aktualisiert
}

MainWindow::~MainWindow()
{
    delete ui;
}




/*
 * Wenn im Mainwindow ein Event über den "+"-Button hinzugefügt wird,
 * dann öffnet sich ein neuer modaler Dialog.
 * Nach Eingabe in diesen Dialog soll der hinzugefügte Eintrag
 * im ListView des Mainwindows ersichtlich sein.
 * Dazu ist der connect-Befehl nötig
*/
void MainWindow::on_pBtn_add_Event_clicked()
{
    Event_add *Fenster = new Event_add;
    Fenster->setModal(true);
    connect(Fenster,SIGNAL(update_MainWindow_Listview()), this,SLOT(updateListView()));
    Fenster->exec();
}

/*
 * Diese Funktion gibt den aktuellen Inhalt der
 * Datenbank "Tabelle Event" für das ListView aus.
 * Also Ausgabe bestehender Event-Einträge
 *
*/
void MainWindow::updateListView()
{
    DBank con;
    con.con_open();

    QSqlQueryModel *modell = new QSqlQueryModel();
    QSqlQueryModel *oldModell = NULL;

    QSqlQuery qry = QSqlQuery(con.myDB);
    qry.prepare("select EventName, ID from Event");
    qry.exec();
    modell->setQuery(qry);

    oldModell = (QSqlQueryModel*)ui->listView->model();
    ui->listView->setModel(modell);

    if(oldModell)
        delete oldModell;
    con.con_closed();
}


//Nach Doppelklick auf einen Event-Eintrag öffnet
//sich ein neues Fenster
//  -a) entweder ohne Teilnehmer-Einträgen oder
//  -b) schon mit bereits eingetragenen Teilnehmern
void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
	Q_UNUSED(index);
    //Teilnehmer *Fenster = new Teilnehmer(0, meineId);
    QVariant row = ui->listView->currentIndex().data();
    QSqlQueryModel *model = (QSqlQueryModel*)ui->listView->model();
    QSqlRecord record = model->record(ui->listView->currentIndex().row());
    QSqlField field_ID = record.field("ID");

    QString ID = field_ID.value().toString();

    Teilnehmer teilnehmer(this, ID);
    teilnehmer.setModal(true);
    teilnehmer.setWindowTitle("Event "+row.toString());

    teilnehmer.exec();
}


//Eventname, der aktiviert wurde, mit remove-pBtn löschen
//inklusive der an diesem Event beteiligten Teilnehmern.
void MainWindow::on_pBtn_remove_Event_clicked()
{

    QSqlQueryModel *model = (QSqlQueryModel*)ui->listView->model();
    QSqlRecord record = model->record(ui->listView->currentIndex().row());
    QSqlField field_ID = record.field("ID");
    QSqlField field_EventName = record.field("EventName");

    QMessageBox msg;
    msg.setText("Achtung es werden auch alle Teilnehmer, \n die zu diesem Event gehören, gelöscht! \n\n Soll das Event: \n \" " +field_EventName.value().toString()+ "\"\n unwiederruflich gelöscht werden?");
    msg.setWindowTitle("Eintrag entfernen");
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg.setIcon(QMessageBox::Critical);
    msg.setButtonText(QMessageBox::Yes, "Ja");
    msg.setButtonText(QMessageBox::No, "Nein");
    msg.setDefaultButton(QMessageBox::No);

    if (msg.exec() == QMessageBox::Yes)
    {
        DBank a;
        QString ID = field_ID.value().toString();
        a.removeEvent(ID);
        qDebug()<< field_ID.value().toString();
        updateListView();
    }
    else
    {
        qDebug()<<"EventName-Eintrag wird nicht gelöscht.";
    }
}

//Der "-"-PBtn (remove_Event) wird erst aktiv,
//wenn ein Eintrag ausgewählt wurde
void MainWindow::on_listView_clicked(const QModelIndex &index)
{
	Q_UNUSED(index);
    ui->pBtn_remove_Event->setEnabled(true);
}


  //Ausleitung als csv-Datei
void MainWindow::on_pushButton_clicked()
{
    QSqlQueryModel *model = (QSqlQueryModel*)ui->listView->model();
    QSqlRecord record = model->record(ui->listView->currentIndex().row());
    QSqlField field_ID = record.field("ID");

    DBank con;
    con.con_open();

    QSqlQuery query(con.myDB);
    query.prepare("SELECT t.Vorname as Vorname, t.Nachname as Nachname, time(t.Endzeit-e.Startzeit, \"unixepoch\") from TEILNEHMER as t JOIN EVENT as e ON e.ID == t.EVENT_ID where e.ID = '"+field_ID.value().toString()+"' ORDER BY t.Endzeit ASC");

    if(query.exec())
    {
       QSqlQueryModel *model=new QSqlQueryModel();
        model->setQuery(query);

        QString DB_Inhalt;
        int rows=model->rowCount();
        int columns=model->columnCount();

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                DB_Inhalt += model->data(model->index(i,j)).toString();
                DB_Inhalt += "; ";
            }
            DB_Inhalt += "\n";
        }

        QString filename = QFileDialog::getSaveFileName(this,"Speichern unter","C://","All files (*.*);;ExcelFile(*.csv)");

        QFile csvfile(filename);
        if(csvfile.open(QIODevice::WriteOnly|QIODevice::Truncate))
        {
            QTextStream out(&csvfile);
            out<<DB_Inhalt;
        }
        csvfile.close();
    }
}
