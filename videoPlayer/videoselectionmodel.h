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
        UrlVideoRole = Qt::UserRole + 1,
        Thumbnail = Qt::UserRole + 2,
        NameVideoRole = Qt::UserRole + 3,
    };

    explicit VideoSelectionModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void addData(const QString &videoPath, const QString &videoName, const QString &thumbnail);
    QList<QUrl> getUrlVideoList() { return m_listUrlVideo; }

private:
    QList<QUrl> m_listUrlVideo;
    QList<QString> m_listNameVideo;
    QList<QString> m_listThumbnail;
};

#endif // VIDEOSELECTIONMODEL_H
