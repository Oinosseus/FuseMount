#include "mountitem.h"

MountItem::MountItem(MountTreeWidget *parent, const QStringList &strings) : QTreeWidgetItem(parent, strings, MOUNTITEM_TYPE)
{
    this->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
}

MountItem::MountItem(MountItemGroup *parent, const QStringList &strings) : QTreeWidgetItem(parent, strings, MOUNTITEM_TYPE)
{
    this->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
}
