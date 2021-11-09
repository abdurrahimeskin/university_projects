#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonUSD_clicked();

    void on_pushButtonEUR_clicked();

    void on_pushButtonGBP_clicked();

    void on_pushButtonCNY_clicked();

    void replyFunc(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager ;

};

#endif // MAINWINDOW_H
