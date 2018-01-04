#ifndef MOUNTTREEWIDGET_H
#define MOUNTTREEWIDGET_H

#include <QTreeWidget>
#include <QContextMenuEvent>
#include <QAction>
#include <KWallet>

class MountTreeWidget : public QTreeWidget
{
    Q_OBJECT

public:
    MountTreeWidget(QWidget *parent = 0);
    ~MountTreeWidget();

public slots:
    void slotAddNewGroup();
    void slotAddNewMount();
    void slotDeleteItem();
    void slotMountItem();
    void slotUnMountItem();

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    KWallet::Wallet *wallet;
    QTreeWidgetItem *newGroupItem(const QString &name);
    QTreeWidgetItem *newMountItem(const QString &name, const QString &host, const QString &mount, QTreeWidgetItem *groupItem = Q_NULLPTR);
    void mount(const QString &host, const QString &mount);
    void unmount(const QString &mount);
    QByteArray getPassword(const QString &host);
    void resetPassword(const QString &host);

};

#endif // MOUNTTREEWIDGET_H
