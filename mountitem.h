#ifndef MOUNTITEM_H
#define MOUNTITEM_H

#include <QTreeWidgetItem>
#include <QStringList>

#include <mounttreewidget.h>
#include <mountitemgroup.h>

#define MOUNTITEM_TYPE 1

class MountItem : public QTreeWidgetItem
{
public:
    MountItem(MountTreeWidget *parent, const QStringList &strings);
    MountItem(MountItemGroup *parent, const QStringList &strings);
};

#endif // MOUNTITEM_H
