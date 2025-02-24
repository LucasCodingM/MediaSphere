#ifndef VIDEOWORKER_H
#define VIDEOWORKER_H

#include <QFileInfo>
#include <QObject>
#include <QSettings>
#include <QThread>
#include <QUrl>
#include "videoselectionmodel.h"
#include "videothumbnailextractor.h"

class VideoWorker : public QObject
{
    Q_OBJECT
public:
    explicit VideoWorker(QSettings &settings,
                         VideoSelectionModel *videoSelectionModel,
                         VideoThumbNailExtractor &videoThumbNailExtractor,
                         QObject *parent = nullptr);

    void appendVideoPathAsync(const QString &newPath);
    void appendInVideosCollections(QString newPath);
    void updateDataSelectionModelAsync();
    QString exposeThumbnailToQml(QImage &thumbnail);
signals:
    void fetchingDataReady(const QUrl &urlVideo, QString &thumbnail);

private:
    QSettings &m_settings;
    VideoSelectionModel *m_videoSelectionModel;
    VideoThumbNailExtractor m_videoThumbNailExtractor;
};

#endif // VIDEOWORKER_H
