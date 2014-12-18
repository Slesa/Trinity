#include <QString>
#include <QtTest>
#include "article.h"
#include "articletest.h"

void ArticleTest::testArticleJson()
{
    Article article(1, "Menu One", 1, 23.10);
    QJsonObject articleObject;
    article.write(articleObject);

    Article compare;
    compare.read(articleObject);
    QCOMPARE(article.id(), compare.id());
    QCOMPARE(article.name(), compare.name());
    QCOMPARE(article.family(), compare.family());
    QCOMPARE(article.price(), compare.price());
}


// #include "tst_article.moc"


