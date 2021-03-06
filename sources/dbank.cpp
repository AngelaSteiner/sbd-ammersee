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
#include "sources/dbank.h"

DBank::DBank()

//DBank::DBank(QString path)
{
    myDB = QSqlDatabase::addDatabase("QSQLITE");

    //Pfad exe-Datei
    QString db_path = QDir::currentPath();
    qDebug() <<"exe"<<db_path;

    //Pfad aktivieren, wenn release gemacht wird
    db_path = QString("%1%2").arg(db_path).arg("/Schwimm.db");

    //Pfad aktivieren, wenn aus Qt heraus gestartet wird
    //db_path = QString("%1%2").arg(db_path).arg("/debug/Schwimm.db");
    qDebug() <<"Pfad: "<<db_path;
    myDB.setDatabaseName(db_path);
    qDebug() << "Aufruf Konstruktor";
}

 //Verbindung zur Datenbank herstellen
bool DBank::con_open()
{
    if(!(myDB.open()))
       {
        qDebug() << "Error: connection with database fail";
        return 0;
       }
       else
       {
        qDebug() << "connect....";
        return 1;
       }
}

//Verbindung zur Datenbank trennen
void DBank::con_closed()
{
    myDB.close();
    myDB.removeDatabase(QSqlDatabase::defaultConnection);
}


//Neuer Eintrag in Datenbank "Tabelle Event"
void DBank::addEvent(QString str)
{
    if(con_open())
    {

    if (!str.isEmpty())
        {
            //Objekt für DB-Abfrage erzeugen
            QSqlQuery qryadd;

            qryadd.prepare("insert into Event (EventName,Startzeit,done) values('"+str+"',+strftime('%s','now'),0)");


            if(qryadd.exec())
            {
                // Meldung hinzugefuegt oder eher nicht? -> Thilo fragen ;
            }
            else
            {
                qDebug() << "add Event failed: " << qryadd.lastError();
            }

         }
         else
         {
         QMessageBox::critical(0, "Meldung aus der Datenbank", "Bitte einen Eventnamen eingeben!");
         }

     }
     else
     {
        qDebug() << "add Event failed: Event cannot be empty";
     }

}

 //Eintrag aus Datenbank "Tabelle Event" mit den zugehörigen
 //Teilnehmern aus "Tabelle Teilnehmer" entfernen
void DBank::removeEvent(QString EventID)
{
    if (con_open())
    {
        QSqlQuery qry_remove;
        qry_remove.prepare("delete from EVENT where ID = '"+EventID+"' ");
        qry_remove.exec();

        QSqlQuery teilnehmer_remove;
        teilnehmer_remove.prepare("delete from Teilnehmer where Event_ID = '"+EventID+"' ");
        teilnehmer_remove.exec();
    }

}

  //Neuer Eintrag in Datenbank "Tabelle Teilnehmer"
void DBank::addTeilnehmer(QString E_ID, QString VN, QString NN, QString RFID)
{
    if(con_open())
    {

    if (!RFID.isEmpty())
        {
            //Objekt für DB-Abfrage erzeugen
            QSqlQuery qryaddTeilnehmer;

            qryaddTeilnehmer.prepare("insert into Teilnehmer (Vorname,Nachname,IDTAG,Event_ID) values('"+VN+"','"+NN+"','"+RFID+"','"+E_ID+"')");

            if(qryaddTeilnehmer.exec())
            {
             // Meldung hinzugefuegt oder eher nicht? -> Thilo fragen ;
            }
            else
            {
                qDebug() << "add Teilnehmer failed: " << qryaddTeilnehmer.lastError();
            }

        }
        else
        {
          QMessageBox::critical(0, "Meldung aus der Datenbank", "Bitte einen Teilnehmer eingeben!");
        }

    }
    else
    {
     qDebug() << "add Teilnehmer failed: Event cannot be empty";
    }

}

 //Eintrag aus Datenbank "Tabelle Teilnehmer" entfernen
