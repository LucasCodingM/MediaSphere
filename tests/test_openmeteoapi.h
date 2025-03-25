#ifndef TEST_OPENMETEOAPI_H
#define TEST_OPENMETEOAPI_H

#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtTest>

class TestOpenMeteoAPI : public QObject
{
    Q_OBJECT

public:
    // Helper function to create mock reply for network requests
    QNetworkReply *createMockReply(const QString &requestId, const QByteArray &data);

private slots:
    // Test Constructor
    void testConstructor();

    // Test serviceRequestFinished()
    void testServiceRequestFinished();

    // Test addLocationInMapUrlQueryItem
    void testAddLocationInMapUrlQueryItem();
};

#endif // TEST_OPENMETEOAPI_H
