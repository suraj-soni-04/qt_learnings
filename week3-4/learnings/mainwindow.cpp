#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize the table model and set headers
    tableModel = new QStandardItemModel(this);
    tableModel->setHorizontalHeaderLabels({"Name", "Age", "Occupation"});

    // Set the model to the table view
    ui->tableView->setModel(tableModel);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    // Initialize the list model
    listModel = new QStringListModel(this);

    // Set the model to the list view
    ui->listView->setModel(listModel);

    // Add initial data to the models
    addInitialData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addInitialData()
{
    // Data for the table
    QList<QList<QString>> tableData = {
        {"John Doe", "30", "Engineer"},
        {"Jane Smith", "25", "Designer"},
        {"Mike Johnson", "45", "Manager"}
    };

    // Add data to the table model
    for (const auto &row : tableData) {
        QList<QStandardItem *> items;
        for (const auto &field : row) {
            items.append(new QStandardItem(field));
        }
        tableModel->appendRow(items);
    }

    // Data for the list
    QStringList listData = {"John Doe - 30 - Engineer", "Jane Smith - 25 - Designer", "Mike Johnson - 45 - Manager"};

    // Add data to the list model
    listModel->setStringList(listData);
}

void MainWindow::on_pushButton_clicked()
{
    // Add new data to the table model
    QList<QStandardItem *> tableItems;
    tableItems.append(new QStandardItem("New Person"));
    tableItems.append(new QStandardItem("0"));
    tableItems.append(new QStandardItem("Occupation"));
    tableModel->appendRow(tableItems);

    // Add new data to the list model
    QStringList listData = listModel->stringList();
    listData.append("New Person - 0 - Occupation");
    listModel->setStringList(listData);
}
