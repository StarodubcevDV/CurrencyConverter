#ifndef CURRENCY_API_COMMUNICATION_H
#define CURRENCY_API_COMMUNICATION_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QStringList>


class CurrencyApi : public QObject
{
    Q_OBJECT

public:
    CurrencyApi();
    ~CurrencyApi();

    void CurrencyApi_GetCurrencyList();
    void CurrencyApi_GetCurrencyValue(QByteArray base_currency, QByteArray result_currency);

    void CurrencyApi_ProcessCurrencyListReply(QNetworkReply * reply);
    void CurrencyApi_ProcessCurrencyValueReply(QNetworkReply * reply);

public slots:
    void CurrencyApi_ProcessReply(QNetworkReply * reply);

signals:
    void CurrencyApi_CurrencyListReplyFinished(QStringList currency_list);
    void CurrencyApi_CurrencyValueReplyFinished(double currency_value);

private:
    QNetworkAccessManager *currency_api_manager;
    QNetworkRequest currency_api_request;
    QNetworkReply *currency_api_reply;
};

#endif // CURRENCY_API_COMMUNICATION_H
