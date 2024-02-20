
#include "currency_api_communication.h"
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>

CurrencyApi::CurrencyApi() : QObject()
{
    currency_api_manager = new QNetworkAccessManager();

    connect(currency_api_manager, &QNetworkAccessManager::finished, this, &CurrencyApi::CurrencyApi_ProcessCurrencyListReply);
}

CurrencyApi::~CurrencyApi()
{
    currency_api_manager->deleteLater();
    this->deleteLater();
}

void CurrencyApi::CurrencyApi_GetCurrencyList()
{
    currency_api_request.setUrl(QUrl("https://api.currencyapi.com/v3/currencies"));

    currency_api_request.setRawHeader("apikey", qgetenv("API_TOKEN"));

    currency_api_reply = currency_api_manager->get(currency_api_request);
}

void CurrencyApi::CurrencyApi_ProcessCurrencyListReply(QNetworkReply * reply)
{
    QStringList temp_currency_array;

    if (reply->error())
    {
        raise(reply->error());
    }

    QJsonParseError json_error;
    QJsonDocument reply_json = QJsonDocument::fromJson(reply->readAll(), &json_error);
    if (json_error.error != QJsonParseError::NoError)
    {
        raise(json_error.error);
    }

    QJsonObject root_object = reply_json.object();
    QJsonObject data_object = root_object["data"].toObject();

    for (int i = 0; i < data_object.count(); i++)
    {
        temp_currency_array << QString(data_object.keys()[i]);
    }

    emit CurrencyApi_CurrencyListReplyFinished(temp_currency_array);
}
