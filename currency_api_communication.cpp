
#include "currency_api_communication.h"
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>


CurrencyApi::CurrencyApi() : QObject()
{
    currency_api_manager = new QNetworkAccessManager();

    connect(currency_api_manager, &QNetworkAccessManager::finished, this, &CurrencyApi::CurrencyApi_ProcessReply);
}

CurrencyApi::~CurrencyApi()
{
    currency_api_manager->deleteLater();
    this->deleteLater();
}

void CurrencyApi::CurrencyApi_GetCurrencyList()
{
    QUrl url("https://api.currencyapi.com/v3/currencies");

    QUrlQuery query;
    query.addQueryItem("apikey", qgetenv("API_TOKEN"));

    url.setQuery(query);
    currency_api_request.setUrl(url);

    currency_api_reply = currency_api_manager->get(currency_api_request);
    currency_api_reply->setProperty("currency_list", true);
}

void CurrencyApi::CurrencyApi_GetCurrencyValue(QByteArray base_currency, QByteArray result_currency)
{
    QUrl url("https://api.currencyapi.com/v3/latest");

    QUrlQuery query;
    query.addQueryItem("apikey", qgetenv("API_TOKEN"));
    query.addQueryItem("base_currency", base_currency);
    query.addQueryItem("currencies", result_currency);

    url.setQuery(query);

    currency_api_request.setUrl(url);

    currency_api_reply = currency_api_manager->get(currency_api_request);
    currency_api_reply->setProperty("get_value", true);
}

void CurrencyApi::CurrencyApi_ProcessReply(QNetworkReply * reply)
{
    if (reply->error())
    {
        raise(reply->error());
    }

    if (!reply->property("currency_list").isNull())
    {
        CurrencyApi_ProcessCurrencyListReply(reply);
    }
    else if (!reply->property("get_value").isNull())
    {
        CurrencyApi_ProcessCurrencyValueReply(reply);
    }
}

void CurrencyApi::CurrencyApi_ProcessCurrencyListReply(QNetworkReply * reply)
{
    QStringList temp_currency_array;

    QJsonParseError json_error;
    QJsonDocument reply_json = QJsonDocument::fromJson(reply->readAll(), &json_error);
    if (json_error.error != QJsonParseError::NoError)
    {
        raise(json_error.error);
    }
    reply->deleteLater();

    QJsonObject root_object = reply_json.object();
    QJsonObject data_object = root_object["data"].toObject();

    for (int i = 0; i < data_object.count(); i++)
    {
        temp_currency_array << QString(data_object.keys()[i]);
    }

    emit CurrencyApi_CurrencyListReplyFinished(temp_currency_array);
}

void CurrencyApi::CurrencyApi_ProcessCurrencyValueReply(QNetworkReply * reply)
{
    QJsonParseError json_error;
    QJsonDocument reply_json = QJsonDocument::fromJson(reply->readAll(), &json_error);
    if (json_error.error != QJsonParseError::NoError)
    {
        raise(json_error.error);
    }
    reply->deleteLater();

    QJsonObject root_object = reply_json.object();
    QJsonObject data_object = root_object["data"].toObject();
    QJsonObject currency_object = data_object[data_object.keys()[0]].toObject();

    emit CurrencyApi_CurrencyValueReplyFinished(currency_object["value"].toDouble());
}
