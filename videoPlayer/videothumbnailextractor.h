#ifndef VIDEOTHUMBNAILEXTRACTOR_H
#define VIDEOTHUMBNAILEXTRACTOR_H

#include <QBuffer>
#include <QDebug>
#include <QEventLoop>
#include <QImage>
#include <QMediaPlayer>
#include <QObject>
#include <QVideoFrame>
#include <QVideoSink>

class VideoThumbNailExtractor : public QObject
{
    Q_OBJECT
public:
    explicit VideoThumbNailExtractor(QObject *parent = nullptr);

    ~VideoThumbNailExtractor()
    {
        if (m_loop.isRunning()) {
            m_loop.quit();
        }
    }

    QImage getVideoThumbnail(const QUrl &videoUrl, int timeInMilliseconds = 1000);

private slots:
    void onVideoFrameChanged(const QVideoFrame &frame);
    void onPositionChanged(qint64 position);

private:
    QMediaPlayer *m_player;
    QVideoSink *m_videoSink;
    QImage m_thumbnail;
    QEventLoop m_loop;
    int m_timeInMs;
};

#endif // VIDEOTHUMBNAILEXTRACTOR_H
