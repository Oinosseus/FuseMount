#include "mounttreewidget.h"

#include <QMenu>
#include <QAction>
#include <QFile>
#include <QDir>

#include <mountitem.h>
#include <mountitemgroup.h>

MountTreeWidget::MountTreeWidget(QWidget *parent) : QTreeWidget(parent)
{
    this->setHeaderLabels(QStringList() << "Name" << "mountpoint" << "server" << "state");
    this->setEditTriggers(QAbstractItemView::DoubleClicked);
}

MountTreeWidget::~MountTreeWidget()
{
    // file format: Name, GroupName, MountPoint, Host\n
    QFile file(QDir::home().absoluteFilePath(".sshfsmount"));
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    // save items
    file.write("Foo Bar");
    for (int i=0; i < this->topLevelItemCount(); ++i) {
        QTreeWidgetItem *twi = this->topLevelItem(i);

        if (twi->type() == MOUNTITEM_TYPE) {
            file.write(twi->text(0) + ", ," + twi->text(1) + ", " + twi->text(2) + "\n");
        } else if (twi->type() == MOUNTITEMGROUP_TYPE) {
            file.write(twi->text(0) + "," + twi->text(0) + "\n");
        }
    }
}

void MountTreeWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QTreeWidgetItem *twi = this->currentItem();
    QMenu menu(this);

    // action group new
    QAction actAddNewGroup(tr("add new group"), this);
    menu.addAction(&actAddNewGroup);
    connect(&actAddNewGroup, SIGNAL(triggered()), this, SLOT(slotAddNewGroup()));

    // action group delete
    QAction actDeleteGroup(tr("delete group"), this);
    if (twi && twi->type() == MOUNTITEMGROUP_TYPE) {
        actDeleteGroup.setText(tr("delete group") + " '" + twi->text(0) + "'");
        connect(&actDeleteGroup, SIGNAL(triggered()), this, SLOT(slotDeleteGroup()));
        menu.addAction(&actDeleteGroup);
    }

    menu.addSeparator();

    // action mount new
    QAction actAddNewMount(tr("add new mount"), this);
    connect(&actAddNewMount, SIGNAL(triggered()), this, SLOT(slotAddNewMount()));
    menu.addAction(&actAddNewMount);

    // action mount delete
    QAction actDeleteMount(tr("delete mount"), this);
    if (twi && twi->type() == MOUNTITEM_TYPE) {
        actDeleteMount.setText(tr("delete mount") + " '" + twi->text(0) + "'");
        connect(&actDeleteMount, SIGNAL(triggered()), this, SLOT(slotDeleteMount()));
        menu.addAction(&actDeleteMount);
    }

    // execute menu
    menu.exec(event->globalPos());
    this->sortItems(0, Qt::AscendingOrder);
}

void MountTreeWidget::slotAddNewGroup()
{
    new MountItemGroup(this, tr("new group"));
}

void MountTreeWidget::slotDeleteGroup()
{
    QTreeWidgetItem *twi = this->currentItem();
    if (twi) delete(twi);
}

void MountTreeWidget::slotAddNewMount()
{
    QTreeWidgetItem *twi = this->currentItem();

    QStringList columns;
    columns << tr("new mount") << tr("/local/path") << tr("user@host:/remote/path");

    if (twi && twi->type() == MOUNTITEMGROUP_TYPE) {
        try {
            MountItemGroup *twig = dynamic_cast<MountItemGroup *>(twi);
            if (twig) new MountItem(twig, columns);
            else new MountItem(this, columns);
        } catch(std::bad_cast) {
            new MountItem(this, columns);
        }
    } else {
        new MountItem(this, columns);
    }
}

void MountTreeWidget::slotDeleteMount()
{
    QTreeWidgetItem *twi = this->currentItem();
    if (twi) delete(twi);
}
