#ifndef TST_ARTICLE_H
#define TST_ARTICLE_H
#include <QObject>

class ArticleTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void testArticleJson();
};

#endif // TST_ARTICLE_H

