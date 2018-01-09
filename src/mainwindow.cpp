#include "mainwindow.h"

#include <QApplication>
#include <QObject>
#include <QTreeWidgetItem>
#include <QStringList>
#include <QSettings>

#include <KActionCollection>
#include <KStandardAction>

#include "mounttreewidget.h"

MainWindow::MainWindow(QWidget *parent) : KXmlGuiWindow(parent)
{
    // quit action
    KStandardAction::quit(qApp, SLOT(closeAllWindows()), actionCollection());

    // list view
    MountTreeWidget *mountTree = new MountTreeWidget();
    this->setCentralWidget(mountTree);

    // kde framework
    this->setupGUI();
}

MainWindow::~MainWindow()
{
}
