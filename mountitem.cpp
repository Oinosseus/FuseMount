#include "mountitem.h"

MountItem::MountItem(MountTreeWidget *parent, const QStringList &strings) : QTreeWidgetItem(parent, strings, MOUNTITEM_TYPE)
{
    this->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
}

MountItem::MountItem(MountItemGroup *parent, const QStringList &strings) : QTreeWidgetItem(parent, strings, MOUNTITEM_TYPE)
{
    this->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
}

void MountItem::save2File(QFile &file)
{
    QString line;

    // get group
    MountItemGroup *mig = dynamic_cast<MountItemGroup *>(this->parent());
    if (mig && mig->type() == MOUNTITEMGROUP_TYPE) {
        line += mig->text(0);
    }

    line += ", " + this->text(0);
    line += ", " + this->text(1);
    line += ", " + this->text(2);
    line += "\n";
    file.write(line.toUtf8());
}
