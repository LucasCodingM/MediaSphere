#ifndef GLOBAL_H
#define GLOBAL_H
#include <QMutex>
#include <QMutexLocker>
#include <QUrl>

class Global
{
public:
    // Method to access the instance of the singleton class
    static Global *getInstance();

    // Prevent copying of the instance
    Global(const Global &) = delete;
    Global &operator=(const Global &) = delete;

    // Nested struct inside the Singleton class
    struct structVideoPlayerSettings
    {
        QString s_videoPath;
        QString s_videoName;
        QString s_thumbnail;

        structVideoPlayerSettings(QString videoPath, QString videoName, QString thumbnail)
            : s_videoPath(videoPath)
            , s_videoName(videoName)
            , s_thumbnail(thumbnail)
        {}
    };

    void initVideoPlayerSettings(const QList<Global::structVideoPlayerSettings> &listSettingsData);
    // Store the settings in the system. In this way, settings will be saved even after reboot
    void appendVideoPlayerSettings(const QList<Global::structVideoPlayerSettings> &listSettingsData);
    QList<structVideoPlayerSettings> getOnlyNewSettings(
        const QList<Global::structVideoPlayerSettings> &pendingList);
    QList<structVideoPlayerSettings> retrieveVideoPlayerSettings();
    void removeVideoPlayerSettings() { removeSettings("VideoPlayer"); }
    void removeSettings(const QString settingsName);
    void clearAllSettings();
    bool isNewVideoPlayerDataSettings(const QString &videoPath);

    void removeVideoPathFromSettings(const QString &videoPath);

private:
    // Private constructor to prevent instantiating from outside
    Global() {}
    // Destructor
    ~Global() {}
    // Static member to hold the single instance
    static Global *m_instance;
};

#endif // GLOBAL_H
