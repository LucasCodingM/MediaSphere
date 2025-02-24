#include "videoplayer.h"

VideoPlayer::VideoPlayer(QObject *parent)
    : QMediaPlayer{parent}
    , m_videoThumbNailExtractor(parent)
    , m_videoSelectionModel(new VideoSelectionModel())
    , m_videoWorker(m_settings, m_videoSelectionModel, m_videoThumbNailExtractor, parent)
{
    m_workerThread = new QThread();
    // Move the worker to the thread
    m_videoWorker.moveToThread(m_workerThread);

    // Connect signals and slots
    connect(m_workerThread, &QThread::started, this, [this]() {
        // Start the append operation
        m_videoWorker.updateDataSelectionModelAsync();
    });

    connect(&m_videoWorker,
            &VideoWorker::fetchingDataReady,
            this,
            &VideoPlayer::onFetchingDataReady);

    //clearVideosCollections();
    // Update media source on the last watched video
    setupSource();
    // Start the worker thread
    m_workerThread->start();
}

void VideoPlayer::setupSource()
{
    m_settings.remove("recentVideosCollections");
    QUrl url;
    if (!m_settings.value("recentVideosCollections").toStringList().empty())
        url = m_settings.value("recentVideosCollections").toStringList().last();
    if (!url.isEmpty())
        this->setSource(url);
}

QImage VideoPlayer::getThumbnailVideoFromUrl(const QUrl &videoPaths)
{
    return m_videoThumbNailExtractor.getVideoThumbnail(videoPaths, 200);
}

void VideoPlayer::appendVideoPath(const QString &newPath)
{
    m_videoWorker.appendVideoPathAsync(newPath);
}

void VideoPlayer::clearVideosCollections()
{
    m_settings.setValue("recentVideosCollections", QStringList());
}

QStringList VideoPlayer::getVideosCollections() const
{
    return m_settings.value("recentVideosCollections").toStringList();
}

void VideoPlayer::replay()
{
    this->setPosition(0);
    this->play();
}

VideoSelectionModel *VideoPlayer::getVideoSelectionModel()
{
    return m_videoSelectionModel;
}

void VideoPlayer::onFetchingDataReady(const QUrl &urlVideo, QImage &thumbnail)
{
    m_videoSelectionModel->addData(urlVideo, thumbnail);
}
