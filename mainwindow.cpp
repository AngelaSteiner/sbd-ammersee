#include "mainwindow.h"
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
    ui->pBtn_remove_Event->setEnabled(true);
}


