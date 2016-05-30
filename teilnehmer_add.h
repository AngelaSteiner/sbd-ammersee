#ifndef TEILNEHMER_ADD_H
#define TEILNEHMER_ADD_H

#include <QDialog>
#include <teilnehmer.h>
#include <dbank.h>
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