void DBank::removeTeilnehmer(QString TlnID)
{
    if (con_open())
    {
        QSqlQuery teilnehmer_remove;
        teilnehmer_remove.prepare("delete from Teilnehmer where ID = '"+TlnID+"' ");
        teilnehmer_remove.exec();
    }
}

  //Eintrag der Startzeit in Datenbank "Tabelle Event"
void DBank::setStartzeit(QString E_ID)
{
    if(con_open())
    {
       QSqlQuery qry_start;
       qry_start.prepare("update Event set Startzeit = +strftime('%s','now') where ID = '"+E_ID+"' ");
      if(qry_start.exec())
      {
          qDebug() << "add Startzeit in Event eingetragen.";
      }
      else
      {
          qDebug() << "add Startzeit in Event failed: " << qry_start.lastError();
      }

    }

}


//Abfrage, ob das Event bereits vorbei ist, um Eingaben
//zu sperren.
bool DBank::isEventDone(QString E_ID)
{
    int Event_done = 0;

    if(con_open())
    {
        QSqlQuery qry("select done from Event where ID = '"+E_ID+"' LIMIT 1");

        if(qry.exec() && qry.next())
        {
             Event_done = qry.value("done").toInt();
             qDebug()<< " record aus qryabfrage done"<<Event_done;
        }
    }

    if(Event_done == 1)
    {
        return 1;
    }
   else
    {
        return 0;
    }

}


//Das "Event" wird in der Datenbank gekennzeichnet, um
//alle Eingaben zu sperren.
void DBank::setEventDone(QString E_ID)
{
    if(con_open())
    {
        QSqlQuery qry("update Event set done = 1 where ID = '"+E_ID+"' ");

        if(qry.exec() && qry.next())
        {
             qDebug()<< " Event is set done";
        }
    }

}

//Rückgabe von Datum und Startzeit als int (Sekunden seit 01.01.1970)
uint DBank::getDatumStartzeitfromEvent(QString E_ID)
{
    uint Datum = 0;

    if(!E_ID.isEmpty())
    {
        if(con_open())
        {
            QSqlQuery qry("select Startzeit from Event where ID = '"+E_ID+"' LIMIT 1");

            if(qry.exec() && qry.next())
            {
                 Datum = qry.value("Startzeit").toInt();
                 qDebug()<< " record aus qryabfrage Datum"<<Datum;
            }
        }
    }

   return Datum;
}

//Rückgabe der Anzahl an Teilnehmer, die sich noch im Wasser befinden
//Auswertung anhand Endzeit = 0
int DBank::getCountSchwimmerWithEndzeitNull(QString E_ID)
{
    int count = 0;

    if(con_open())
    {
        QSqlQuery Anzahl;
        Anzahl.prepare("Select Endzeit from Teilnehmer where Event_ID = '"+E_ID+"' ");

        if(Anzahl.exec())
        {
            while (Anzahl.next())
            {
                QSqlRecord record = Anzahl.record();
                QSqlField field = record.field("Endzeit");

                qDebug()<<field.value().toString();
                QString Endz = field.value().toString();

                if(Endz.isNull())
                {
                    count++;
                }
            }
        }
    }

    return count;
}

//Eintrag der Endzeit in Datenbank "Tabelle Teilnehmer"
void DBank::setEndzeit(QString RFID)
{
    if(con_open())
    {
       QSqlQuery setEndzeit;
       setEndzeit.prepare("update Teilnehmer set Endzeit = +strftime('%s','now') where IDTAG = '"+RFID+"' ");
      if(setEndzeit.exec())
      {
          qDebug() <<  "Endzeit beim Schwimmer eingetragen.";
      }
      else
      {
          qDebug() << "Endzeit beim Schwimmer eintragen failed: " << setEndzeit.lastError();
      }

    }
}
