#include "article.h"

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

void Article::read(const QJsonObject &json)
{
    mId = json["id"].toInt();
    mName = json["name"].toString();
    mFamily = json["family"].toInt();
    mPrice = json["price"].toDouble();
}

void Article::write(QJsonObject &json) const
{
    json["id"] = mId;
    json["name"] = mName;
    json["family"] = mFamily;
    json["price"] = mPrice;
}
