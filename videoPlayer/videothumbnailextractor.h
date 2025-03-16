#ifndef VIDEOTHUMBNAILEXTRACTOR_H
#define VIDEOTHUMBNAILEXTRACTOR_H

/**
 * @file VideoThumbNailExtractor.h
 * @brief Extracts thumbnails from videos.
 */

#include <QBuffer>
#include <QDebug>
#include <QEventLoop>
#include <QImage>
#include <QMediaPlayer>
#include <QObject>
#include <QVideoFrame>
#include <QVideoSink>

/**
 * @class VideoThumbNailExtractor
 * @brief Extracts a thumbnail image from a video at a specified time.
 *
 * This class uses QMediaPlayer and QVideoSink to capture a frame from a video
 * at a given time and convert it into a QImage. It is useful for generating
 * video thumbnails.
 */
class VideoThumbNailExtractor : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor for VideoThumbNailExtractor.
     *
     * Initializes the media player and video sink, and sets up the necessary
     * connections to capture video frames.
     *
     * @param parent The parent object.
     */
    explicit VideoThumbNailExtractor(QObject *parent = nullptr);

    ~VideoThumbNailExtractor()
    {
        if (m_loop.isRunning()) {
            m_loop.quit();
        }
    }

    /**
     * @brief Retrieves a thumbnail image from a video at a specified time.
     *
     * This method sets the video source, plays the video, and captures a frame
     * at the specified time to use as a thumbnail.
     *
     * @param videoUrl The URL of the video.
     * @param timeInMilliseconds The time in milliseconds at which to capture the thumbnail.
     * @return The captured thumbnail image.
     */
    QImage getVideoThumbnail(const QUrl &videoUrl, int timeInMilliseconds = 1000);

private slots:
    /**
     * @brief Slot to handle changes in the video frame.
     *
     * This method is called when the video frame changes. It captures the frame
     * and converts it to a QImage if the frame is valid.
     *
     * @param frame The current video frame.
     */
    void onVideoFrameChanged(const QVideoFrame &frame);
    /**
     * @brief Slot to handle changes in the media player's position.
     *
     * This method is called when the media player's position changes. It stops
     * the player and exits the event loop when the desired position is reached.
     *
     * @param position The current position in milliseconds.
     */
    void onPositionChanged(qint64 position);

private:
    QMediaPlayer *m_player;  /**< Media player to play the video. */
    QVideoSink *m_videoSink; /**< Video sink to capture frames. */
    QImage m_thumbnail;      /**< Captured thumbnail image. */
    QEventLoop m_loop;       /**< Event loop to block until the frame is captured. */
    int m_timeInMs;          /**< Time in milliseconds to capture the thumbnail. */
};

#endif // VIDEOTHUMBNAILEXTRACTOR_H
