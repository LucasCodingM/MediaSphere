#ifndef GLOBAL_H
#define GLOBAL_H
#include <QMutex>
#include <QMutexLocker>

class Global
{
public:
    // Method to access the instance of the singleton class
    static Global *getInstance();

    // Prevent copying of the instance
    Global(const Global &) = delete;
    Global &operator=(const Global &) = delete;

    // Nested struct inside the Singleton class
    struct structSettings
    {
        QString s_videoPath;
        QString s_videoName;
        QString s_thumbnail;

        structSettings(QString videoPath, QString videoName, QString thumbnail)
            : s_videoPath(videoPath)
            , s_videoName(videoName)
            , s_thumbnail(thumbnail)
        {}
    };

    // Store the settings in the system. In this way, settings will be saved even after reboot
    void appendVideoPlayerSettings(const QList<Global::structSettings> &listSettingsData);
    QList<structSettings> getOnlyNewSettings(const QList<Global::structSettings> &pendingList);
    QList<structSettings> retrieveVideoPlayerSettings();
    void removeVideoPlayerSettings() { removeSettings("VideoPlayer"); }
    void removeSettings(const QString settingsName);
    bool isNewVideoPlayerDataSettings(const QString &videoPath);

private:
    // Private constructor to prevent instantiating from outside
    Global() {}
    // Destructor
    ~Global() {}
    // Static member to hold the single instance
    static Global *m_instance;
};

#endif // GLOBAL_H
