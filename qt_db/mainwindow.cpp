#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect to MySQL database
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("hr");
    db.setUserName("root");
    db.setPassword("1234");

    if (!db.open()) {
        QMessageBox::critical(this, "Database Connection Error", db.lastError().text());
    } else {
        qDebug() << "Database connected successfully!";
    }

    connect(ui->add_push_button, &QPushButton::clicked, this, &MainWindow::on_add_push_button_clicked);
    connect(ui->update_push_button, &QPushButton::clicked, this, &MainWindow::on_update_push_button_clicked);
    connect(ui->delete_push_button, &QPushButton::clicked, this, &MainWindow::on_delete_push_button_clicked);
    connect(ui->load_push_button, &QPushButton::clicked, this, &MainWindow::on_load_push_button_clicked);

}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_add_push_button_clicked()
{
    QString name = ui->name_line_edit->text();
    QString email = ui->email_line_edit->text();
    QString contact = ui->contact_line_edit->text();

    QSqlQuery query;
    query.prepare("INSERT INTO contacts (name, email, phone) VALUES (:name, :email, :phone)");
    query.bindValue(":name", name);
    query.bindValue(":email", email);
    query.bindValue(":phone", contact);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", query.lastError().text());
    } else {
        QMessageBox::information(this, "Success", "Contact added successfully!");
        on_load_push_button_clicked();
    }
}



void MainWindow::on_update_push_button_clicked()
{
    int row = ui->display_table_widget->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Selection Error", "Please select a contact to update.");
        return;
    }

    QString id = ui->display_table_widget->item(row, 0)->text();
    QString name = ui->name_line_edit->text();
    QString email = ui->email_line_edit->text();
    QString contact = ui->contact_line_edit->text();

    QSqlQuery query;
    query.prepare("UPDATE contacts SET name = :name, email = :email, phone = :phone WHERE id = :id");
    query.bindValue(":name", name);
    query.bindValue(":email", email);
    query.bindValue(":phone", contact);
    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", query.lastError().text());
    } else {
        QMessageBox::information(this, "Success", "Contact updated successfully!");
        on_load_push_button_clicked();
    }
}



void MainWindow::on_delete_push_button_clicked()
{
    int row = ui->display_table_widget->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Selection Error", "Please select a contact to delete.");
        return;
    }

    QString id = ui->display_table_widget->item(row, 0)->text();

    QSqlQuery query;
    query.prepare("DELETE FROM contacts WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", query.lastError().text());
    } else {
        QMessageBox::information(this, "Success", "Contact deleted successfully!");
        on_load_push_button_clicked();
    }
}



void MainWindow::on_load_push_button_clicked()
{
    QSqlQuery query("SELECT * FROM contacts");

    ui->display_table_widget->setRowCount(0);
    while (query.next()) {
        int rowCount = ui->display_table_widget->rowCount();
        ui->display_table_widget->insertRow(rowCount);

        ui->display_table_widget->setItem(rowCount, 0, new QTableWidgetItem(query.value("id").toString()));
        ui->display_table_widget->setItem(rowCount, 1, new QTableWidgetItem(query.value("name").toString()));
        ui->display_table_widget->setItem(rowCount, 2, new QTableWidgetItem(query.value("email").toString()));
        ui->display_table_widget->setItem(rowCount, 3, new QTableWidgetItem(query.value("phone").toString()));
    }
}


