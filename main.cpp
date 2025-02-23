#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
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

    qmlRegisterType<VideoPlayer>("VideoPlayerModule", 1, 0, "VideoPlayer");
    qmlRegisterType<VideoSelectionModel>("VideoSelection", 1, 0, "VideoSelectionModel");

    engine.rootContext()->setContextProperty("openMeteoApi", &openMeteoApi);
    engine.loadFromModule("RaspGui", "Main");

    return app.exec();
}
