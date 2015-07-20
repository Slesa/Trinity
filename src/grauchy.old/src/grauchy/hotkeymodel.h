#ifndef HOTKEYMODEL_H
#define HOTKEYMODEL_H

#include "data/hotkey.h"
#include <QList>
#include <QAbstractItemModel>

class HotkeyModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    HotkeyModel(QList<Hotkey> hotkeys);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex& index, int role) const Q_DECL_OVERRIDE;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;

private:
    QList<Hotkey> _hotkeys;
};

#endif // HOTKEYMODEL_H
