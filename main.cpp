#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "customexception.h"
#include "logger.h"
#include "openmeteoapi.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Logger oLogger("application.log"); // Log to 'application.log' file
    openMeteoAPI openMeteoApi;

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    // Expose the object to QML context
    engine.rootContext()->setContextProperty("openMeteoApi", &openMeteoApi);
    engine.loadFromModule("RaspGui", "Main");

    try {
        openMeteoApi.fetchWeather();
    } catch (const CustomException &e) {
        // Catching the custom exception and handling it
        qCritical() << e.what();
    } catch (...) {
        std::cerr << "Caught unknown exception!" << std::endl;
    }

    return app.exec();
}
