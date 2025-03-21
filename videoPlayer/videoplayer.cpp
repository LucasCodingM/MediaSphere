#include "videoplayer.h"

VideoPlayer::VideoPlayer(QObject *parent)
    : QMediaPlayer{parent}
    , m_videoThumbNailExtractor(parent)
    , m_videoSelectionModel(new VideoSelectionModel())
    , m_videoWorker(m_settings, m_videoSelectionModel, m_videoThumbNailExtractor, parent)
{
    //Global::getInstance()->clearAllSettings();
    m_workerThread = new QThread();
    // Move the worker to the thread
    m_videoWorker.moveToThread(m_workerThread);

    // Connect signals and slots
    connect(m_workerThread, &QThread::started, this, [this]() {
        // Start the append operation
        m_videoWorker.updateDataInModelAsync();
    });

    connect(&m_videoWorker,
            &VideoWorker::fetchingDataReady,
            this,
            &VideoPlayer::onFetchingDataReady);

    //clearVideosCollections();
    // Update media source on the last watched video
    setupToLastValidSource();
    // Start the worker thread
    m_workerThread->start();
}

VideoPlayer::~VideoPlayer()
{
    // Clean up
    m_workerThread->quit();
    m_workerThread->wait();
    delete m_workerThread;
}

void VideoPlayer::setupToLastValidSource()
{
    QUrl url;
    if (!Global::getInstance()->retrieveVideoPlayerSettings().empty())
        url = Global::getInstance()->retrieveVideoPlayerSettings().last().s_videoPath;
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

void VideoPlayer::replay()
{
    this->setPosition(0);
    this->play();
}

bool VideoPlayer::sourceIsValid()
{
    return m_videoWorker.fileExist(this->source());
}

VideoSelectionModel *VideoPlayer::getVideoSelectionModel()
{
    return m_videoSelectionModel;
}

void VideoPlayer::deleteVideo(const QString &videoPath)
{
    // m_videoWorker.deleteVideo(videoPath);
    Global::getInstance()->removeVideoPathFromSettings(videoPath);
    m_videoSelectionModel->removeDataByVideoPath(videoPath);
}

void VideoPlayer::onFetchingDataReady(const Global::structVideoPlayerSettings &videoPlayerSettings)
{
    m_videoSelectionModel->addData(videoPlayerSettings.s_videoPath,
                                   videoPlayerSettings.s_videoName,
                                   videoPlayerSettings.s_thumbnail);
}
