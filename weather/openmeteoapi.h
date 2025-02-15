#ifndef OPENMETEOAPI_H
#define OPENMETEOAPI_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QTimer>

//Requête https pour récupérer la météo
//https://api.open-meteo.com/v1/forecast?latitude=48.11&longitude=-1.6744&hourly=temperature_2m,weather_code&timezone=auto&forecast_days=3
class openMeteoAPI : public QObject
{
    Q_OBJECT
public:
    explicit openMeteoAPI(QObject *parent = nullptr);

    void clearJsonDataWeather();
    Q_INVOKABLE void fetchWeather();
    Q_INVOKABLE bool getIsDataAvailable();
    Q_INVOKABLE QJsonObject getListDailyWeatherData();
    Q_INVOKABLE QJsonObject getCurrentWeatherData();
    void initUrlInfoWeatherParameter(const QJsonDocument &jsonDoc);
    void addLocationInMapUrlQueryItem(QString latitude, QString longitude);
    void makeRequest(const QUrl &qUrl, const QString &requestId);
    void fillUrlInfoWeatherQueryItem();
    void updateDataFromRequest(QNetworkReply *networkReply);
signals:
    void requestFinished();
public slots:
    void serviceRequestFinished(QNetworkReply *networkReply);
    void onTimeout();

private:
    // Contains the url request
    QUrl m_urlInfoWeather;
    // Contains the url request for ip info (mainly for localisation)
    const QUrl m_urlInfoIp;
    QMap<QString, QString> m_mapUrlQueryItem;
    // Manage the http request
    QNetworkAccessManager *m_networkManager;
    // Data about the weather in json format fetched on api.open-meteo.com
    QJsonObject m_jsonInfoWeather;
    // Boolean about the data avaibility's state. The data is false during an update period or when the data weather
    // has not been successfully fetched
    bool m_bIsDataAvailable;
signals:
};

#endif // OPENMETEOAPI_H
