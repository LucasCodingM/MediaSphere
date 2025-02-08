#include "openmeteoapi.h"
#include "customexception.h"

openMeteoAPI::openMeteoAPI(QObject *parent)
    : QObject{parent}
    , m_url("https://api.open-meteo.com/v1/"
            "forecast?latitude=48.112&longitude=-1.6743&current=temperature_2m,weather_code&daily="
            "weather_code,temperature_2m_max,temperature_2m_min&timezone=auto&forecast_days=3")
    , m_reply(nullptr)
    , m_bIsDataAvailable(false)
{
    m_networkManager = new QNetworkAccessManager(this);
    QObject::connect(m_networkManager,
                     &QNetworkAccessManager::finished,
                     this,
                     &openMeteoAPI::serviceRequestFinished);
    QTimer *timer = new QTimer(this); // `this` sets openMeteoAPI as the parent of the QTimer
    connect(timer,
            &QTimer::timeout,
            this,
            &openMeteoAPI::onTimeout); // Connect the timeout signal to the slot
    timer->start(60000);               // Start the timer in ms interval (1min)
}

void openMeteoAPI::serviceRequestFinished(QNetworkReply *networkReply)
{
    m_reply = networkReply;
    if (m_reply->error() != QNetworkReply::NoError) {
        qCritical() << m_reply->errorString();
        return;
    }
    qDebug() << "Request received";
    // Parse the JSON response
    QByteArray response = m_reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(response);
    m_jsonInfoWeather = doc.object();
    m_reply->deleteLater();
    m_bIsDataAvailable = true;
    emit requestFinished();
}

void openMeteoAPI::onTimeout()
{
    static QDate lastCheckedDate = QDate::currentDate();
    QDate currentDate = QDate::currentDate();
    // If the date has changed
    if (currentDate != lastCheckedDate) {
        lastCheckedDate = currentDate;
        fetchWeather();
    }
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

QJsonObject openMeteoAPI::getListDailyWeatherData()
{
    if (m_jsonInfoWeather.empty()) {
        qCritical() << "Daily weather data not available";
        return QJsonObject();
    }
    return m_jsonInfoWeather["daily"].toObject();
}

QJsonObject openMeteoAPI::getCurrentWeatherData()
{
    if (m_jsonInfoWeather.empty()) {
        qCritical() << "Current weather data not available";
        return QJsonObject();
    }
    return m_jsonInfoWeather["current"].toObject();
}
