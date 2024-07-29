#pragma once
#include <QAbstractTableModel>
#include <QVector>
#include <QStringList>

class CustomTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    CustomTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    void addItem(const QStringList &item);

private:
    QVector<QStringList> m_data;
    QStringList m_headers;
};
