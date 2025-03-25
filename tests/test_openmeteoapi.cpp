#include "test_openmeteoapi.h"
#include "mocknetworkreply.h"
#include "weather/openmeteoapi.h"

QNetworkReply *TestOpenMeteoAPI::createMockReply(const QString &requestId, const QByteArray &data)
{
    MockNetworkReply *reply = new MockNetworkReply();
    reply->setContent(data);
    reply->setRequestId(requestId);
    return reply;
}

void TestOpenMeteoAPI::testConstructor()
{
    openMeteoAPI api;
    QVERIFY(api.getIsDataAvailable() == false);
}

void TestOpenMeteoAPI::testServiceRequestFinished()
{
    openMeteoAPI api;
    // Create a mock reply with valid data
    QFile replyData(":/forecast.json");
    // Check if the file is openable
    if (!replyData.open(QIODevice::ReadOnly)) {
        qCritical() << "Could not open the file forecast.json";
        return;
    }

    QByteArray infoWeatherByteArray = replyData.readAll();
    QNetworkReply *mockReply = createMockReply("infoWeather", infoWeatherByteArray);

    api.serviceRequestFinished(mockReply);

    QVERIFY(api.getIsDataAvailable() == true);
    QVERIFY(!api.getListDailyWeatherData().isEmpty());
}

void TestOpenMeteoAPI::testAddLocationInMapUrlQueryItem()
{
    openMeteoAPI api;

    api.addLocationInMapUrlQueryItem("50.123", "3.456");
    QMap<QString, QString> map = api.getUrlQueryItem();

    QCOMPARE(map["latitude"], QString("50.123"));
    QCOMPARE(map["longitude"], QString("3.456"));
}

QTEST_MAIN(TestOpenMeteoAPI)
#include "test_openmeteoapi.moc"
