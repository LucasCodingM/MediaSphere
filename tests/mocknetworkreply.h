#ifndef MOCKNETWORKREPLY_H
#define MOCKNETWORKREPLY_H

#include <QNetworkReply>

class MockNetworkReply : public QNetworkReply
{
    Q_OBJECT

public:
    MockNetworkReply(QObject *parent = 0);
    ~MockNetworkReply();

    void setHttpStatusCode(int code, const QByteArray &statusText = QByteArray());
    void setHeader(QNetworkRequest::KnownHeaders header, const QVariant &value);
    void setContentType(const QByteArray &contentType);

    void setContent(const QString &content);
    void setContent(const QByteArray &content);

    void abort();
    qint64 bytesAvailable() const;
    bool isSequential() const;

    void setRequestId(const QString &requestId);

    QString requestId() const;

protected:
    qint64 readData(char *data, qint64 maxSize);

private:
    struct MockNetworkReplyPrivate *d;
};

#endif // MOCKNETWORKREPLY_H
