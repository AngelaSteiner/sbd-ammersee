#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <event_add.h>
#include <teilnehmer.h>
#include <QMessageBox>
#include <QString>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:
    //Hinzufügen eines neuen Event-Eintrages über "+"-Button
    void on_pBtn_add_Event_clicked();

    //Nach Doppelklick auf einen Event-Eintrag öffnet
    //sich ein neues Fenster
    //  -a) entweder ohne Teilnehmer-Einträgen oder
    //  -b) schon mit bereits eingetragenen Teilnehmern
    void on_listView_doubleClicked(const QModelIndex &index);

    //Eintrag aus Datenbank "Tabelle Event" entfernen
    //inklusive der an diesem Event beteiligten Teilnehmern.
    void on_pBtn_remove_Event_clicked();

    //Der "-"-PBtn (remove_Event) wird erst aktiv,
    //wenn ein Eintrag ausgewählt wurde
    void on_listView_clicked(const QModelIndex &index);

public slots:
    /*
     * Diese Funktion gibt den aktuellen Inhalt der
     * Datenbank "Tabelle Event" für das ListView aus.
     * Also Ausgabe bestehender Event-Einträge
    */
    void updateListView();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
