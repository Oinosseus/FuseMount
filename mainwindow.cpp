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

    // add test items
    MountItemGroup *g1 = new MountItemGroup(mountTree, "Group1");
    new MountItem(g1, QStringList() << "mnt1" << "/home/mnt/1" << "user@host:/path/to/dir1" << "unmounted");
    new MountItem(g1, QStringList() << "mnt2" << "/home/mnt/2" << "user@host:/path/to/dir2" << "mounting");
    new MountItem(mountTree, QStringList() << "mnt3" << "/home/mnt/3" << "user@host:/path/to/dir3" << "mounted");
}

MainWindow::~MainWindow()
{
}
