
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegExp>
#include <QtWidgets>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//I have created that to keep currency unit USD EUR etc
QString unitStr;


void MainWindow::replyFunc(QNetworkReply *reply)  {


    QString str ;
    int pos=0;
// It reads the all data fetched from the web site
    QString data = (QString) reply->readAll();

// use regex matching code to take the rate information
    QRegExp rx("(\\d+\\.\\d+)");


       if ( rx.indexIn(data, pos) != -1 ) {

      //getting from regex
       QString each=rx.cap(1);

      //converting the regex information to float
       float eachFloat=each.toFloat();
      //converting float value to calculate
       float tlF=ui->edittext->text().toFloat();

      float total=eachFloat*tlF;

       str.setNum(total);
       //assign that value to str
       str+=" "+unitStr;


}
       else {
           str = QString("Error") ;
       }
       // set the text of the amount and rate result
       ui->label_amount->setText(str);
       ui->label_rate->setText(rx.cap(1)+" TL/"+unitStr);

}
void MainWindow::on_pushButtonUSD_clicked()
{
     unitStr="USD";

     QUrl url="http://api.fixer.io/latest?base=TRY&symbols="+unitStr;
//controls line situation whether it is empty or not
     if(ui->edittext->text()==""){
        ui->label_error->setText("Please enter a number");
    }

    else
    {
//checking the line edit number is it number or not
        QRegExp re("\\d*");
        if (re.exactMatch(ui->edittext->text()))
        {

    manager = new QNetworkAccessManager(this) ;
    connect(manager, SIGNAL(finished(QNetworkReply *)),this, SLOT(replyFunc(QNetworkReply *)));
    manager->get(QNetworkRequest(url));

    ui->label_error->setText("");}
        else {
//if there is no number in line edit we warn that told enter a number again
            ui->label_error->setText("Please enter a number");

        }

}
}

//when we click the EUR button it finds the converting value of EUR currency by finding it from the site index
//Initially it controls whether it is empty or not
//After that take the value and convert TL values into EUR currency
//All other mothods work with same algorithm just in different currency names and they are working with same logic

void MainWindow::on_pushButtonEUR_clicked()
{
    unitStr="EUR";
    QUrl url="http://api.fixer.io/latest?base=TRY&symbols="+unitStr;
   if(ui->edittext->text()==""){
       ui->label_error->setText("Please enter a number");
   }

   else
   {
       QRegExp re("\\d*");
       if (re.exactMatch(ui->edittext->text()))
       {

   manager = new QNetworkAccessManager(this) ;
   connect(manager, SIGNAL(finished(QNetworkReply *)),this, SLOT(replyFunc(QNetworkReply *)));
   manager->get(QNetworkRequest(url));

   ui->label_error->setText("");}
       else {
           ui->label_error->setText("Please enter a number");

       }

}
}

void MainWindow::on_pushButtonGBP_clicked()
{
    unitStr="GBP";
    QUrl url="http://api.fixer.io/latest?base=TRY&symbols="+unitStr;
   if(ui->edittext->text()==""){
       ui->label_error->setText("Please enter a number");
   }

   else
   {
       QRegExp re("\\d*");
       if (re.exactMatch(ui->edittext->text()))
       {

   manager = new QNetworkAccessManager(this) ;
   connect(manager, SIGNAL(finished(QNetworkReply *)),this, SLOT(replyFunc(QNetworkReply *)));
   manager->get(QNetworkRequest(url));

   ui->label_error->setText("");}
       else {
           ui->label_error->setText("Please enter a number");

       }

}
}

void MainWindow::on_pushButtonCNY_clicked()
{
    unitStr="CNY";
    QUrl url="http://api.fixer.io/latest?base=TRY&symbols="+unitStr;
   if(ui->edittext->text()==""){
       ui->label_error->setText("Please enter a number");
   }

   else
   {
       QRegExp re("\\d*");
       if (re.exactMatch(ui->edittext->text()))
       {

   manager = new QNetworkAccessManager(this) ;
   connect(manager, SIGNAL(finished(QNetworkReply *)),this, SLOT(replyFunc(QNetworkReply *)));
   manager->get(QNetworkRequest(url));

   ui->label_error->setText("");}
       else {
           ui->label_error->setText("Please enter a number");

       }

}
}


