#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::changeMoney(int diff)
{
    money += diff;
    if(money < 0){
        QMessageBox msgBox;
        msgBox.warning(nullptr, "WARNING", "not enough minerals\nshow me the money");
        money -= diff;
    }

    if (money >= 200){
        ui->pbCola->setEnabled(true);
        ui->pbTea->setEnabled(true);
        ui->pbCoffee->setEnabled(true);
    } else if(money >= 150){
        ui->pbCola->setEnabled(false);
        ui->pbTea->setEnabled(true);
        ui->pbCoffee->setEnabled(true);
    } else if(money >= 100){
        ui->pbCola->setEnabled(false);
        ui->pbTea->setEnabled(false);
        ui->pbCoffee->setEnabled(true);
    } else{
        ui->pbCola->setEnabled(false);
        ui->pbTea->setEnabled(false);
        ui->pbCoffee->setEnabled(false);
    }
    ui->lcdNumber->display(money);
}

void Widget::on_pb10_clicked()
{
    changeMoney(10);
}

void Widget::on_pb50_clicked()
{
    changeMoney(50);
}

void Widget::on_pb100_clicked()
{
    changeMoney(100);
}

void Widget::on_pb500_clicked()
{
    changeMoney(5000000);
}

void Widget::on_pbCoffee_clicked()
{
    changeMoney(-100);
}

void Widget::on_pbTea_clicked()
{
    changeMoney(-150);
}

void Widget::on_pbCola_clicked()
{
    changeMoney(-200);
}

void Widget::on_pbReset_clicked()
{
    ui->lcdNumber->display(0);
    ui->pbCoffee->setEnabled(false);
    ui->pbTea->setEnabled(false);
    ui->pbCola->setEnabled(false);
    int r10 = 0;int r50 = 0;int r100 = 0;int r500 = 0;
    r500 = money / 500;
    if(r500) money = money % 500;
    r100 = money / 100;
    if(r100) money = money % 100;
    r50 = money / 50;
    if(r50) money = money % 50;
    r10 = money / 10;

    char str[1024] = "return\n\n";
    int len = 7;

    if(r500) len += sprintf(str + len, "500 : %d\n", r500);
    if(r100) len += sprintf(str + len, "100 : %d\n", r100);
    if(r50) len += sprintf(str + len, "50  : %d\n", r50);
    if(r10) sprintf(str + len, "10  : %d\n", r10);
    if(!r500&&!r100&&!r50&&!r10) strcat(str, "anything\n");

    QMessageBox msgBox;
    msgBox.information(nullptr, "Changes", str);
    money = 0;
}
