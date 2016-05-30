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
