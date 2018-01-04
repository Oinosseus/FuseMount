#include "mainwindow.h"
#include <QCoreApplication>
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Oinosseus");
    QCoreApplication::setOrganizationDomain("private");
    QCoreApplication::setApplicationName("SshfsMount");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
