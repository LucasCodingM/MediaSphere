#include "videoplayer.h"

VideoPlayer::VideoPlayer(QObject *parent)
    : QMediaPlayer{parent}
    , m_videoThumbNailExtractor(parent)
{
    // Connect the sourceChanged signal to a custom slot
    //clearVideosCollections();
    connect(this, &QMediaPlayer::sourceChanged, this, &VideoPlayer::onSourceChanged);
    setupSource();
    m_videoSelectionModel = new VideoSelectionModel();
    updateDataSelectionModel();
}

void VideoPlayer::setupSource()
{
    QUrl url;
    if (!m_settings.value("recentVideosCollections").toStringList().empty())
        url = m_settings.value("recentVideosCollections").toStringList().last();
    if (!url.isEmpty())
        this->setSource(url);
}

void VideoPlayer::updateDataSelectionModel()
{
    foreach (QString videoPaths, getVideosCollections()) {
        const QUrl urlVideoPaths(videoPaths);
        if (!m_videoSelectionModel->getUrlVideoList().contains(urlVideoPaths)) {
            QImage thumbnail = getThumbnailVideoFromUrl(urlVideoPaths);
            m_videoSelectionModel->addData(urlVideoPaths, thumbnail);
        }
    }
}

QImage VideoPlayer::getThumbnailVideoFromUrl(const QUrl &videoPaths)
{
    return m_videoThumbNailExtractor.getVideoThumbnail(videoPaths, 200);
}

void VideoPlayer::appendVideoPath(const QString &newPath)
{
    // Load the current list of video paths from QSettings
    QStringList videoPaths = getVideosCollections();

    // Append the new path to the list (if it's not already in the list)
    if (!videoPaths.contains(newPath)) {
        videoPaths.append(newPath);
    }

    // Save the updated list back to QSettings
    m_settings.setValue("recentVideosCollections", videoPaths);

    updateDataSelectionModel();

    // For debugging purposes, print the updated list
    qDebug() << "Updated video paths:" << videoPaths;
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

void VideoPlayer::onSourceChanged(const QUrl &newSource)
{

}
