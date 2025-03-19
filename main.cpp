#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTranslator>
#include <QQuickStyle>
#include "shared/logger/logger.h"
#include "videoPlayer/videoplayer.h"
#include "weather/openmeteoapi.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QCoreApplication::setOrganizationName("LucasCodingM");
    QCoreApplication::setApplicationName("MediaSphere");

    // Set the style globally for the application
    QQuickStyle::setStyle("Fusion");

    Logger oLogger("application.log"); // Log to 'application.log' file
    // Expose the object to QML context
    openMeteoAPI openMeteoApi;

    // Create a QTranslator object and load a translation file (e.g., en.qm)
    QTranslator translator;
    if (translator.load("MediaSphere_fr.qm")) {
        app.installTranslator(&translator);
        qInfo() << "Loading translations files";
    }

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
    engine.loadFromModule("MediaSphere", "Main");

    return app.exec();
}
