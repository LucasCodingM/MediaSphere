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

    QImage getVideoThumbnail(const QUrl &videoUrl, int timeInMilliseconds = 1000);

private slots:
    void onVideoFrameChanged(const QVideoFrame &frame);

private:
    QMediaPlayer *m_player;
    QVideoSink *m_videoSink;
    QImage m_thumbnail;
    int m_timeInMs;
};

#endif // VIDEOTHUMBNAILEXTRACTOR_H
