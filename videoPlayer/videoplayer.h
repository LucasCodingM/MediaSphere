#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QAudioOutput>
#include <QDebug>
#include <QMediaPlayer>
#include <QObject>
#include <QSettings>
#include <QUrl>
#include "videoselectionmodel.h"
#include "videothumbnailextractor.h"
#include "videoworker.h"

class VideoPlayer : public QMediaPlayer
{
    Q_OBJECT

public:
    explicit VideoPlayer(QObject *parent = nullptr);

    ~VideoPlayer()
    {
        // Clean up
        m_workerThread->quit();
        m_workerThread->wait();
        delete m_workerThread;
    }

    Q_INVOKABLE void appendVideoPath(const QString &newPath);
    void clearVideosCollections();
    QStringList getVideosCollections() const;
    Q_INVOKABLE void replay();
    Q_INVOKABLE VideoSelectionModel *getVideoSelectionModel();

protected:
    void setupSource();
    QImage getThumbnailVideoFromUrl(const QUrl &videoPaths);
private slots:
    // Custom slot to handle the sourceChanged signal
    void onFetchingDataReady(
        const QUrl &urlVideo,
        QImage &thumbnail); // Slot when the data is ready to be updated in the model

private:
    QSettings m_settings;
    // Creation model's gridView for video selection
    VideoSelectionModel *m_videoSelectionModel;

    VideoThumbNailExtractor m_videoThumbNailExtractor;

    VideoWorker m_videoWorker;
    QThread *m_workerThread;
};

#endif // VIDEOPLAYER_H
