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

void VideoSelectionModel::addData(const QUrl &urlVideo, QImage &thumbnail)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_urlVideo.append(urlVideo); // Add the thumbnail to the list
    m_thumbnail.append(exposeThumbnailToQml(thumbnail));
    endInsertRows();
}

QString VideoSelectionModel::exposeThumbnailToQml(QImage &thumbnail)
{
    // // Load an image, for example:
    // if (urlVideo.isLocalFile())
    //     thumbnail.load(urlVideo.toString()); // Replace with your actual image path or resource
    // else
    //     thumbnail.load(urlVideo.toLocalFile()); // Replace with your actual image path or resource

    // if (thumbnail.isNull())
    //     qWarning() << "Impossible de charger " << urlVideo.toLocalFile();

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
