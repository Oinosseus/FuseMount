#ifndef MOUNTTREEWIDGET_H
#define MOUNTTREEWIDGET_H

#include <QTreeWidget>
#include <QContextMenuEvent>
#include <QAction>

class MountTreeWidget : public QTreeWidget
{
    Q_OBJECT

public:
    MountTreeWidget(QWidget *parent = 0);

public slots:
    void slotAddNewGroup();
    void slotDeleteGroup();
    void slotAddNewMount();
    void slotDeleteMount();

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

};

#endif // MOUNTTREEWIDGET_H
