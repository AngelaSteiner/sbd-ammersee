#include "teilnehmer.h"
#include "ui_teilnehmer.h"
#include <QDate>

Teilnehmer::Teilnehmer(QWidget *parent, QString Event_ID_) :
    QDialog(parent),
    ui(new Ui::Teilnehmer)
{
    ui->setupUi(this);
    Event_ID = Event_ID_;

    //Abfrage, ob Eingaben gesperrt werden müssen
    doneAbfrage();

    //bei FensterÖffnung wird das TableWidget aktualisiert
    updateTW();

    //Überschrift einfügen
    setDatumUeberschrift();
}

Teilnehmer::~Teilnehmer()
{
    delete ui;
}


//Das Datum wird im oberen Teil des Fensters angezeigt
void Teilnehmer::setDatumUeberschrift()
{
    DBank a;  
    QDateTime d = QDateTime::fromTime_t(a.getDatumStartzeitfromEvent(Event_ID));
    ui->lbl_Datum->setText(d.date().toString("dd.MM.yyyy"));

    a.con_closed();
}

//Abfrage des Event-Status in der Datenbank
//um PBtn's zu disablen
void Teilnehmer::doneAbfrage()
 {
      DBank a;
      if(a.isEventDone(Event_ID)== 1)
      {
         ui->pBtn_Start->setEnabled(false);
         ui->pBn_Teilnehmer_add->setEnabled(false);
         QMessageBox::information(this,"Eventstatus","Das Event ist bereits beendet.\nEs können keine Eingaben mehr getätigt werden.");
      }
 }

// Wenn über den "+"-Button ein Teilnehmer hinzugefügt
// werden soll, dann öffnet sich ein neuer modaler Dialog.
// Nach Eingabe in diesen Dialog soll der hinzugefügte Eintrag
// im TableView ersichtlich sein.
// Dazu ist der connect-Befehl nötig
void Teilnehmer::on_pBn_Teilnehmer_add_clicked()
{
    teilnehmer_add teilnehmer(this, Event_ID);
    teilnehmer.setModal(true);
    connect(&teilnehmer,SIGNAL(update_teilnehmer_TW()),this,SLOT(updateTW()));


    teilnehmer.exec();
}

/*
 * Diese Funktion gibt den aktuellen Inhalt der
 * Datenbank "Tabelle Teilnehmer" für das TableView aus.
 * Also Ausgabe bestehender Teilnehmer-Einträge
 *
*/
void Teilnehmer::updateTW()
 {

     if(!Event_ID.isEmpty())
     {
     DBank con;
     con.con_open();

     QSqlQueryModel *model = new QSqlQueryModel();
     QSqlQueryModel *oldModell = NULL;

     QSqlQuery qry = QSqlQuery(con.myDB);
     qry.prepare("select ID, Vorname, Nachname, IDTAG from Teilnehmer where Event_ID = '"+Event_ID+"' ");//And Endzeit Is NULL ");
     qry.exec();
     model->setQuery(qry);

     oldModell = (QSqlQueryModel*)ui->tableView->model();
     ui->tableView->setModel(model);
     ui->tableView->setColumnHidden(0,true);

     if(oldModell)
         delete oldModell;

     con.con_closed();
     }
 }

//Der "-"-PBtn (remove_Teilnehmer) wird erst aktiv,
//wenn ein Eintrag ausgewählt wurde und das Event noch
//nicht beendet wurde.
void Teilnehmer::on_tableView_clicked(const QModelIndex &index)
{
    DBank a;
    if(a.isEventDone(Event_ID)== 1)
    {
         ui->pBtn_Teilnehmer_remove->setEnabled(false);
    }
    else
        ui->pBtn_Teilnehmer_remove->setEnabled(true);
}


