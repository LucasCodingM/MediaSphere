#ifndef GLOBAL_H
#define GLOBAL_H
#include <QMutex>
#include <QMutexLocker>
#include <QUrl>

/**
 * @class Global
 * @brief Singleton class to manage global settings for the application.
 *
 * This class provides methods to initialize, retrieve, and manipulate global settings,
 * specifically for video player settings. It ensures thread safety when accessing the
 * singleton instance.
 */
class Global
{
public:
    /**
     * @brief Get the singleton instance of the Global class.
     *
     * This method ensures that only one instance of the Global class exists.
     * It uses a mutex to ensure thread safety during instance creation.
     *
     * @return The singleton instance of the Global class.
     */
    static Global *getInstance();

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

    /**
     * @brief Initialize video player settings.
     *
     * This method writes a list of video player settings to the application's settings.
     * It removes any existing settings before writing the new ones.
     *
     * @param listSettingsData The list of video player settings to initialize.
     */
    void initVideoPlayerSettings(const QList<Global::structVideoPlayerSettings> &listSettingsData);
    /**
     * @brief Append new video player settings to the existing settings. In this way, settings will be saved even after reboot
     *
     * This method adds new video player settings to the existing settings, ensuring
     * that only new settings are added.
     *
     * @param listSettingsData The list of new video player settings to append.
     */
    void appendVideoPlayerSettings(const QList<Global::structVideoPlayerSettings> &listSettingsData);
    /**
     * @brief Retrieve only new video player settings from a pending list.
     *
     * This method compares a pending list of settings with the current settings and
     * returns only the new settings that are not already present.
     *
     * @param pendingList The list of pending video player settings.
     * @return A list of new video player settings that are not already present.
     */
    QList<structVideoPlayerSettings> getOnlyNewSettings(
        const QList<Global::structVideoPlayerSettings> &pendingList);
    /**
     * @brief Retrieve the current video player settings.
     *
     * This method reads the video player settings from the application's settings and
     * returns them as a list.
     *
     * @return The list of current video player settings.
     */
    QList<structVideoPlayerSettings> retrieveVideoPlayerSettings();
    /**
     * @brief Remove a video path from the video player settings.
     *
     * This method removes the settings associated with a given video path.
     *
     * @param videoPath The video path to remove.
     */
    void removeVideoPlayerSettings() { removeSettings("VideoPlayer"); }
    /**
     * @brief Remove a specific setting by name.
     *
     * This method removes a setting identified by its name from the application's settings.
     *
     * @param settingsName The name of the setting to remove.
     */
    void removeSettings(const QString settingsName);
    /**
     * @brief Clear all settings.
     *
     * This method clears all settings stored in the application.
     */
    void clearAllSettings();
    /**
     * @brief Check if a video path is new in the video player settings.
     *
     * This method checks if a given video path is already present in the current settings.
     *
     * @param videoPath The video path to check.
     * @return True if the video path is new, false otherwise.
     */
    bool isNewVideoPlayerDataSettings(const QString &videoPath);

    /**
     * @brief Remove a video path from the video player settings.
     *
     * This method searches for a video path in the current video player settings and removes
     * the corresponding entry if found. It then updates the settings with the modified list.
     *
     * @param videoPath The video path to remove from the settings.
     */
    void removeVideoPathFromSettings(const QString &videoPath);

private:
    Global() = default;                         /**< Private constructor for singleton pattern. */
    Global(const Global &) = delete;            /**< Deleted copy constructor. */
    Global &operator=(const Global &) = delete; /**< Deleted assignment operator. */
    ~Global() = default;                        /**< Destructor. */

    static Global *m_instance; /**< Singleton instance of the Global class. */
};

#endif // GLOBAL_H
