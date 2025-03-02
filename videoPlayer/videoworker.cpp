#include "videoworker.h"
#include "shared/global.h"

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
    if (Global::getInstance()->isNewVideoPlayerDataSettings(newPath)) {
        appendInVideosCollections(newPath);
        updateDataInModelAsync();
    }
}

QString VideoWorker::exposeThumbnailToQml(QImage &thumbnail)
{
    QByteArray bArray;
    QBuffer buffer(&bArray);
    buffer.open(QIODevice::WriteOnly);

    // Save the image to the buffer in JPEG format
    thumbnail.save(&buffer, "PNG");

    // Convert the QByteArray to Base64 and prepend the appropriate data URI
    QString image("data:image/png;base64,");
    image.append(QString::fromLatin1(bArray.toBase64().data()));

    return image;
}

void VideoWorker::appendInVideosCollections(QString newPath)
{
    QImage i_thumbnail = m_videoThumbNailExtractor.getVideoThumbnail(QUrl(newPath), 200);
    QString qmlThumbnail = exposeThumbnailToQml(i_thumbnail);
    QFileInfo fileInfo(newPath);
    Global::structVideoPlayerSettings videoPlayerSettings(newPath,
                                                          fileInfo.fileName(),
                                                          qmlThumbnail);
    QList<Global::structVideoPlayerSettings> listVideoPlayerSettings;
    listVideoPlayerSettings.append(videoPlayerSettings);
    Global::getInstance()->appendVideoPlayerSettings(listVideoPlayerSettings);
}

void VideoWorker::keepOnlyValidVideoFiles()
{
    QList<Global::structVideoPlayerSettings> listVideoPlayerSettings
        = Global::getInstance()->retrieveVideoPlayerSettings();
    foreach (auto videoPlayerSettings, listVideoPlayerSettings) {
        QUrl url(videoPlayerSettings.s_videoPath);
        if (!fileExist(url)) {
            Global::getInstance()->removeVideoPathFromSettings(videoPlayerSettings.s_videoPath);
        }
    }
}

bool VideoWorker::fileExist(const QUrl &urlFile)
{
    return QFile::exists(urlFile.toLocalFile());
}

void VideoWorker::updateDataInModelAsync()
{
    keepOnlyValidVideoFiles();
    QList<Global::structVideoPlayerSettings> listVideoPlayerSettings
        = Global::getInstance()->retrieveVideoPlayerSettings();
    foreach (Global::structVideoPlayerSettings videoPlayerSettings, listVideoPlayerSettings) {
        const QUrl urlVideoPaths(videoPlayerSettings.s_videoPath);
        if (!m_videoSelectionModel->getUrlVideoList().contains(urlVideoPaths)) {
            emit fetchingDataReady(videoPlayerSettings);
        }
    }
}
