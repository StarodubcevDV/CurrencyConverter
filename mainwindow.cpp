#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    api_manager = new CurrencyApi();
    api_manager->CurrencyApi_GetCurrencyList();

    connect(ui->convert_button, &QPushButton::released, this, &MainWindow::ConvertCurrency);
    connect(api_manager, &CurrencyApi::CurrencyApi_CurrencyListReplyFinished, this, &MainWindow::SetCurrencyList);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ConvertCurrency()
{
    // double converted_currency;

    switch (0)
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

void MainWindow::SetCurrencyList(QStringList currency_list)
{
    ui->currency_setter->addItems(currency_list);
}
