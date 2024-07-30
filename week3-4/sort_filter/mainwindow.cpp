#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new QStandardItemModel(this))
    , filteredModel(new QStandardItemModel(this))
    , proxyModel(new QSortFilterProxyModel(this))
{
    ui->setupUi(this);
    ui->tableView->setModel(proxyModel);
    proxyModel->setSourceModel(model);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    connect(ui->add_push_button, &QPushButton::clicked, this, &MainWindow::on_add_push_button_clicked);
    connect(ui->search_line_edit, &QLineEdit::textChanged, this, &MainWindow::on_search_line_edit_textChanged);
    ui->tableView->setSortingEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_push_button_clicked()
{
    ui->search_line_edit->clear();
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open CSV"), "", tr("CSV Files (*.csv);;All Files (*)"));
    if (!fileName.isEmpty())
    {
        loadCSV(fileName);
        ui->file_name_label->setText(QFileInfo(fileName).fileName());
    }
}

void MainWindow::loadCSV(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return;

    QTextStream stream(&file);
    QStringList headers = stream.readLine().split(',');
    //qDebug()<<"Headers : "<<"("<<headers<<")";

    model->clear();
    model->setHorizontalHeaderLabels(headers);

    while (!stream.atEnd())
    {
        QList<QStandardItem *> items;
        foreach (const QString &text, stream.readLine().split(','))
        {
            items.append(new QStandardItem(text));
        }
        model->appendRow(items);
    }

    file.close();
}

void MainWindow::on_search_line_edit_textChanged(const QString &text)
{
    filterTable(text);
}

void MainWindow::filterTable(const QString &text)
{
    filteredModel->clear();
    for (int col = 0; col < model->columnCount(); ++col)
    {
        filteredModel->setHorizontalHeaderItem(col, model->horizontalHeaderItem(col)->clone());
    }

    for (int row = 0; row < model->rowCount(); ++row)
    {
        bool match = false;
        for (int col = 0; col < model->columnCount(); ++col)
        {
            if (model->item(row, col)->text().contains(text, Qt::CaseInsensitive))
            {
                match = true;
                break;
            }
        }
        if (match)
        {
            QList<QStandardItem *> items;
            for (int col = 0; col < model->columnCount(); ++col)
            {
                items.append(new QStandardItem(model->item(row, col)->text()));
            }
            filteredModel->appendRow(items);
        }
    }

    ui->tableView->setModel(filteredModel);
}


