#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;

private slots:
    void NumPressed();
    void MathButtonPressed();
    void EqualButton();
    void ChangeNumberSign();
    void on_Dot_released();
    void on_Percent_released();
    void on_Square_released();
    void on_Clear_released();
    void on_Back_released();
    void on_Cube_released();
    void on_Fraction_released();
    void on_Hexadecimal_released();
    void on_Binary_released();
};
#endif // CALCULATOR_H
