#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
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
    void on_add_push_button_clicked();
    void on_search_line_edit_textChanged(const QString &text);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QStandardItemModel *filteredModel;
    QSortFilterProxyModel *proxyModel;
    QString currentFileName;
    void loadCSV(const QString &fileName);
    void filterTable(const QString &text);
};

#endif // MAINWINDOW_H
