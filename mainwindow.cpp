#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->currency_setter->addItems({"ololo", "ololo1"});

    connect(ui->convert_button, &QPushButton::released, this, &MainWindow::ConvertCurrency);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ConvertCurrency()
{
    double converted_currency;

    switch (ui->currency_setter->currentIndex())
    {
    case 0:
        ui->converted_value->setText("index 0");
        break;
    case 1:
        ui->converted_value->setText("index 1");
        break;
    default:
        break;
    }



}
