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

    // load from file
    MountItem *mi = Q_NULLPTR;
    MountItemGroup *mig = Q_NULLPTR;
    QFile file(QDir::home().absoluteFilePath(".sshfsmount"));
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        while (!file.atEnd()) {
            QByteArray line = file.readLine();
            QList<QByteArray> elements = line.split(',');

            if (elements.size() >= 4) {

                // check for new group
                QString groupName = QString::fromUtf8(elements.at(0)).trimmed();
                if (groupName.length() == 0) {
                    mig = Q_NULLPTR;
                } else if (!mig || mig->text(0) != groupName) {
                    mig = new MountItemGroup(this, groupName);
                }

                QString mountName = QString::fromUtf8(elements.at(1)).trimmed();
                QString localPath = QString::fromUtf8(elements.at(2)).trimmed();
                QString host = QString::fromUtf8(elements.at(3)).trimmed();

                if (mig) new MountItem(mig, QStringList() << mountName << localPath << host);
                else new MountItem(this, QStringList() << mountName << localPath << host);

            }
        }
    }
}

MountTreeWidget::~MountTreeWidget()
{
    // helper variables
    MountItem *mi;
    MountItemGroup *mig;
    QTreeWidgetItem *twi;

    // file format: GroupName, Name, MountPoint, Host\n
    QFile file(QDir::home().absoluteFilePath(".sshfsmount"));
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {

        // save items
        for (int i=0; i < this->topLevelItemCount(); ++i) {
            twi = this->topLevelItem(i);

            // save mount
            if (twi->type() == MOUNTITEM_TYPE) {
                mi = dynamic_cast<MountItem *>(twi);
                if (mi) {
                    mi->save2File(file);
                }

            // save group
            } else if (twi->type() == MOUNTITEMGROUP_TYPE) {
                mig = dynamic_cast<MountItemGroup *>(twi);
                if (mig) {

                    // save sub items
                    for (int j=0; j<mig->childCount(); ++j) {
                        mi = dynamic_cast<MountItem *>(mig->child(j));

                        // save mount
                        if (mi && mi->type() == MOUNTITEM_TYPE) {
                            mi->save2File(file);
                        }
                    }
                }
            }
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
