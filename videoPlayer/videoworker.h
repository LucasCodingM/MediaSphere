/**
 * @file videoworker.h
 * @brief VideoWorker class declaration.
 *
 * This class provides asynchronous video processing capabilities, allowing for efficient playback of multiple videos in sequence without blocking the main thread. It also manages thumbnail image extraction and updates associated selection models with new information.
 */

#ifndef VIDEOWORKER_H
#define VIDEOWORKER_H

#include <QFileInfo>
#include <QObject>
#include <QSettings>
#include <QThread>
#include <QUrl>
#include "shared/global.h"
#include "videoselectionmodel.h"
#include "videothumbnailextractor.h"

/**
 * @class VideoWorker
 * @brief A worker thread responsible for processing video files and URLs asynchronously.
 *
 * This class provides asynchronous video playback capabilities, 
 * allowing the main thread to remain responsive while videos are being processed. 
 * It also manages thumbnail image extraction and updates associated selection models with new information.
 */
class VideoWorker : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for VideoWorker.
     *
     * Initializes a new instance of the VideoWorker class with the given settings, video selection model, and parent object. 
     * The worker thread is created automatically when this function is called.
     *
     * @param settings A reference to the player's settings, which can include video playback preferences.
     * @param videoSelectionModel A pointer to the selection model that manages the current media file or URL.
     * @param videoThumbNailExtractor An instance of VideoThumbNailExtractor used for thumbnail image extraction. 
     *        Defaults to nullptr.
     * @param parent The parent object to which this worker belongs. Defaults to nullptr.
     */
    explicit VideoWorker(QSettings &settings,
                         VideoSelectionModel *videoSelectionModel,
                         VideoThumbNailExtractor &videoThumbNailExtractor,
                         QObject *parent = nullptr);

    /**
     * @brief Appends a new video path to the current media source asynchronously.
     *
     * Adds a new video file or URL to the player's media source, allowing it to play back multiple videos in sequence. 
     * The new path is appended after any existing paths without blocking the main thread.
     *
     * @param newPath The new video path to append.
     */
    void appendVideoPathAsync(const QString &newPath);

    /**
     * @brief Appends a new video file or URL to the current media source in videos collections asynchronously.
     *
     * Adds a new video file or URL to the player's media source, allowing it to play back multiple videos in sequence.
     * The new path is appended after any existing paths without blocking the main thread.
     *
     * @param newPath The new video path to append.
     */
    void appendInVideosCollections(QString newPath);

    /**
     * @brief Updates data in the associated selection model asynchronously.
     *
     * Triggers an asynchronous update of the selected media file or URL, 
     * which can be used for display purposes (e.g., displaying thumbnails).
     */
    void updateDataInModelAsync();

    /**
     * @brief Exposes a thumbnail image to QML-based user interfaces.
     *
     * Returns a QImage object representing the specified video file or URL as an image. 
     * This function is typically called from within the selection model's slot 
     * that updates its data asynchronously using this worker thread.
     *
     * @param thumbnail A reference to the output image, which will be populated with the extracted thumbnail representation of the given media source.
     */
    QString exposeThumbnailToQml(QImage &thumbnail);

    /**
     * @brief Keeps only valid video files in videos collections.
     *
     * Removes any invalid or corrupted video files from the player's media source. 
     * This function is typically called periodically to maintain a clean and up-to-date list of available video content.
     */
    void keepOnlyValidVideoFiles();

    /**
     * @brief Checks if a file exists at the specified URL asynchronously.
     *
     * Returns true if the given URL points to an existing valid media source; otherwise returns false. 
     * This function is typically called from within the selection model's slot 
     * that updates its data asynchronously using this worker thread.
     *
     * @param urlFile A reference to the current media source (e.g., a QUrl).
     * @return True if the file exists, false otherwise.
     */
    bool fileExist(const QUrl &urlFile);

    void deleteVideo(const QString &videoPath);

signals:
    /**
     * @brief Signal emitted when data is ready to be updated in the model asynchronously.
     *
     * This signal is triggered by this worker thread after it has finished processing any pending video files or URLs. 
     * It updates the associated selection model with new information, 
     * which can then be used for display purposes (e.g., displaying thumbnails).
     */
    void fetchingDataReady(const Global::structVideoPlayerSettings &videoPlayerSettings);

private:
    QSettings &
        m_settings; /**< A reference to the player's settings, which can include video playback preferences. */

    VideoSelectionModel *
        m_videoSelectionModel; /**< A pointer to the selection model that manages the current media file or URL. */

    VideoThumbNailExtractor
        m_videoThumbNailExtractor; /**< An instance of VideoThumbNailExtractor used for thumbnail image extraction. */
};

#endif // VIDEOWORKER_H
