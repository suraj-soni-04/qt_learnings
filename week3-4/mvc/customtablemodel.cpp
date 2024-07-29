#include "customtablemodel.h"

CustomTableModel::CustomTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    m_headers << "Name" << "Age" << "Occupation";
}

int CustomTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}

int CustomTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_headers.count();
}

QVariant CustomTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_data.count() || index.column() >= m_headers.count() || role != Qt::DisplayRole) {
        return QVariant();
    }

    return m_data.at(index.row()).at(index.column());
}

QVariant CustomTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        return m_headers.at(section);
    } else {
        return QString::number(section + 1);
    }
}

void CustomTableModel::addItem(const QStringList &item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data.append(item);
    endInsertRows();
}
