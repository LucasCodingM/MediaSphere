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

void Global::initVideoPlayerSettings(const QList<structVideoPlayerSettings> &listSettingsData)
{
    QSettings settings;
    // Deleting videoPlayer settings before initialisation
    removeVideoPlayerSettings();
    settings.beginWriteArray("videoPlayer");
    for (int i = 0; i < listSettingsData.size(); ++i) {
        settings.setArrayIndex(i);
        settings.setValue("videoPath", listSettingsData[i].s_videoPath); // name
        settings.setValue("videoName", listSettingsData[i].s_videoName); // file path
        settings.setValue("thumbnail",
                          listSettingsData[i].s_thumbnail); // QImage as byte array
    }
    settings.endArray();
    qDebug() << "initVideoPlayerSettings ended successfully";
}

void Global::appendVideoPlayerSettings(const QList<Global::structVideoPlayerSettings> &listSettingsData)
{
    QSettings settings;

    QList<structVideoPlayerSettings> newListSettingsData = retrieveVideoPlayerSettings()
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

QList<Global::structVideoPlayerSettings> Global::getOnlyNewSettings(
    const QList<Global::structVideoPlayerSettings> &pendingList)
{
    QList<Global::structVideoPlayerSettings> validatedNewSettings = pendingList;
    const QList<structVideoPlayerSettings> currentListSettings = retrieveVideoPlayerSettings();
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
    const QList<structVideoPlayerSettings> currentListSettings = retrieveVideoPlayerSettings();
    for (auto &currentSettings : currentListSettings) {
        if (videoPath == currentSettings.s_videoPath) {
            return false;
        }
    }
    return true;
}

void Global::removeVideoPathFromSettings(const QString &videoPath)
{
    QList<Global::structVideoPlayerSettings> listVideoPlayerSettings = retrieveVideoPlayerSettings();
    bool hasBeenRemoved = false;
    // Find and remove the Login entry with the given videoPath
    for (int i = 0; i < listVideoPlayerSettings.size(); ++i) {
        if (listVideoPlayerSettings[i].s_videoPath == videoPath) {
            listVideoPlayerSettings.removeAt(i); // Remove the element
            hasBeenRemoved = true;
            break; // Exit once the matching user is found and removed
        }
    }
    if (hasBeenRemoved) {
        qDebug() << videoPath << " has been removed";
        initVideoPlayerSettings(listVideoPlayerSettings);
    } else
        qWarning() << videoPath << " has not been removed -> reason: not found";
}

void Global::removeSettings(const QString settingsName)
{
    QSettings settings;
    settings.remove(settingsName);
}

void Global::clearAllSettings()
{
    QSettings settings;
    settings.clear();
}

QList<Global::structVideoPlayerSettings> Global::retrieveVideoPlayerSettings()
{
    QSettings settings;
    QList<structVideoPlayerSettings> listSettingsData;

    int size = settings.beginReadArray("videoPlayer");
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        structVideoPlayerSettings s_settings(settings.value("videoPath").toString(),
                                  settings.value("videoName").toString(),
                                  settings.value("thumbnail").toString());
        listSettingsData.append(s_settings);
    }
    settings.endArray();
    return listSettingsData;
}
