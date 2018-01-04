#include "mainwindow.h"

#include <QTreeWidgetItem>
#include <QStringList>
#include <QSettings>

#include "mounttreewidget.h"
#include "mountitemgroup.h"
#include "mountitem.h"

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
    // save window settings
    QSettings settings;
    settings.setValue("MainWindow/geometry", this->saveGeometry());
    settings.setValue("MainWindow/windowState", this->saveState());
}
