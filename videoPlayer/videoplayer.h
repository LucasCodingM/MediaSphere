#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QAudioOutput>
#include <QDebug>
#include <QMediaPlayer>
#include <QObject>
#include <QUrl>

class videoPlayer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString videoUrl READ videoUrl WRITE setVideoUrl NOTIFY videoUrlChanged)
    Q_PROPERTY(bool isPlaying READ isPlaying NOTIFY isPlayingChanged)
    Q_PROPERTY(bool isPaused READ isPaused NOTIFY isPausedChanged)
    Q_PROPERTY(bool isStopped READ isStopped NOTIFY isStoppedChanged)
    Q_PROPERTY(QObject *videoOutput READ videoOutput WRITE setVideoOutput NOTIFY videoOutputChanged)
public:
    explicit videoPlayer(QObject *parent = nullptr);

    QString videoUrl() const;
    void setVideoUrl(const QString &url);
    QObject *videoOutput();
    void setVideoOutput(QObject *objVideoOutput);

    bool isPlaying() const;
    bool isPaused() const;
    bool isStopped() const;
public slots:
    void play();
    void pause();
    void stop();
    void setVolume(float volume);
    void setMute(bool mute);

signals:
    void videoUrlChanged();
    void isPlayingChanged();
    void isPausedChanged();
    void isStoppedChanged();
    void videoOutputChanged();

private:
    QMediaPlayer *m_mediaPlayer;
    QAudioOutput *m_audioOutput;
    QString m_videoUrl;
    bool m_isPlaying;
    bool m_isPaused;
    bool m_isStopped;
};

#endif // VIDEOPLAYER_H
