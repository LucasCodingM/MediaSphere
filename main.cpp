#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "shared/customexception.h"
#include "shared/logger/logger.h"
#include "videoPlayer/videoplayer.h"
#include "weather/openmeteoapi.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Logger oLogger("application.log"); // Log to 'application.log' file
    // Expose the object to QML context
    openMeteoAPI openMeteoApi;

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    qmlRegisterType<videoPlayer>("VideoPlayerModule", 1, 0, "VideoPlayer");
    engine.rootContext()->setContextProperty("openMeteoApi", &openMeteoApi);
    engine.loadFromModule("RaspGui", "Main");
    // Register the VideoPlayer class to QML

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
