#include <QString>
#include <QtTest>

class TestQString : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testToUpper();
};

void TestQString::testToUpper()
{
    QString str = "Hello";
    QCOMPARE(str.toUpper(), QString("HELLO"));
}

QTEST_APPLESS_MAIN(TestQString)
#include "testqstring.moc"
