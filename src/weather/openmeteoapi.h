#ifndef OPENMETEOAPI_H
#define OPENMETEOAPI_H

/**
 * @file openmeteoapi.h
 * @brief Provides access to OpenMeteo API for weather forecasts.
 * 
 * This file contains the implementation of the openMeteoAPI class, which provides methods to fetch weather data
 * from the OpenMeteo API, handle the network requests, and manage the weather data.
 * 
 * The class interacts with the OpenMeteo API to fetch current and forecast weather data.
 */

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QTimer>

/**
 * @brief Constructs a new openMeteoAPI object.
 * 
 * Initializes the OpenMeteo API interface, sets default values for weather-related query parameters, and sets up 
 * a network manager to handle requests. It also sets up a timer to periodically fetch weather data.
 * 
 * @param parent The parent QObject for this instance.
 */
class openMeteoAPI : public QObject
{
    Q_OBJECT
public:
    explicit openMeteoAPI(QObject *parent = nullptr);

    /**
 * @brief Clears the stored weather data.
 * 
 * This method clears the stored weather data to reset the internal state.
 */
    void clearJsonDataWeather();
    /**
 * @brief Fetches the latest weather data.
 * 
 * This method initiates the process to fetch weather data by first requesting location information. 
 * Once the location is retrieved, a subsequent request is made for the weather data.
 */
    Q_INVOKABLE void fetchWeather();

    /**
 * @brief Checks if weather data is available.
 * 
 * @return True if the weather data is available, false otherwise.
 */
    Q_INVOKABLE bool getIsDataAvailable();
    /**
 * @brief Retrieves the daily weather data.
 * 
 * This method returns the daily weather data from the stored JSON response. 
 * If the data is not available, it logs an error and returns an empty JSON object.
 * 
 * @return A QJsonObject containing the daily weather data.
 */
    Q_INVOKABLE QJsonObject getListDailyWeatherData();

    /**
 * @brief Retrieves the current weather data.
 * 
 * This method returns the current weather data from the stored JSON response.
 * If the data is not available, it logs an error and returns an empty JSON object.
 * 
 * @return A QJsonObject containing the current weather data.
 */
    Q_INVOKABLE QJsonObject getCurrentWeatherData();

    /**
 * @brief Initializes the weather request URL with the location parameters.
 * 
 * This method extracts the latitude and longitude from the provided JSON document and updates the request URL.
 * 
 * @param jsonDoc The JSON document containing location information.
 */
    void initUrlInfoWeatherParameter(const QJsonDocument &jsonDoc);
    /**
 * @brief Adds a location (latitude and longitude) to the URL query parameters.
 * 
 * This method updates the query parameters in the URL to include the provided latitude and longitude.
 * 
 * @param latitude The latitude of the location.
 * @param longitude The longitude of the location.
 */
    void addLocationInMapUrlQueryItem(QString latitude, QString longitude);
    /**
 * @brief Makes a network request to a given URL.
 * 
 * This method sends a GET request to the provided URL with a custom request identifier.
 * 
 * @param qUrl The URL to send the request to.
 * @param requestId A string identifier for the request.
 */
    void makeRequest(const QUrl &qUrl, const QString &requestId);
    /**
 * @brief Fills the URL query parameters for the weather request.
 * 
 * This method constructs the query parameters for the weather request using the data stored in m_mapUrlQueryItem.
 * The URL is then updated with these parameters.
 */
    void fillUrlInfoWeatherQueryItem();
    /**
 * @brief Updates internal data based on the network reply.
 * 
 * This method parses the JSON response from the API and stores the data based on the request ID.
 * It also emits a signal when the data has been successfully updated.
 * 
 * @param networkReply The network reply containing the response data.
 */
    void updateDataFromRequest(QNetworkReply *networkReply);

    /** @brief Return m_mapUrlQueryItem*/
    QMap<QString, QString> getUrlQueryItem() { return m_mapUrlQueryItem; }

signals:
    /**
 * @brief Signal that the request has been processed and the data is ready.
 * 
 * This method is connected to the Weather.qml file and is used to tell to the GUI to update the data
 */
    void requestFinished();
public slots:
    /**
 * @brief Handles the completion of a network request.
 * 
 * This method is called when a network request finishes. It checks if the request was successful and processes
 * the response data. If there is an error, it logs the error message.
 * 
 * @param networkReply The network reply containing the response.
 */
    void serviceRequestFinished(QNetworkReply *networkReply);
    /**
 * @brief Periodically checks and updates weather data if the date has changed.
 * 
 * This method is called every minute to check if the date has changed. If it has, it triggers a fetch for new weather data.
 */
    void onTimeout();

private:
    QUrl m_urlInfoWeather; /**< This property contains the URL used to send a request to the OpenMeteo API to fetch weather data.*/
    const QUrl
        m_urlInfoIp; /**< This constant property holds the URL for sending a request to fetch the IP information, primarily for determining
                                the user's location (latitude and longitude).*/
    QMap<QString, QString>
        m_mapUrlQueryItem; /**< This map contains the necessary query parameters such as latitude, longitude, forecast days, and more, which are
                                                    appended to the weather API request URL for fetching specific weather information.*/
    QNetworkAccessManager *
        m_networkManager; /**< This property is a pointer to a `QNetworkAccessManager`, which handles all HTTP requests and responses for
                                                    retrieving data from the weather API and IP info API.*/
    QJsonObject
        m_jsonInfoWeather; /**< This property contains the weather data received from the OpenMeteo API in the form of a `QJsonObject`. It includes
                                        scurrent weather information, forecasts, and other relevant data.*/
    bool m_bIsDataAvailable; /**< This boolean flag indicates whether the weather data is available or not. It is set to `false` when data is being
                                     fetched or updated, and `true` when the weather data has been successfully retrieved.*/
signals:
};

#endif // OPENMETEOAPI_H
