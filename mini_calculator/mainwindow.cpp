#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , leftOperand(0.0)
    , rightOperand(0.0)
    , waitingForOperand(true)
{
    ui->setupUi(this);
    ui->displayLineEdit->setReadOnly(true);
    ui->historyLineEdit->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateHistory(QString value) {
    ui->historyLineEdit->setText(ui->historyLineEdit->text() + value);
}

void MainWindow::clearHistory() {
    ui->historyLineEdit->clear();
}

void MainWindow::on_pushButton_7_clicked() { ui->displayLineEdit->setText(ui->displayLineEdit->text() + "7"); updateHistory("7"); }
void MainWindow::on_pushButton_8_clicked() { ui->displayLineEdit->setText(ui->displayLineEdit->text() + "8"); updateHistory("8"); }
void MainWindow::on_pushButton_9_clicked() { ui->displayLineEdit->setText(ui->displayLineEdit->text() + "9"); updateHistory("9"); }
void MainWindow::on_pushButton_4_clicked() { ui->displayLineEdit->setText(ui->displayLineEdit->text() + "4"); updateHistory("4"); }
void MainWindow::on_pushButton_5_clicked() { ui->displayLineEdit->setText(ui->displayLineEdit->text() + "5"); updateHistory("5"); }
void MainWindow::on_pushButton_6_clicked() { ui->displayLineEdit->setText(ui->displayLineEdit->text() + "6"); updateHistory("6"); }
void MainWindow::on_pushButton_1_clicked() { ui->displayLineEdit->setText(ui->displayLineEdit->text() + "1"); updateHistory("1"); }
void MainWindow::on_pushButton_2_clicked() { ui->displayLineEdit->setText(ui->displayLineEdit->text() + "2"); updateHistory("2"); }
void MainWindow::on_pushButton_3_clicked() { ui->displayLineEdit->setText(ui->displayLineEdit->text() + "3"); updateHistory("3"); }
void MainWindow::on_pushButton_0_clicked() { ui->displayLineEdit->setText(ui->displayLineEdit->text() + "0"); updateHistory("0"); }

void MainWindow::on_pushButton_decimal_clicked()
{
    if (!ui->displayLineEdit->text().contains("."))
        ui->displayLineEdit->setText(ui->displayLineEdit->text() + ".");
    updateHistory(".");
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->displayLineEdit->clear();
    leftOperand = 0.0;
    rightOperand = 0.0;
    pendingOperator.clear();
    waitingForOperand = true;
    clearHistory();
}

void MainWindow::on_pushButton_equals_clicked()
{
    QString text = ui->displayLineEdit->text();
    rightOperand = text.toDouble();
    if (pendingOperator == "+") {
        leftOperand += rightOperand;
    } else if (pendingOperator == "-") {
        leftOperand -= rightOperand;
    } else if (pendingOperator == "*") {
        leftOperand *= rightOperand;
    } else if (pendingOperator == "/") {
        if (rightOperand == 0.0) {
            ui->displayLineEdit->setText("Error");
            clearHistory();
            return;
        } else {
            leftOperand /= rightOperand;
        }
    } else if (pendingOperator == "%") {
        leftOperand = std::fmod(leftOperand, rightOperand);
    }
    ui->displayLineEdit->setText(QString::number(leftOperand));
    updateHistory(" = " + QString::number(leftOperand) + "\n");
    waitingForOperand = true;
}

void MainWindow::on_pushButton_division_clicked()
{
    if (!pendingOperator.isEmpty() && !waitingForOperand) {
        on_pushButton_equals_clicked();
    }
    pendingOperator = "/";
    leftOperand = ui->displayLineEdit->text().toDouble();
    ui->displayLineEdit->clear();
    updateHistory(" / ");
    waitingForOperand = false;
}

void MainWindow::on_pushButton_multiply_clicked()
{
    if (!pendingOperator.isEmpty() && !waitingForOperand) {
        on_pushButton_equals_clicked();
    }
    pendingOperator = "*";
    leftOperand = ui->displayLineEdit->text().toDouble();
    ui->displayLineEdit->clear();
    updateHistory(" * ");
    waitingForOperand = false;
}

void MainWindow::on_pushButton_subtract_clicked()
{
    if (!pendingOperator.isEmpty() && !waitingForOperand) {
        on_pushButton_equals_clicked();
    }
    pendingOperator = "-";
    leftOperand = ui->displayLineEdit->text().toDouble();
    ui->displayLineEdit->clear();
    updateHistory(" - ");
    waitingForOperand = false;
}

void MainWindow::on_pushButton_addition_clicked()
{
    if (!pendingOperator.isEmpty() && !waitingForOperand) {
        on_pushButton_equals_clicked();
    }
    pendingOperator = "+";
    leftOperand = ui->displayLineEdit->text().toDouble();
    ui->displayLineEdit->clear();
    updateHistory(" + ");
    waitingForOperand = false;
}

void MainWindow::on_pushButton_reciprocal_clicked()
{
    double value = ui->displayLineEdit->text().toDouble();
    value = 1.0 / value;
    ui->displayLineEdit->setText(QString::number(value));
    updateHistory("1/(" + QString::number(value) + ") = " + QString::number(value) + "\n");
}

void MainWindow::on_pushButton_percentage_clicked()
{
    if (!pendingOperator.isEmpty() && !waitingForOperand) {
        on_pushButton_equals_clicked();
    }
    pendingOperator = "%";
    leftOperand = ui->displayLineEdit->text().toDouble();
    ui->displayLineEdit->clear();
    updateHistory(" % ");
    waitingForOperand = false;
}


void MainWindow::on_pushButton_open_bracket_clicked()
{
    ui->displayLineEdit->setText(ui->displayLineEdit->text() + "(");
    updateHistory("(");
}


void MainWindow::on_pushButton_closed_bracket_clicked()
{
    ui->displayLineEdit->setText(ui->displayLineEdit->text() + ")");
    updateHistory(")");
}


void MainWindow::on_pushButton_squareroot_clicked()
{
    double value = ui->displayLineEdit->text().toDouble();
    value = std::sqrt(value);
    ui->displayLineEdit->setText(QString::number(value));
    updateHistory("√(" + QString::number(value) + ") = " + QString::number(value) + "\n");
}

