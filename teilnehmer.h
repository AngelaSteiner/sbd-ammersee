#ifndef TEILNEHMER_H
#define TEILNEHMER_H

#include <QDialog>
#include <teilnehmer_add.h>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QDateTime>
#include <duringevent.h>
#include <dbank.h>
#include <QStandardItemModel>



namespace Ui {
class Teilnehmer;
}

class Teilnehmer : public QDialog
{
    Q_OBJECT

public:
     //Bei Anlage des Objektes wird auch gleich die Variable Event-ID mit angelegt
    explicit Teilnehmer(QWidget *parent = 0, QString Event_ID_ = "");
    ~Teilnehmer();

public slots:
    /* Diese Funktion gibt den aktuellen Inhalt der
     * Datenbank "Tabelle Event" für das ListView aus.
     * Also Ausgabe bestehender Event-Einträge*/
    void updateTW();

    //Das Datum wird im oberen Teil des Fensters angezeigt
    void setDatumUeberschrift();


private slots:
    // Wenn über den "+"-Button ein Teilnehmer hinzugefügt
    // werden soll, dann öffnet sich ein neuer modaler Dialog.
    // Nach Eingabe in diesen Dialog soll der hinzugefügte Eintrag
    // im TableView ersichtlich sein.
    // Dazu ist der connect-Befehl nötig
    void on_pBn_Teilnehmer_add_clicked();

    //Der "-"-PBtn (remove_Teilnehmer) wird erst aktiv,
    //wenn ein Eintrag ausgewählt wurde und das Event noch
    //nicht beendet wurde.
    void on_tableView_clicked(const QModelIndex &index);

    //Abfrage des Event-Status in der Datenbank
    //um PBtn's zu disablen
    void doneAbfrage();

    //Update der Startzeit des Events in der Datenbank
    //Update der FensterÜberschrift (Datum / Startzeit)
    //Öffnen eines neuen Fensters
    void on_pBtn_Start_clicked();

    //Teilnehmer, der aktiviert wurde, mit remove-pBtn löschen
    void on_pBtn_Teilnehmer_remove_clicked();

    //Update des TableView nach Beendigung des Events
    //Die Auflistung des Inhaltes ist sortiert nach
    //der benötigten Zeit eines jeden Teilnehmers
    //Also Auswertung
    void update_TV_orderedByTime();


private:
    Ui::Teilnehmer *ui;
    QString Event_ID;

};

#endif // TEILNEHMER_H
