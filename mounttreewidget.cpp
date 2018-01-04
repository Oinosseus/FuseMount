#include "mounttreewidget.h"

#include <QMenu>
#include <QAction>

MountTreeWidget::MountTreeWidget(QWidget *parent) : QTreeWidget(parent)
{
    this->setHeaderLabels(QStringList() << "Name" << "mountpoint" << "server" << "state");
}

void MountTreeWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(new QAction("Foo1"));
    menu.addAction(new QAction("Foo2"));
    menu.exec(event->globalPos());
}
