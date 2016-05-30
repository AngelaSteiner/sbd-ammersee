#include "mainwindow.h"
#include <QApplication>
#include <dbank.h>
#include <QMessageBox>
#include <QString>
#include <QLabel>
#include <QFileDialog>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
