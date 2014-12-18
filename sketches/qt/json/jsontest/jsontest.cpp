#include <QString>
#include <QtTest>
#include "article.h"
#include "jsontest.h"

JsonTest::JsonTest()
{
}

void JsonTest::initTestCase()
{
}

void JsonTest::cleanupTestCase()
{
}

void JsonTest::testArticlesJson()
{
    Article article(1, "Menu One", 1, 23.10);
    QJsonObject articleObject = article.write();

    Article compare = Article::read(articleObject);
    QCOMPARE(article.id(), compare.id());
    QCOMPARE(article.name(), compare.name());
    QCOMPARE(article.family(), compare.family());
    QCOMPARE(article.price(), compare.price());
}

// #include "tst_jsontest.moc"
