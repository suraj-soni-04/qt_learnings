#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    listModel = new CustomListModel(this);
    tableModel = new CustomTableModel(this);

    // ui->listView->setModel(listModel);
    // ui->tableView->setModel(tableModel);

    listProxyModel = new QSortFilterProxyModel(this);
    listProxyModel->setSourceModel(listModel);
    listProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    tableProxyModel = new QSortFilterProxyModel(this);
    tableProxyModel->setSourceModel(tableModel);
    tableProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    ui->listView->setModel(listProxyModel);
    ui->tableView->setModel(tableProxyModel);

    // Adding initial data
    listModel->addItem("John Doe - Engineer");
    listModel->addItem("Jane Smith - Designer");
    listModel->addItem("Mike Johnson - Manager");

    tableModel->addItem({"John Doe", "30", "Engineer"});
    tableModel->addItem({"Jane Smith", "25", "Designer"});
    tableModel->addItem({"Mike Johnson", "45", "Manager"});

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    connect(ui->filterLineEdit, &QLineEdit::textChanged, this, &MainWindow::on_filterLineEdit_textChanged);
    connect(ui->sortNameButton, &QPushButton::clicked, this, &MainWindow::on_sortNameButton_clicked);
    connect(ui->sortAgeButton, &QPushButton::clicked, this, &MainWindow::on_sortAgeButton_clicked);
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

void MainWindow::on_filterLineEdit_textChanged(const QString &text)
{
    listProxyModel->setFilterWildcard(text);
    tableProxyModel->setFilterWildcard(text);
}

void MainWindow::on_sortNameButton_clicked()
{
    tableProxyModel->sort(0, Qt::AscendingOrder); // Sort by first column (Name)
}

void MainWindow::on_sortAgeButton_clicked()
{
    tableProxyModel->sort(1, Qt::AscendingOrder); // Sort by second column (Age)
}

