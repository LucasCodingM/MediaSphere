#include "videothumbnailextractor.h"
#include <QTimer>

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
    connect(m_player,
            &QMediaPlayer::positionChanged,
            this,
            &VideoThumbNailExtractor::onPositionChanged);
}

QImage VideoThumbNailExtractor::getVideoThumbnail(const QUrl &videoUrl, int timeInMilliseconds)
{
    m_timeInMs = timeInMilliseconds;
    // Set the video file and play the media
    m_player->setSource(videoUrl);

    m_player->play();
    m_player->setPosition(timeInMilliseconds); // Set to capture the thumbnail at 1 second (1000 ms)

    // Create and configure the QTimer
    QTimer timer;
    timer.setSingleShot(true); // Ensure the timer triggers only once
    QObject::connect(&timer, &QTimer::timeout, &m_loop, &QEventLoop::quit);

    // Start the timer with a timeout duration (e.g., 5 seconds)
    timer.start(3000);

    m_loop.exec(); // This blocks until the frame is captured

    // Check if the thumbnail was captured
    if (m_thumbnail.isNull()) {
        qWarning("Failed to capture thumbnail within the timeout period.");
    }

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

void VideoThumbNailExtractor::onPositionChanged(qint64 position)
{
    if (position >= m_timeInMs) {
        m_player->stop();
        m_loop.quit();
    }
}
