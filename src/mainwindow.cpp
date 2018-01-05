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

    // restore window settings
    QSettings settings;
    this->restoreGeometry(settings.value("MainWindow/geometry").toByteArray());
    this->restoreState(settings.value("MainWindow/windowState").toByteArray());

    // kde framework
    this->setupGUI();
}

MainWindow::~MainWindow()
{
    QSettings settings;

    // save window settings
    settings.setValue("MainWindow/geometry", this->saveGeometry());
    settings.setValue("MainWindow/windowState", this->saveState());
}
