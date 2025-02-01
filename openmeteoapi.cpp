#include "openmeteoapi.h"
#include "customexception.h"

openMeteoAPI::openMeteoAPI(QObject *parent)
    : QObject{parent}
    , m_url("https://api.open-meteo.com/v1/"
            "forecast?latitude=48.112&longitude=-1.6743&current=temperature_2m&daily=weather_code&"
            "timezone=auto&forecast_days=3")
    , m_reply(nullptr)
    , m_bIsDataAvailable(false)
{
    m_networkManager = new QNetworkAccessManager(this);
    QObject::connect(m_networkManager,
                     &QNetworkAccessManager::finished,
                     this,
                     &openMeteoAPI::serviceRequestFinished);
}

void openMeteoAPI::serviceRequestFinished(QNetworkReply *networkReply)
{
    m_reply = networkReply;
    if (m_reply->error() != QNetworkReply::NoError) {
        THROW_CUSTOM_EXCEPTION(m_reply->errorString());
        return;
    }
    qDebug() << "Receive https reply";
    // Parse the JSON response
    QByteArray response = m_reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(response);
    m_jsonInfoWeather = doc.object();
    m_reply->deleteLater();
    m_bIsDataAvailable = true;
    emit requestFinished();
}

void openMeteoAPI::fetchWeather()
{
    m_bIsDataAvailable = false;
    clearJsonData();
    m_networkManager->get(QNetworkRequest(m_url));
}

void openMeteoAPI::clearJsonData()
{
    m_jsonInfoWeather = QJsonObject();
}

bool openMeteoAPI::getIsDataAvailable()
{
    return m_bIsDataAvailable;
}

QJsonArray openMeteoAPI::getListDaysWeatherCode()
{
    if (m_jsonInfoWeather.empty()) {
        THROW_CUSTOM_EXCEPTION("weather code not available");
        return QJsonArray();
    }
    return m_jsonInfoWeather["weather_code"].toArray();
}

double openMeteoAPI::getTemperature()
{
    if (m_jsonInfoWeather.empty()) {
        THROW_CUSTOM_EXCEPTION("weather temperature not available");
        return 0;
    }
    return m_jsonInfoWeather["current"].toObject()["temperature_2m"].toDouble();
}
