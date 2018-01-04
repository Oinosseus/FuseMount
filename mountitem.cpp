#include "mountitem.h"

MountItem::MountItem(MountTreeWidget *parent, const QStringList &strings) : QTreeWidgetItem(parent, strings, 1)
{
}

MountItem::MountItem(MountItemGroup *parent, const QStringList &strings) : QTreeWidgetItem(parent, strings, 1)
{

}
