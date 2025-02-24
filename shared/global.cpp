#include "global.h"

#include <QSettings>

// Initialize the static member to nullptr
Global *Global::m_instance = nullptr;

Global *Global::getInstance()
{
    // This ensures thread safety while creating the singleton instance
    static QMutex mutex;         // Mutex to protect the creation of the singleton
    QMutexLocker locker(&mutex); // Locking mutex to ensure thread safety

    if (!m_instance) {
        m_instance = new Global();
    }

    return m_instance;
}

void Global::appendVideoPlayerSettings(const QList<Global::structSettings> &listSettingsData)
{
    QSettings settings;

    QList<structSettings> newListSettingsData = retrieveVideoPlayerSettings()
                                                + getOnlyNewSettings(listSettingsData);

    // Store data in QSettings
    settings.beginWriteArray("videoPlayer");
    for (int i = 0; i < newListSettingsData.size(); ++i) {
        settings.setArrayIndex(i);
        settings.setValue("videoPath", newListSettingsData[i].s_videoPath); // name
        settings.setValue("videoName", newListSettingsData[i].s_videoName); // file path
        settings.setValue("thumbnail",
                          newListSettingsData[i].s_thumbnail); // QImage as byte array
    }
    settings.endArray();
}

QList<Global::structSettings> Global::getOnlyNewSettings(
    const QList<Global::structSettings> &pendingList)
{
    QList<Global::structSettings> validatedNewSettings = pendingList;
    const QList<structSettings> currentListSettings = retrieveVideoPlayerSettings();
    for (int i = 0; i < pendingList.size(); i++) {
        for (int j = 0; j < currentListSettings.size(); ++j) {
            if (pendingList[i].s_videoPath == currentListSettings[j].s_videoPath) {
                validatedNewSettings.remove(i);
            }
        }
    }
    return validatedNewSettings;
}

bool Global::isNewVideoPlayerDataSettings(const QString &videoPath)
{
    const QList<structSettings> currentListSettings = retrieveVideoPlayerSettings();
    for (auto &currentSettings : currentListSettings) {
        if (videoPath == currentSettings.s_videoPath) {
            return false;
        }
    }
    return true;
}

void Global::removeSettings(const QString settingsName)
{
    QSettings settings;
    settings.remove(settingsName);
}

QList<Global::structSettings> Global::retrieveVideoPlayerSettings()
{
    QSettings settings;
    QList<structSettings> listSettingsData;

    int size = settings.beginReadArray("videoPlayer");
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        structSettings s_settings(settings.value("videoPath").toString(),
                                  settings.value("videoName").toString(),
                                  settings.value("thumbnail").toString());
        listSettingsData.append(s_settings);
    }
    settings.endArray();
    return listSettingsData;
}
