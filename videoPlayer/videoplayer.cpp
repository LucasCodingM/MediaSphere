#include "videoplayer.h"

VideoPlayer::VideoPlayer(QObject *parent)
    : QMediaPlayer{parent}
{
    // Connect the sourceChanged signal to a custom slot
    connect(this, &QMediaPlayer::sourceChanged, this, &VideoPlayer::onSourceChanged);
    setupSource();
}

void VideoPlayer::setupSource()
{
    QUrl url;
    if (!m_settings.value("recentVideosCollections").toStringList().empty())
        url = m_settings.value("recentVideosCollections").toStringList().last();
    this->setSource(url);
}

void VideoPlayer::appendVideoPath(const QString &newPath)
{
    // Load the current list of video paths from QSettings
    QStringList videoPaths = m_settings.value("recentVideosCollections").toStringList();

    // Append the new path to the list (if it's not already in the list)
    if (!videoPaths.contains(newPath)) {
        videoPaths.append(newPath);
    }

    // Save the updated list back to QSettings
    m_settings.setValue("recentVideosCollections", videoPaths);

    // For debugging purposes, print the updated list
    qDebug() << "Updated video paths:" << videoPaths;
}

void VideoPlayer::clearVideosCollections()
{
    m_settings.value("recentVideosCollections").clear();
}

void VideoPlayer::replay()
{
    this->setPosition(0);
    this->play();
}

void VideoPlayer::onSourceChanged(const QUrl &newSource)
{
    appendVideoPath(newSource.toString());
}
