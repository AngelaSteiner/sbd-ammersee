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
