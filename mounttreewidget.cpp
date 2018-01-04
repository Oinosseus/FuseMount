#include "mounttreewidget.h"

#include <QMenu>
#include <QAction>

#include <mountitem.h>
#include <mountitemgroup.h>

MountTreeWidget::MountTreeWidget(QWidget *parent) : QTreeWidget(parent)
{
    this->setHeaderLabels(QStringList() << "Name" << "mountpoint" << "server" << "state");
    this->setEditTriggers(QAbstractItemView::DoubleClicked);
}

void MountTreeWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QTreeWidgetItem *twi = this->currentItem();

    QMenu menu(this);

    // group administrative actions
    menu.addAction(new QAction(tr("add new group")));
    if (twi->type() == MOUNTITEMGROUP_TYPE) {
        menu.addAction(new QAction(tr("delete group") + " " + twi->text(0)));
    }
    menu.addSeparator();

    // mount administrative actions
    menu.addAction(new QAction(tr("add new mount")));
    if (twi->type() == MOUNTITEM_TYPE) {
        menu.addAction(new QAction(tr("delete mount") + " " + twi->text(0)));
    }
    menu.addSeparator();


    menu.addAction(new QAction("Foo2"));
    menu.exec(event->globalPos());
}
