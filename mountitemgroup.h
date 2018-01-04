#ifndef MOUNTITEMGROUP_H
#define MOUNTITEMGROUP_H

#include <QTreeWidgetItem>
#include <QStringList>

#include <mounttreewidget.h>

#define MOUNTITEMGROUP_TYPE 2

class MountItemGroup : public QTreeWidgetItem
{
public:
    MountItemGroup(MountTreeWidget *parent, const QString &name);
};

#endif // MOUNTITEMGROUP_H
