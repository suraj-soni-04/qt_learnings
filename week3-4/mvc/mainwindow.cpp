#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    listModel = new CustomListModel(this);
    tableModel = new CustomTableModel(this);

    ui->listView->setModel(listModel);
    ui->tableView->setModel(tableModel);

    // Adding initial data
    listModel->addItem("John Doe - Engineer");
    listModel->addItem("Jane Smith - Designer");
    listModel->addItem("Mike Johnson - Manager");

    tableModel->addItem({"John Doe", "30", "Engineer"});
    tableModel->addItem({"Jane Smith", "25", "Designer"});
    tableModel->addItem({"Mike Johnson", "45", "Manager"});

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    listModel->addItem("New Person - Occupation");
    tableModel->addItem({"New Person", "0", "Occupation"});
}
