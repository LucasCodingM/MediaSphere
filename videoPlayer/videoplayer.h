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

class VideoPlayer : public QMediaPlayer
{
    Q_OBJECT

public:
    explicit VideoPlayer(QObject *parent = nullptr);
    Q_INVOKABLE void appendVideoPath(const QString &newPath);
    void clearVideosCollections();
    QStringList getVideosCollections() const;
    Q_INVOKABLE void replay();
    Q_INVOKABLE VideoSelectionModel *getVideoSelectionModel();

protected:
    void setupSource();
    void updateDataSelectionModel();
    QImage getThumbnailVideoFromUrl(const QUrl &videoPaths);
private slots:
    // Custom slot to handle the sourceChanged signal
    void onSourceChanged(const QUrl &newSource);

private:
    QSettings m_settings;
    // Creation model's gridView for video selection
    VideoSelectionModel *m_videoSelectionModel;

    VideoThumbNailExtractor m_videoThumbNailExtractor;
};

#endif // VIDEOPLAYER_H
