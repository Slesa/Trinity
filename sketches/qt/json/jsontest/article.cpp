#include "article.h"
#include <QJsonArray>

Article::Article()
    : mId(0)
    , mFamily(0)
    , mPrice(0.0)
{
}

Article::Article(int id, const QString &name, int family, double price)
    : mId(id)
    , mName(name)
    , mFamily(family)
    , mPrice(price)
{
}

Article Article::read(const QJsonObject &json)
{
    Article article;
    article.readFrom(json);
    return article;
}

QJsonObject Article::write() const
{
    QJsonObject target;
    writeTo(target);
    return target;
}

void Article::readFrom(const QJsonObject &json)
{
    mId = json["id"].toInt();
    mName = json["name"].toString();
    mFamily = json["family"].toInt();
    mPrice = json["price"].toDouble();
}

void Article::writeTo(QJsonObject &json) const
{
    json["id"] = mId;
    json["name"] = mName;
    json["family"] = mFamily;
    json["price"] = mPrice;
}

Articles Articles::read(const QJsonObject& json)
{
    Articles articles;
    articles.readFrom(json);
    return articles;
}

QJsonObject Articles::write()
{
    QJsonObject target;
    writeTo(target);
    return target;
}

void Articles::readFrom(const QJsonObject& json)
{
    clear();
    QJsonArray list = json["articles"].toArray();
    for(int index=0; index<list.size(); ++index)
    {
        QJsonObject articleObject = list[index].toObject();
        Article article = Article::read(articleObject);
        append(article);
    }
}

void Articles::writeTo(QJsonObject &json)
{
    QJsonArray list;
    foreach(const Article article, *this)
    {
        QJsonObject target = article.write();
        list.append(target);
    }
    json["articles"] = list;
}
