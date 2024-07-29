#pragma once
#include <QAbstractListModel>
#include <QStringList>

class CustomListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    CustomListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void addItem(const QString &item);

private:
    QStringList m_data;
};

