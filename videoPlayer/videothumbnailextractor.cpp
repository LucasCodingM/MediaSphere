#include "videothumbnailextractor.h"

VideoThumbNailExtractor::VideoThumbNailExtractor(QObject *parent)
    : QObject{parent}
{
    // Create the media player and video sink (to capture frames)
    m_player = new QMediaPlayer(this);
    m_videoSink = new QVideoSink(this);
    m_player->setVideoSink(m_videoSink);

    // Connect the video sink frame signal to capture the frame
    connect(m_videoSink,
            &QVideoSink::videoFrameChanged,
            this,
            &VideoThumbNailExtractor::onVideoFrameChanged);
}

QImage VideoThumbNailExtractor::getVideoThumbnail(const QUrl &videoUrl, int timeInMilliseconds)
{
    m_timeInMs = timeInMilliseconds;
    // Set the video file and play the media
    m_player->setSource(videoUrl);

    // Set the position to capture the thumbnail at the given time (e.g., 1000 ms)
    m_player->play();
    m_player->setPosition(timeInMilliseconds); // Set to capture the thumbnail at 1 second (1000 ms)

    // Wait for the video frame to be captured
    QEventLoop loop;
    connect(m_player, &QMediaPlayer::positionChanged, this, [this, &loop, timeInMilliseconds]() {
        if (m_player->position() >= timeInMilliseconds) {
            // Stop the player once we reach the desired position
            m_player->stop();

            // Exit the event loop
            loop.quit();
        }
    });
    loop.exec(); // This blocks until the frame is captured

    // Return the captured thumbnail image
    return m_thumbnail;
}

void VideoThumbNailExtractor::onVideoFrameChanged(const QVideoFrame &frame)
{
    // Check if the frame is valid
    if (frame.isValid()) {
        // Convert the frame to QImage
        m_thumbnail = frame.toImage();
        return;
    }
}
