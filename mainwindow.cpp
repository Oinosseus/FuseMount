#include "mainwindow.h"

#include <QTreeWidgetItem>
#include <QStringList>

#include "mounttreewidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // list view
    MountTreeWidget *mountTree = new MountTreeWidget();
    this->setCentralWidget(mountTree);

    // add test items
    new QTreeWidgetItem(mountTree, QStringList() << "mnt1" << "/home/mnt/1" << "user@host:/path/to/dir1" << "unmounted");
    new QTreeWidgetItem(mountTree, QStringList() << "mnt2" << "/home/mnt/2" << "user@host:/path/to/dir2" << "mounting");
    new QTreeWidgetItem(mountTree, QStringList() << "mnt3" << "/home/mnt/3" << "user@host:/path/to/dir3" << "mounted");
}

MainWindow::~MainWindow()
{
}
