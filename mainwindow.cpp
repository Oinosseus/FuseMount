#include "mainwindow.h"

#include <QTreeWidgetItem>
#include <QStringList>

#include "mounttreewidget.h"
#include "mountitemgroup.h"
#include "mountitem.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // list view
    MountTreeWidget *mountTree = new MountTreeWidget();
    this->setCentralWidget(mountTree);
}

MainWindow::~MainWindow()
{
}
