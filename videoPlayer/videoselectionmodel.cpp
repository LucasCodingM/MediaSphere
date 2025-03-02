#include "videoselectionmodel.h"

VideoSelectionModel::VideoSelectionModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int VideoSelectionModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_listUrlVideo.count();
}

QVariant VideoSelectionModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == UrlVideoRole) {
        return m_listUrlVideo.at(index.row()); // Return the url video
    } else if (role == Thumbnail) {
        return m_listThumbnail.at(index.row());
    } else if (role == NameVideoRole) {
        return m_listNameVideo.at(index.row());
    }

    return QVariant();
}

QHash<int, QByteArray> VideoSelectionModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[UrlVideoRole] = "videoUrl";   // Map the role to "videoUrl"
    roles[Thumbnail] = "thumbnail";     // Map the role to "thumbnail"
    roles[NameVideoRole] = "videoName"; // Map the role to "videoName"
    return roles;
}

void VideoSelectionModel::addData(const QString &videoPath,
                                  const QString &videoName,
                                  const QString &thumbnail)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_listUrlVideo.append(QUrl(videoPath));
    m_listNameVideo.append(videoName);
    m_listThumbnail.append(thumbnail);
    endInsertRows();
}
