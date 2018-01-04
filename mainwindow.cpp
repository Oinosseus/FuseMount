#include "mainwindow.h"

#include <QTreeWidgetItem>
#include <QStringList>
#include <QSettings>

#include "mounttreewidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // list view
    MountTreeWidget *mountTree = new MountTreeWidget();
    this->setCentralWidget(mountTree);

    // restore window settings
    QSettings settings;
    this->restoreGeometry(settings.value("MainWindow/geometry").toByteArray());
    this->restoreState(settings.value("MainWindow/windowState").toByteArray());
}

MainWindow::~MainWindow()
{
    QSettings settings;

    // save window settings
    settings.setValue("MainWindow/geometry", this->saveGeometry());
    settings.setValue("MainWindow/windowState", this->saveState());
}
