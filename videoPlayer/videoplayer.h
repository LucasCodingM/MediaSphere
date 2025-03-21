/**
 * @file videoplayer.h
 * @brief VideoPlayer class declaration.
 *
 * This class is a subclass of QMediaPlayer, providing additional functionality
 * specific to video playback. It allows for appending new video paths, replaying,
 * checking the validity of the source, and retrieving the associated selection model.
 */

#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QAudioOutput>
#include <QDebug>
#include <QMediaPlayer>
#include <QObject>
#include <QSettings>
#include <QUrl>
#include "shared/global.h"
#include "videoselectionmodel.h"
#include "videothumbnailextractor.h"
#include "videoworker.h"

/**
 * @class VideoPlayer
 * @brief A subclass of QMediaPlayer for video playback.
 *
 * This class provide a media player with additonnal functionalities such
 * as method to get and update the video model data, and others
 */
class VideoPlayer : public QMediaPlayer
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for VideoPlayer.
     *
     * Initializes a new instance of the VideoPlayer class with the given parent object.
     *
     * @param parent The parent object to which this player belongs. Defaults to nullptr.
     */
    explicit VideoPlayer(QObject *parent = nullptr);

    /**
     * @brief Destructor for VideoPlayer.
     *
     * Cleans up any resources allocated by the VideoPlayer instance.
     */
    ~VideoPlayer();

    /**
     * @brief Appends a new video path to the current media source.
     *
     * Adds a new video file or URL to the player's media source.
     * This methos calls the videoWorker class to do it asynchronously
     *
     * @param newPath The new video path to append.
     */
    Q_INVOKABLE void appendVideoPath(const QString &newPath);

    /**
     * @brief Replays the current media source.
     *
     * Starts playing back the currently selected media file or URL. If no media is
     * set, this function does nothing.
     */
    Q_INVOKABLE void replay();

    /**
     * @brief Checks if the current media source is valid.
     *
     * Returns true if a valid media source has been established; otherwise returns false.
     *
     * @return True if the source is valid, false otherwise.
     */
    Q_INVOKABLE bool sourceIsValid();

    /**
     * @brief Retrieves model data display in the QML videoPlayer menu.
     *
     * Returns a pointer to the VideoSelectionModel instance that manages the list of video.
     * 
     * @return A pointer to the VideoSelectionModel instance.
     */
    Q_INVOKABLE VideoSelectionModel *getVideoSelectionModel();

    Q_INVOKABLE void deleteVideo(const QString &videoPath);

protected:
    /**
     * @brief Sets up the video source for the VideoPlayer.
     *
     * This function retrieves the video player settings from the Global instance
     * and sets the video source to the last video path in the settings if available.
     * If no video path is found, the source remains unchanged.
     *
     * @details The function first checks if the video player settings are not empty.
     * If settings are available, it retrieves the last video path from the settings.
     * Then, it checks if the retrieved URL is not empty and sets it as the source
     * for the video player.
     */
    void setupToLastValidSource();

    /**
     * @brief Retrieves a thumbnail image from the specified video path.
     *
     * Extracts an image representation of the given video file or URL, which can be used
     * to display thumbnails in QML-based user interfaces. The returned image is stored as a QImage object.
     *
     * @param videoPaths A reference to an media source (e.g., a QUrl).
     * @return An image representation of the specified video file or URL, represented as a QImage object.
     */
    QImage getThumbnailVideoFromUrl(const QUrl &videoPaths);

private slots:
    /**
     * @brief Slot called when data is ready to be updated in the model.
     *
     * This function is triggered by the VideoWorker instance after it has finished processing
     * any pending video files or URLs. It updates the associated selection model with new information,
     * which can then be used for display purposes (e.g., displaying thumbnails).
     */
    void onFetchingDataReady(const Global::structVideoPlayerSettings &videoPlayerSettings);

private:
    QSettings m_settings; /**< The player's settings, which can include video playback preferences. */

    VideoSelectionModel *
        m_videoSelectionModel; /**< A pointer to the instance that manage the videoPlayer model data*/

    VideoThumbNailExtractor
        m_videoThumbNailExtractor; /**< An instance of VideoThumbNailExtractor used for thumbnail image extraction. */

    VideoWorker
        m_videoWorker; /**< The video worker class responsible for processing data asynchronously. */
    QThread *
        m_workerThread; /**< A pointer to the worker thread, which enable videoWorker to process asynchronously. */
};

#endif // VIDEOPLAYER_H
