#include "calculator.h"
#include "ui_calculator.h"
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

void Calculator::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    if(!displayVal.contains('.') && (displayVal.toDouble() == 0)){
        ui->Display->setText(butVal);
    }
    else if(displayVal.contains('.') && butVal == "0"){
        QString newVal = displayVal + butVal;
        ui->Display->setText(newVal);
    }
    else{
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
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


void Calculator::on_Clear_released(){
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;

    ui->Display->setText(QString::number(0.0));
}

