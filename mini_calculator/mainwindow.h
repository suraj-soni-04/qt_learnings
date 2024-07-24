#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_0_clicked();

    void on_pushButton_decimal_clicked();
    void on_pushButton_clear_clicked();
    void on_pushButton_equals_clicked();
    void on_pushButton_division_clicked();
    void on_pushButton_multiply_clicked();
    void on_pushButton_subtract_clicked();
    void on_pushButton_addition_clicked();
    void on_pushButton_percent_clicked();

    void on_pushButton_reciprocal_clicked();
    void on_pushButton_percentage_clicked();
    void on_pushButton_open_bracket_clicked();
    void on_pushButton_closed_bracket_clicked();
    void on_pushButton_squareroot_clicked();

private:
    Ui::MainWindow *ui;
    double leftOperand;
    double rightOperand;
    QString pendingOperator;
    bool waitingForOperand;
    QString history;
    void updateHistory(QString value);
    void clearHistory();
};

#endif // MAINWINDOW_H
