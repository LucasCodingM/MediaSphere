#ifndef VIDEOSELECTIONMODEL_H
#define VIDEOSELECTIONMODEL_H

#include <QAbstractListModel>
#include <QBuffer>
#include <QList>
#include <QPixmap>
#include <QUrl>

class VideoSelectionModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Role {
        UrlVideoRole = Qt::UserRole + 1, // Change to represent the urlVideo
        Thumbnail = Qt::UserRole + 2
    };

    explicit VideoSelectionModel(QObject *parent = nullptr);
    // Overriding necessary QAbstractListModel methods
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    // Method to add data to the model (in this case, url video)
    void addData(const QUrl &urlVideo, QImage &thumbnail); // Store a QUrl for each video
    QList<QUrl> getUrlVideoList() { return m_urlVideo; }
    QString exposeThumbnailToQml(QImage &thumbnail);

private:
    QList<QUrl> m_urlVideo; // Store the video url
    QList<QString> m_thumbnail; //Store the pixmap
};

#endif // VIDEOSELECTIONMODEL_H
