#include "mounttreewidget.h"

#include <QMenu>
#include <QAction>
#include <QFile>
#include <QDir>
#include <QProcess>
#include <QMessageBox>
#include <QInputDialog>

#define TREEWIDGETITEMTYPE_GROUP 1
#define TREEWIDGETITEMTYPE_MOUNT 2

MountTreeWidget::MountTreeWidget(QWidget *parent) : QTreeWidget(parent)
{
    this->wallet = Q_NULLPTR;

    this->setHeaderLabels(QStringList() << "Name" << "Host" << "Mount");
    this->setEditTriggers(QAbstractItemView::DoubleClicked);

    // load from file
    QTreeWidgetItem *lastGroupItem = Q_NULLPTR;
    QFile file(QDir::home().absoluteFilePath(".sshfsmount"));
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        while (!file.atEnd()) {
            QByteArray line = file.readLine();
            QList<QByteArray> elements = line.split(',');

            if (elements.size() >= 4) {

                // check for new group
                QString groupName = QString::fromUtf8(elements.at(0)).trimmed();
                if (groupName.length() == 0) {
                    lastGroupItem = Q_NULLPTR;
                } else if (!lastGroupItem || lastGroupItem->text(0) != groupName) {
                    lastGroupItem = this->newGroupItem(groupName);
                }

                // get attributes
                QString mountName = QString::fromUtf8(elements.at(1)).trimmed();
                QString host = QString::fromUtf8(elements.at(2)).trimmed();
                QString mount = QString::fromUtf8(elements.at(3)).trimmed();

                // instantiate mount
                this->newMountItem(mountName, host, mount, lastGroupItem);
            }
        }
    }
}

MountTreeWidget::~MountTreeWidget()
{
    // close wallet
    if (this->wallet) delete this->wallet;

    // helper variables
    QTreeWidgetItem *twi;

    // file format: GroupName, Name, Host, Mount\n
    QFile file(QDir::home().absoluteFilePath(".sshfsmount"));
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {

        // save items
        for (int i=0; i < this->topLevelItemCount(); ++i) {
            twi = this->topLevelItem(i);

            // save mount
            if (twi->type() == TREEWIDGETITEMTYPE_MOUNT) {
                QString line;
                line += ", " + twi->text(0);
                line += ", " + twi->text(1);
                line += ", " + twi->text(2);
                line += "\n";
                file.write(line.toUtf8());

            // save group
            } else if (twi->type() == TREEWIDGETITEMTYPE_GROUP) {
                QTreeWidgetItem *twi2 = Q_NULLPTR;
                for (int j=0; j<twi->childCount(); ++j) {
                    twi2 = twi->child(j);
                    QString line;
                    line += twi->text(0);
                    line += ", " + twi2->text(0);
                    line += ", " + twi2->text(1);
                    line += ", " + twi2->text(2);
                    line += "\n";
                    file.write(line.toUtf8());
                }
            }
        }
    }
}

void MountTreeWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QTreeWidgetItem *twi = this->currentItem();
    QMenu menu(this);

    // (un)mount options
    QAction actUnMountItem(tr("unmount"));
    QAction actMountItem(tr("mount"), this);
    if (twi && twi->type() == TREEWIDGETITEMTYPE_MOUNT) {
        actUnMountItem.setText(tr("unmount") + " '" + twi->text(0) + "'");
        connect(&actUnMountItem, SIGNAL(triggered(bool)), this, SLOT(slotUnMountItem()));
        menu.addAction(&actUnMountItem);
        actMountItem.setText(tr("mount") + " '" + twi->text(0) + "'");
        connect(&actMountItem, SIGNAL(triggered(bool)), this, SLOT(slotMountItem()));
        menu.addAction(&actMountItem);
    }

    menu.addSeparator();

    // action mount new
    QAction actAddNewMount(tr("add new mount"), this);
    connect(&actAddNewMount, SIGNAL(triggered()), this, SLOT(slotAddNewMount()));
    menu.addAction(&actAddNewMount);

    // action group new
    QAction actAddNewGroup(tr("add new group"), this);
    menu.addAction(&actAddNewGroup);
    connect(&actAddNewGroup, SIGNAL(triggered()), this, SLOT(slotAddNewGroup()));

    menu.addSeparator();

    // action delete
    QAction actDeleteMount(tr("delete"), this);
    if (twi) {
        actDeleteMount.setText(tr("delete") + " '" + twi->text(0) + "'");
        connect(&actDeleteMount, SIGNAL(triggered()), this, SLOT(slotDeleteItem()));
        menu.addAction(&actDeleteMount);
    }

    // execute menu
    menu.exec(event->globalPos());
    this->sortItems(0, Qt::AscendingOrder);
}

