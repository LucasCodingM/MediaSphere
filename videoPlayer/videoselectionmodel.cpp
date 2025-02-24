#include "videoselectionmodel.h"

VideoSelectionModel::VideoSelectionModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int VideoSelectionModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_urlVideo.count();
}

QVariant VideoSelectionModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == UrlVideoRole) {
        return m_urlVideo.at(index.row()); // Return the url video
    } else if (role == Thumbnail) {
        return m_thumbnail.at(index.row());
    }

    return QVariant();
}

QHash<int, QByteArray> VideoSelectionModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[UrlVideoRole] = "urlVideo"; // Map the role to "urlVideo"
    roles[Thumbnail] = "thumbnail";   // Map the role to "urlVideo"
    return roles;
}

void VideoSelectionModel::addData(const QUrl &urlVideo, QString &thumbnail)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_urlVideo.append(urlVideo); // Add the thumbnail to the list
    m_thumbnail.append(thumbnail);
    endInsertRows();
}
