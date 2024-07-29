#include "customlistmodel.h"

CustomListModel::CustomListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int CustomListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}

QVariant CustomListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_data.count() || role != Qt::DisplayRole) {
        return QVariant();
    }

    return m_data.at(index.row());
}

void CustomListModel::addItem(const QString &item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data.append(item);
    endInsertRows();
}
