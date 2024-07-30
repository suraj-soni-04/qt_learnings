#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "customlistmodel.h"
#include "customtablemodel.h"
#include <QSortFilterProxyModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_sortNameButton_clicked();
    void on_sortAgeButton_clicked();
    void on_filterLineEdit_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    CustomListModel *listModel;
    CustomTableModel *tableModel;
    QSortFilterProxyModel *listProxyModel;
    QSortFilterProxyModel *tableProxyModel;
};

#endif // MAINWINDOW_H
