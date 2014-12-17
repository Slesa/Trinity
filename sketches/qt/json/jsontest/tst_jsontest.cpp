#include <QString>
#include <QtTest>

class JsonTest : public QObject
{
    Q_OBJECT

public:
    JsonTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testJsonFormat();
};

JsonTest::JsonTest()
{
}

void JsonTest::initTestCase()
{
}

void JsonTest::cleanupTestCase()
{
}

void JsonTest::testJsonFormat()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(JsonTest)

#include "tst_jsontest.moc"
