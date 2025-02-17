#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QAudioOutput>
#include <QDebug>
#include <QMediaPlayer>
#include <QObject>
#include <QSettings>
#include <QUrl>

class VideoPlayer : public QMediaPlayer
{
    Q_OBJECT

public:
    explicit VideoPlayer(QObject *parent = nullptr);
    void appendVideoPath(const QString &newPath);
    void clearVideosCollections();
    Q_INVOKABLE void replay();

protected:
    void setupSource();
private slots:
    // Custom slot to handle the sourceChanged signal
    void onSourceChanged(const QUrl &newSource);

private:
    QSettings m_settings;
};

#endif // VIDEOPLAYER_H
