#include <QString>
#include <QtTest>

class TestQString : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void toUpper_data();
    void toUpper();
};

void TestQString::toUpper_data()
{
    QTest::addColumn<QString>("string");
    QTest::addColumn<QString>("result");

    QTest::newRow("all lower") << "hello" << "HELLO";
    QTest::newRow("midex") << "Hello" << "HELLO";
    QTest::newRow("all upper") << "HELLO" << "HELLO";
}

void TestQString::toUpper()
{
    QFETCH(QString, string);
    QFETCH(QString, result);

    QCOMPARE(string.toUpper(), result);
}

QTEST_APPLESS_MAIN(TestQString)
#include "testqstring.moc"
