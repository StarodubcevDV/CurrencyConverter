#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "currency_api_communication.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CurrencyApi *api_manager;

    void SetCurrencyList(QStringList currency_list);

private slots:
    void ConvertCurrency();
};
#endif // MAINWINDOW_H