QTreeWidgetItem *MountTreeWidget::newGroupItem(const QString &name)
{
    QTreeWidgetItem *groupItem = new QTreeWidgetItem(this, QStringList() << name, TREEWIDGETITEMTYPE_GROUP);
    groupItem->setFirstColumnSpanned(true);
    groupItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    return groupItem;
}

QTreeWidgetItem *MountTreeWidget::newMountItem(const QString &name, const QString &host, const QString &mount, QTreeWidgetItem *groupItem)
{
    QTreeWidgetItem *mountItem = Q_NULLPTR;
    if (groupItem) mountItem = new QTreeWidgetItem(groupItem, QStringList() << name << host << mount, TREEWIDGETITEMTYPE_MOUNT);
    else mountItem = new QTreeWidgetItem(this, QStringList() << name << host << mount, TREEWIDGETITEMTYPE_MOUNT);
    mountItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    return mountItem;
}

QByteArray MountTreeWidget::getPassword(const QString &host)
{
    QString password;

    // open wallet
    if (!this->wallet) {
        QString foldername = "sshfsmount";
        this->wallet = KWallet::Wallet::openWallet(KWallet::Wallet::NetworkWallet(), this->winId());
        if (!this->wallet->hasFolder(foldername)) this->wallet->createFolder(foldername);
        this->wallet->setFolder(foldername);
    }

    // try to read password
    this->wallet->readPassword(host, password);

    // ask for new password
    if (password.length() == 0) {
        password = QInputDialog::getText(this, tr("Password Request"), tr("Enter password for") + " '" + host + "'", QLineEdit::Password);
        password = password.trimmed();
        this->wallet->writePassword(host, password);
    }

    return password.toUtf8();
}

void MountTreeWidget::resetPassword(const QString &host)
{
    // open wallet
    if (!this->wallet) {
        QString foldername = "sshfsmount";
        this->wallet = KWallet::Wallet::openWallet(KWallet::Wallet::NetworkWallet(), this->winId());
        if (!this->wallet->hasFolder(foldername)) this->wallet->createFolder(foldername);
        this->wallet->setFolder(foldername);
    }

    this->wallet->removeEntry(host);
}

void MountTreeWidget::slotAddNewGroup()
{
    this->newGroupItem("new group");
}

void MountTreeWidget::slotAddNewMount()
{
    QTreeWidgetItem *twi = this->currentItem();
    if (twi && twi->type() == TREEWIDGETITEMTYPE_GROUP) this->newMountItem("new mount", "user@host:/remote/path", "local/path", twi);
    else this->newMountItem("new mount", "user@host:/remote/path", "local/path");
}

void MountTreeWidget::slotDeleteItem()
{
    QTreeWidgetItem *twi = this->currentItem();
    if (twi) delete(twi);
}

void MountTreeWidget::slotMountItem()
{
    QTreeWidgetItem *twi = this->currentItem();
    if (twi && twi->type() != TREEWIDGETITEMTYPE_MOUNT) return;

    QString host = twi->text(1).trimmed();
    QString mount = twi->text(2).trimmed();

    QByteArray password = this->getPassword(host);

    QProcess sshfs;
    sshfs.start("sshfs", QStringList() << host << mount << "-o" << "password_stdin");
    if (!sshfs.waitForStarted()) return;
    sshfs.write(password + "\n");
    sshfs.waitForFinished();

    if (sshfs.exitCode() != 0) {
        this->resetPassword(host);
        QMessageBox msg(this);
        msg.setText(QString::fromUtf8(sshfs.readAllStandardError()));
        msg.exec();
    }
}

void MountTreeWidget::slotUnMountItem()
{
    QTreeWidgetItem *twi = this->currentItem();
    if (twi && twi->type() != TREEWIDGETITEMTYPE_MOUNT) return;

    QProcess sshfs;
    sshfs.start("fusermount", QStringList() << "-u" << twi->text(2));
    if (!sshfs.waitForStarted()) return;
    sshfs.waitForFinished();

    if (sshfs.exitCode() != 0) {
        QMessageBox msg(this);
        msg.setText(QString::fromUtf8(sshfs.readAllStandardError()));
        msg.exec();
    }
}