//Update der Startzeit des Events in der Datenbank
//Update der FensterÜberschrift (Datum / Startzeit)
//Öffnen eines neuen Fensters
void Teilnehmer::on_pBtn_Start_clicked()
{
    DBank a;

    a.setStartzeit(Event_ID);
    QDateTime d = QDateTime::fromTime_t(a.getDatumStartzeitfromEvent(Event_ID));
    ui->lbl_Datum->setText(d.date().toString("dd.MM.yyyy"));
    ui->lbl_Startzeit->setText(d.time().toString("HH:mm:ss"));


    duringevent Fenster(this,Event_ID);
    Fenster.setModal(true);

    connect(&Fenster,SIGNAL(update_TW_Finish()),this,SLOT(update_TV_orderedByTime()));

    a.con_closed();
    Fenster.exec();

}


//Teilnehmer, der aktiviert wurde, mit remove-pBtn löschen
void Teilnehmer::on_pBtn_Teilnehmer_remove_clicked()
{
    QSqlQueryModel *model = (QSqlQueryModel*)ui->tableView->model();
    QSqlRecord record = model->record(ui->tableView->currentIndex().row());
    QSqlField field_ID = record.field(0);
    QSqlField field_Nachname = record.field(2);

    QMessageBox msg;
    msg.setText("Soll der Teilnehmer \n \"" +field_Nachname.value().toString()+"\"\n unwiederruflich gelöscht werden?");
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
        a.removeTeilnehmer(ID);

        updateTW();
    }
    else
    {
        qDebug()<<"EventName-Eintrag wird nicht gelöscht.";
    }
}

//Update des TableView nach Beendigung des Events
//Die Auflistung des Inhaltes ist sortiert nach
//der benötigten Zeit eines jeden Teilnehmers
//Also Auswertung
void Teilnehmer::update_TV_orderedByTime()
{
    ui->pBtn_Start->setEnabled(false);
    ui->pBtn_Teilnehmer_remove->setEnabled(false);
    ui->pBn_Teilnehmer_add->setEnabled(false);

    DBank a;
    a.con_open();
    uint Startzeit = a.getDatumStartzeitfromEvent(Event_ID);

    QStandardItemModel *model = new QStandardItemModel(0,4,this);
    model->setHeaderData(1,Qt::Horizontal,tr("Vorname"));
    model->setHeaderData(2,Qt::Horizontal,tr("Nachname"));
    model->setHeaderData(3,Qt::Horizontal,tr("benötigte Zeit"));

    QSqlQuery qry(a.myDB);
    qry.prepare("SELECT Vorname,Nachname,Endzeit from TEILNEHMER where Event_ID = '"+Event_ID+"' ORDER BY Endzeit ASC");
    if(qry.exec())
    {

        while (qry.next())
        {
           uint Endzeit = 0;

           QList<QStandardItem*> NewRow;
            //Einfügen einer Leerspalte
           QStandardItem *newColumn = new QStandardItem();
           newColumn = new QStandardItem();
           NewRow.append(newColumn);

           QString Vorname = qry.value("Vorname").toString();
           newColumn = new QStandardItem(Vorname);
           NewRow.append(newColumn);

           QString Nachname = qry.value("Nachname").toString();
           newColumn = new QStandardItem(Nachname);
           NewRow.append(newColumn);

           Endzeit = qry.value("Endzeit").toInt();
           if(Endzeit == NULL)
           {
               Endzeit = Startzeit;
           }
           Endzeit = Endzeit - Startzeit;
           uint secs = Endzeit;
           uint mins = (secs / 60) % 60;
           uint hours = (secs / 3600);
           secs = secs % 60;
           QString ben_Zeit = (QString("%1:%2:%3").arg(hours, 2, 10,
                               QLatin1Char('0')).arg(mins, 2, 10,
                               QLatin1Char('0')).arg(secs, 2, 10,
                               QLatin1Char('0')));
           newColumn = new QStandardItem(ben_Zeit);
           NewRow.append(newColumn);

           model->appendRow(NewRow);
        }
        ui->tableView->setModel(model);
        ui->tableView->show();
    }
}


