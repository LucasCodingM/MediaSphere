#ifndef VIDEOSELECTIONMODEL_H
#define VIDEOSELECTIONMODEL_H

/**
 * @file VideoSelectionModel.h
 * @brief Manage the video media model data
 */

#include <QAbstractListModel>
#include <QBuffer>
#include <QList>
#include <QPixmap>
#include <QUrl>

/**
 * @class VideoSelectionModel
 * @brief A model to manage a list of video items with URLs, names, and thumbnails.
 *
 * This class extends QAbstractListModel to provide a data model for video items.
 * Each video item has a URL, a name, and a thumbnail. The model supports adding
 * new video items and retrieving data for each item based on its role.
 */
class VideoSelectionModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Role {
        UrlVideoRole = Qt::UserRole + 1,
        Thumbnail = Qt::UserRole + 2,
        NameVideoRole = Qt::UserRole + 3,
    };

    /**
     * @brief Constructor for VideoSelectionModel.
     *
     * Initializes the model with an optional parent object.
     *
     * @param parent The parent object.
     */
    explicit VideoSelectionModel(QObject *parent = nullptr);
    /**
     * @brief Returns the number of rows in the model.
     *
     * This method returns the count of video items in the model.
     *
     * @param parent The parent model index (unused).
     * @return The number of video items.
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    /**
     * @brief Returns the data for a given role and index.
     *
     * This method retrieves the data for a video item based on the specified role.
     * Supported roles include UrlVideoRole, Thumbnail, and NameVideoRole.
     *
     * @param index The model index.
     * @param role The data role.
     * @return The data for the specified role and index.
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    /**
     * @brief Returns the role names for the model.
     *
     * This method maps the role names to their respective keys.
     *
     * @return A hash of role names.
     */
    QHash<int, QByteArray> roleNames() const override;

    /**
     * @brief Adds a new video item to the model.
     *
     * This method appends a new video item with the specified URL, name, and thumbnail.
     *
     * @param videoPath The URL of the video.
     * @param videoName The name of the video.
     * @param thumbnail The thumbnail of the video.
     */
    void addData(const QString &videoPath, const QString &videoName, const QString &thumbnail);
    QList<QUrl> getUrlVideoList() { return m_listUrlVideo; }

    void removeData(int row);

    void removeDataByVideoPath(const QString &videoPath);

private:
    QList<QUrl> m_listUrlVideo;     /**< List of video URLs. */
    QList<QString> m_listNameVideo; /**< List of video names. */
    QList<QString> m_listThumbnail; /**< List of video thumbnails. */
};

#endif // VIDEOSELECTIONMODEL_H
