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
        return m_listThumbnail.at(index.row()); // Return the thumbnail video
    } else if (role == NameVideoRole) {
        return m_listNameVideo.at(index.row()); // Return the name video
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

void VideoSelectionModel::removeData(int row)
{
    if (row == -1) {
        qWarning() << "Row number is not valid";
        return;
    }
    // Notify the model that a row is about to be removed
    beginRemoveRows(QModelIndex(), row, row);

    // Remove the data from the internal lists
    m_listUrlVideo.removeAt(row);
    m_listNameVideo.removeAt(row);
    m_listThumbnail.removeAt(row);

    // Notify the model that the row has been removed
    endRemoveRows();
}

void VideoSelectionModel::removeDataByVideoPath(const QString &videoPath)
{
    // Find the row index corresponding to the videoPath
    int row = -1;
    for (int i = 0; i < m_listUrlVideo.size(); ++i) {
        if (m_listUrlVideo[i].toString() == videoPath) {
            row = i;
            break;
        }
    }
    removeData(row);
}
