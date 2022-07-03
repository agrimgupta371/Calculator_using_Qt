#include "calculator.h"
#include "ui_calculator.h"
#include <cmath>
#include <string>
#include <bits/stdc++.h>
using namespace std;
//#include <QRegExp>

double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

Calculator::Calculator(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i=0; i<10; ++i){
        QString butName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));

    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButton()));
    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));
}

Calculator::~Calculator()
{
    delete ui;
}
/*
void decimal_to_binary(int n){
    QString bin = "";
    if(n == 0){
        bin + "0";
        //printf("0");
        return;
    }
    else if(n == 1){
        bin + "1";
        //printf("1");
        return;
    }
    else{
        decimal_to_binary(n/2);
        printf("%d", n%2);
    }
}*/

void Calculator::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    QString display2Val = ui->Display2->text();
    if(!displayVal.contains('.') && (displayVal.toDouble() == 0)){
        ui->Display->setText(butVal);
        ui->Display2->setText(display2Val + butVal);
    }
    else if(displayVal.contains('.') && butVal == "0"){
        QString newVal = displayVal + butVal;
        ui->Display->setText(newVal);
        ui->Display2->setText(display2Val + butVal);
    }
    else{
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
        ui->Display2->setText(display2Val + butVal);
    }
}

void Calculator::MathButtonPressed(){
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;

    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    ui->Display2->setText(displayVal + butVal);
    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0){
        divTrigger = true;
    }
    else if(QString::compare(butVal, "*", Qt::CaseInsensitive) == 0){
        multTrigger = true;
    }
    else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){
        addTrigger = true;
    }
    else {
        subTrigger = true;
    }
    ui->Display->setText("");
}

void Calculator::EqualButton(){
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if(addTrigger || subTrigger || multTrigger || divTrigger){
        if(addTrigger){
            solution = calcVal + dblDisplayVal;
        }
        else if(subTrigger){
            solution = calcVal - dblDisplayVal;
        }
        else if(multTrigger){
            solution = calcVal * dblDisplayVal;
        }
        else{
            solution = calcVal / dblDisplayVal;
        }
    }
    ui->Display->setText(QString::number(solution));
}

void Calculator::ChangeNumberSign(){
    QString displayVal = ui->Display->text();

    double dblDisplayVal = displayVal.toDouble();
    double dblDisplayValSign = -1 * dblDisplayVal;
    ui->Display->setText(QString::number(dblDisplayValSign, 'g', 16));

}

void Calculator::on_Dot_released(){
    if(!ui->Display->text().contains('.')){
        ui->Display->setText(ui->Display->text() + ".");
        ui->Display2->setText(ui->Display2->text() + ".");
    }
}

void Calculator::on_Percent_released(){
    QString displayVal = ui->Display->text();

    double dblDisplayVal = displayVal.toDouble();
    double dblDisplayValSign = 0.01 * dblDisplayVal;
    ui->Display->setText(QString::number(dblDisplayValSign, 'g', 16));
}


void Calculator::on_Square_released(){
    QString displayVal = ui->Display->text();

    double dblDisplayVal = displayVal.toDouble();
    double dblDisplayValSign = dblDisplayVal * dblDisplayVal;
    ui->Display->setText(QString::number(dblDisplayValSign, 'g', 16));
}

void Calculator::on_Cube_released(){
    QString displayVal = ui->Display->text();

    double dblDisplayVal = displayVal.toDouble();
    double dblDisplayValSign = dblDisplayVal * dblDisplayVal*dblDisplayVal;
    ui->Display->setText(QString::number(dblDisplayValSign, 'g', 16));
}

void Calculator::on_Fraction_released(){
    QString displayVal = ui->Display->text();

    double dblDisplayVal = displayVal.toDouble();
    double dblDisplayValSign = 1/dblDisplayVal;
    ui->Display->setText(QString::number(dblDisplayValSign, 'g', 16));
}

void Calculator::on_Clear_released(){
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;

    ui->Display->setText(QString::number(0.0));
    ui->Display2->setText("");
}


void Calculator::on_Back_released()
{
    QString displayVal = ui->Display->text();
    QString display2Val = ui->Display2->text();
    displayVal.chop(1);
    display2Val.chop(1);
    ui->Display->setText(displayVal);
    ui->Display2->setText(display2Val);
}


void Calculator::on_Hexadecimal_released(){
    QString displayVal = ui->Display->text();
    double n = displayVal.toDouble();
    int sign = 1;
    string s;
    if(n<0){
        sign = -1;
        n = n*sign;
    }
    double t = n - (int)n;
    int x = (int)n;
    while(x!=0){
        int temp = x % 16;
        if(temp<10){
            s.push_back(temp + 48);
        }
        else{
            s.push_back(temp + 55);
        }
        x = x/16;
    }
    if(sign == -1) s.push_back('-');
    reverse(s.begin(), s.end());
    if(t!=0) s.push_back('.');

    while(t!=0){
        double temp = t * 16;
        int temp1 = (int)temp;
        if(temp1<10){
            s.push_back(temp1 + 48);
        }
        else{
            s.push_back(temp1 + 55);
        }
        t = temp - temp1;
    }
    //return s;
    QString s1 = QString::fromStdString(s);
    ui->Display2->setText(s1);

}


void Calculator::on_Binary_released(){
    QString displayVal = ui->Display->text();
    double n = displayVal.toDouble();
    int sign = 1;
    string s;
    if(n<0){
        sign = -1;
        n = n*sign;
    }
    double t = n - (int)n;
    int x = (int)n;
    while(x!=0){
        int temp = x % 2;
        s.push_back(temp + 48);
        x = x/2;
    }
    if(sign == -1) s.push_back('-');
    reverse(s.begin(), s.end());
    if(t!=0) s.push_back('.');

    while(t!=0){
        double temp = t * 2;
        int temp1 = (int)temp;
        s.push_back(temp1 + 48);
        t = temp - temp1;
    }
    //return s;
    QString s1 = QString::fromStdString(s);
    ui->Display2->setText(s1);

}

