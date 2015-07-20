#include "hotkeymodel.h"

HotkeyModel::HotkeyModel(QList<Hotkey> hotkeys)
    : _hotkeys(hotkeys)
{

}

int HotkeyModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _hotkeys.size();
}

int HotkeyModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}

QVariant HotkeyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( role!=Qt::DisplayRole) return QVariant();

    switch (section) {
    case 0:
        return tr("Key");
    case 1:
        return tr("Description");
    case 2:
        return tr("Tags");
    default:
        break;
    }
    return QVariant();
}

QVariant HotkeyModel::data(const QModelIndex& index, int role) const
{
    if(!index.isValid()) return QVariant();

    if(role!=Qt::DisplayRole) return QVariant();

    Hotkey hotkey = _hotkeys.at(index.row());
    switch(index.column()) {
    case 1:
        return hotkey.getDescription();
    }
}

QModelIndex HotkeyModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();

/*    TreeItem *parentItem = getItem(parent);

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else */
        return QModelIndex();
}

QModelIndex HotkeyModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

/*    TreeItem *childItem = getItem(index);
    TreeItem *parentItem = childItem->parent();

    if (parentItem == rootItem) */
        return QModelIndex();

//    return createIndex(parentItem->childNumber(), 0, parentItem);
}
