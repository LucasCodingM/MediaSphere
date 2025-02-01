#ifndef OPENMETEOAPI_H
#define OPENMETEOAPI_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>

//Requête https pour récupérer la météo
//https://api.open-meteo.com/v1/forecast?latitude=48.11&longitude=-1.6744&hourly=temperature_2m,weather_code&timezone=auto&forecast_days=3
class openMeteoAPI : public QObject
{
    Q_OBJECT
public:
    explicit openMeteoAPI(QObject *parent = nullptr);

    void fetchWeather();
    Q_INVOKABLE QJsonArray getListDaysWeatherCode();
    Q_INVOKABLE double getTemperature();

public slots:
    void serviceRequestFinished(QNetworkReply *networkReply);

private:
    const QUrl m_url;
    QNetworkReply *m_reply;
    QNetworkAccessManager *m_networkManager;
    QJsonObject m_jsonInfoWeather;
signals:
};

#endif // OPENMETEOAPI_H
