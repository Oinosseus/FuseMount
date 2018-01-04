#include "mountitemgroup.h"

MountItemGroup::MountItemGroup(MountTreeWidget *parent, const QString &name) : QTreeWidgetItem(parent, QStringList(name), MOUNTITEMGROUP_TYPE)
{
    this->setFirstColumnSpanned(true);
    this->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
}
