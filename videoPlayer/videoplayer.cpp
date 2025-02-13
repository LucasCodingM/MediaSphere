#include "videoplayer.h"

videoPlayer::videoPlayer(QObject *parent)
    : QObject{parent}
    , m_mediaPlayer(new QMediaPlayer(this))
    , m_audioOutput(new QAudioOutput(this))
    , m_isPlaying(false)
    , m_isPaused(false)
    , m_isStopped(false)
{
    m_mediaPlayer->setAudioOutput(m_audioOutput);
    connect(m_mediaPlayer,
            &QMediaPlayer::playbackStateChanged,
            this,
            [this](QMediaPlayer::PlaybackState newState) {
                m_isPlaying = false;
                m_isPaused = false;
                m_isStopped = false;
                if (newState == QMediaPlayer::PlaybackState::PlayingState)
                    m_isPlaying = true;
                else if (newState == QMediaPlayer::PlaybackState::PausedState)
                    m_isPaused = true;
                else if (newState == QMediaPlayer::PlaybackState::StoppedState)
                    m_isStopped = true;
                emit isPlayingChanged();
                emit isPausedChanged();
                emit isStoppedChanged();
            });
}

void videoPlayer::setVideoOutput(QObject *objVideoOutput)
{
    m_mediaPlayer->setVideoOutput(objVideoOutput);
}

QObject *videoPlayer::videoOutput()
{
    return m_mediaPlayer->videoOutput();
}

QString videoPlayer::videoUrl() const
{
    return m_videoUrl;
}

void videoPlayer::setVideoUrl(const QString &url)
{
    if (m_videoUrl != url) {
        m_videoUrl = url;
        emit videoUrlChanged();
        m_mediaPlayer->setSource(QUrl::fromLocalFile(m_videoUrl));
    }
}

bool videoPlayer::isPlaying() const
{
    return m_isPlaying;
}

bool videoPlayer::isPaused() const
{
    return m_isPaused;
}

bool videoPlayer::isStopped() const
{
    return m_isStopped;
}

void videoPlayer::play()
{
    if (m_mediaPlayer->playbackState() != QMediaPlayer::PlayingState) {
        m_mediaPlayer->play();
    }
}

void videoPlayer::pause()
{
    if (m_mediaPlayer->playbackState() == QMediaPlayer::PlayingState) {
        m_mediaPlayer->pause();
    }
}

void videoPlayer::stop()
{
    m_mediaPlayer->stop();
}

void videoPlayer::setVolume(float volume)
{
    m_audioOutput->setVolume(volume);
}

void videoPlayer::setMute(bool mute)
{
    m_audioOutput->setMuted(mute);
}
