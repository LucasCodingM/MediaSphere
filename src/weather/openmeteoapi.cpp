#include "openmeteoapi.h"

#include <QThread>
#include <QUrlQuery>

openMeteoAPI::openMeteoAPI(QObject *parent)
    : QObject{parent}
    , m_urlInfoWeather("https://api.open-meteo.com/v1/forecast")
    , m_urlInfoIp("https://ipinfo.io/json")
    , m_mapUrlQueryItem(
          QMap<QString, QString>({{"latitude", "48.112"},
                                  {"longitude", "-1.6743"},
                                  {"current", "temperature_2m,weather_code,is_day"},
                                  {"daily", "weather_code,temperature_2m_max,temperature_2m_min"},
                                  {"timezone", "auto"},
                                  {"forecast_days", "3"}}))
    , m_jsonInfoWeather(QJsonObject())
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
    timer->start(60000);               // Start the timer in ms interval (1h)
}

void openMeteoAPI::serviceRequestFinished(QNetworkReply *networkReply)
{
    if (networkReply->error() != QNetworkReply::NoError) {
        qCritical() << networkReply->errorString();
        return;
    }
    updateDataFromRequest(networkReply);
    networkReply->deleteLater();
}

void openMeteoAPI::updateDataFromRequest(QNetworkReply *networkReply)
{
    // Parse the JSON response
    QByteArray response = networkReply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(response);
    // Retrieve the custom attribute (requestId) from the request
    QString requestId = networkReply->request().attribute(QNetworkRequest::User).toString();
    if (requestId == "infoWeather") {
        qDebug() << "infoWeather received";
        m_jsonInfoWeather = doc.object();
        m_bIsDataAvailable = true;
        emit requestFinished(); // signal the weather GUI to update data
    } else if (requestId == "infoIp") {
        qDebug() << "infoIp received";
        // Init the urlInfoWeather with location parameter and others if needed
        initUrlInfoWeatherParameter(doc);
        // Finally get the info weather
        makeRequest(m_urlInfoWeather, "infoWeather");
    } else
        qCritical() << "Request received but requestId unknown";
}

void openMeteoAPI::makeRequest(const QUrl &qUrl, const QString &requestId)
{
    // Set a custom property (identifier) for the request
    QNetworkRequest request(qUrl);
    request.setAttribute(QNetworkRequest::User, requestId);
    // Send the request
    m_networkManager->get(QNetworkRequest(request));
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
    clearJsonDataWeather();
    // First get the location
    // Then when serviceRequestFinished received the signal the weather will be fetched
    makeRequest(m_urlInfoIp, "infoIp");
}

void openMeteoAPI::clearJsonDataWeather()
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

void openMeteoAPI::addLocationInMapUrlQueryItem(QString latitude, QString longitude)
{
    if (!m_mapUrlQueryItem.empty()) {
        m_mapUrlQueryItem["latitude"] = latitude;
        m_mapUrlQueryItem["longitude"] = longitude;
    }
}

void openMeteoAPI::fillUrlInfoWeatherQueryItem()
{
    // Create a QUrlQuery object
    QUrlQuery query;
    QMapIterator<QString, QString> it(m_mapUrlQueryItem);
    while (it.hasNext()) {
        it.next();
        query.addQueryItem(it.key(), it.value());
    }
    m_urlInfoWeather.setQuery(query);
}

void openMeteoAPI::initUrlInfoWeatherParameter(const QJsonDocument &jsonDoc)
{
    // Split the string to get the latitude and longitude coordinates;
    QList<QString> sLocation = jsonDoc["loc"].toString().split(',');
    addLocationInMapUrlQueryItem(sLocation.at(0), sLocation.at(1));
    fillUrlInfoWeatherQueryItem();
}
