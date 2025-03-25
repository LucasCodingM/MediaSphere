#include "mocknetworkreply.h"
#include <QBuffer>
#include <QNetworkAccessManager>
#include <QTimer>

struct MockNetworkReplyPrivate
{
    QByteArray content;
    qint64 offset;
};

MockNetworkReply::MockNetworkReply(QObject *parent)
    : QNetworkReply{parent}
{
    d = new MockNetworkReplyPrivate;
}

MockNetworkReply::~MockNetworkReply()
{
    delete d;
}

void MockNetworkReply::setHttpStatusCode(int code, const QByteArray &statusText)
{
    setAttribute(QNetworkRequest::HttpStatusCodeAttribute, code);
    if (statusText.isNull())
        return;

    setAttribute(QNetworkRequest::HttpReasonPhraseAttribute, statusText);
}

void MockNetworkReply::setHeader(QNetworkRequest::KnownHeaders header, const QVariant &value)
{
    QNetworkReply::setHeader(header, value);
}

void MockNetworkReply::setContentType(const QByteArray &contentType)
{
    setHeader(QNetworkRequest::ContentTypeHeader, contentType);
}

void MockNetworkReply::setContent(const QString &content)
{
    setContent(content.toUtf8());
}

void MockNetworkReply::setContent(const QByteArray &content)
{
    d->content = content;
    d->offset = 0;

    open(ReadOnly | Unbuffered);
    setHeader(QNetworkRequest::ContentLengthHeader, QVariant(content.size()));

    QTimer::singleShot(0, this, SIGNAL(readyRead()));
    QTimer::singleShot(0, this, SIGNAL(finished()));
}

void MockNetworkReply::abort()
{
    // NOOP
}

qint64 MockNetworkReply::bytesAvailable() const
{
    return d->content.size() - d->offset + QIODevice::bytesAvailable();
}

bool MockNetworkReply::isSequential() const
{
    return true;
}

qint64 MockNetworkReply::readData(char *data, qint64 maxSize)
{
    if (d->offset >= d->content.size())
        return -1;

    qint64 number = qMin(maxSize, d->content.size() - d->offset);
    memcpy(data, d->content.constData() + d->offset, number);
    d->offset += number;

    return number;
}

// Set the requestId for this reply
void MockNetworkReply::setRequestId(const QString &requestId)
{
    QNetworkRequest networkRequest;
    networkRequest.setAttribute(QNetworkRequest::User, requestId);
    setRequest(networkRequest);
}

// Retrieve the requestId from this reply
QString MockNetworkReply::requestId() const
{
    return attribute(QNetworkRequest::User).toString();
}
