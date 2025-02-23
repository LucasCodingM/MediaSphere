#include "videoworker.h"

VideoWorker::VideoWorker(QSettings &settings,
                         VideoSelectionModel *videoSelectionModel,
                         VideoThumbNailExtractor &videoThumbNailExtractor,
                         QObject *parent)
    : QObject{parent}
    , m_settings(settings)
    , m_videoSelectionModel(videoSelectionModel)
    , m_videoThumbNailExtractor(&videoThumbNailExtractor)
{}

void VideoWorker::appendVideoPathAsync(const QString &newPath)
{
    appendInVideosCollections(newPath);
    updateDataSelectionModelAsync();
}

QStringList VideoWorker::getVideosCollections()
{
    // Retrieve the current video paths from QSettings
    return m_settings.value("recentVideosCollections").toStringList();
}

void VideoWorker::appendInVideosCollections(QString newPath)
{
    QStringList videosCollections = getVideosCollections();
    // Append the new path to the list (if it's not already in the list)
    if (!videosCollections.contains(newPath)) {
        videosCollections.append(newPath);
    }
    // Save the updated list back to QSettings
    m_settings.setValue("recentVideosCollections", videosCollections);
}

void VideoWorker::updateDataSelectionModelAsync()
{
    foreach (QString videoPaths, getVideosCollections()) {
        const QUrl urlVideoPaths(videoPaths);
        if (!m_videoSelectionModel->getUrlVideoList().contains(urlVideoPaths)) {
            QImage thumbnail = m_videoThumbNailExtractor.getVideoThumbnail(urlVideoPaths, 200);
            emit fetchingDataReady(urlVideoPaths, thumbnail);
        }
    }
}
