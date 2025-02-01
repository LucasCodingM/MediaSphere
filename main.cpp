#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "customexception.h"
#include "logger.h"
#include "openmeteoapi.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("RaspGui", "Main");

    try {
        Logger oLogger("application.log"); // Log to 'application.log' file
        openMeteoAPI openMeteoApi;
        openMeteoApi.fetchWeather();
        openMeteoApi.getTemperature();
    } catch (const CustomException &e) {
        // Catching the custom exception and handling it
        qCritical() << e.getDetailMessage();
    }

    return app.exec();
}
