#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    api_manager = new CurrencyApi();
    api_manager->CurrencyApi_GetCurrencyList();

    connect(ui->convert_button, &QPushButton::released, this, &MainWindow::ConvertCurrency);
    connect(api_manager, &CurrencyApi::CurrencyApi_CurrencyListReplyFinished, this, &MainWindow::SetCurrencyList);
    connect(api_manager, &CurrencyApi::CurrencyApi_CurrencyValueReplyFinished, this, &MainWindow::SetCurrencyConvertedValue);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ConvertCurrency()
{
    api_manager->CurrencyApi_GetCurrencyValue(ui->currency_setter->currentText().toUtf8(),
                                              ui->result_currency->currentText().toUtf8());
}

void MainWindow::SetCurrencyList(QStringList currency_list)
{
    ui->currency_setter->addItems(currency_list);
    ui->result_currency->addItems(currency_list);
}

void MainWindow::SetCurrencyConvertedValue(double currency_value)
{
    double calc_value = ui->value_input->text().toDouble() * currency_value;
    ui->converted_value->setText(QString::number(calc_value));
}
