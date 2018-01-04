#ifndef MOUNTTREEWIDGET_H
#define MOUNTTREEWIDGET_H

#include <QTreeWidget>
#include <QContextMenuEvent>

class MountTreeWidget : public QTreeWidget
{
public:
    MountTreeWidget(QWidget *parent = 0);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
};

#endif // MOUNTTREEWIDGET_H
