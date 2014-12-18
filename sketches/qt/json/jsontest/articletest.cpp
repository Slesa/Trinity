#include <QString>
#include <QtTest>
#include "article.h"
#include "articletest.h"

void ArticleTest::testArticleJson()
{
    Article article(1, "Menu One", 1, 23.10);
    QJsonObject articleObject = article.write();

    Article compare = Article::read(articleObject);
    QCOMPARE(article.id(), compare.id());
    QCOMPARE(article.name(), compare.name());
    QCOMPARE(article.family(), compare.family());
    QCOMPARE(article.price(), compare.price());
}

void ArticleTest::testArticlesJson()
{
    Articles articles;
    for(int i=0; i<100; ++i)
    {
        articles.append(Article(i, QString("Article %1").arg(i), i+10, 1.11*i));
    }

    QJsonObject json = articles.write();
    Articles compare = Articles::read(json);
    for(int i=0; i<100; ++i)
    {
        Article article = articles[i];
        QCOMPARE(article.id(), i);
        QCOMPARE(article.name(), QString("Article %1").arg(i));
        QCOMPARE(article.family(), i+10);
        QCOMPARE(article.price(), 1.11*i);
    }
}



