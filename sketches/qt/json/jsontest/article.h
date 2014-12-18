#ifndef ARTICLE_H
#define ARTICLE_H

#include <QJsonObject>
#include <QString>

class Article
{
public:
    Article();
    Article(int id, const QString& name, int family, double price);

    int id() const { return mId; }
    void setId(int id) { mId = id; }

    QString name() const { return mName;}
    void setName(const QString& name) { mName = name; }

    int family() const { return mFamily; }
    void setFamily(int family) { mFamily = family; }

    double price() const { return mPrice; }
    void setPrice(double price) { mPrice = price; }

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;

private:
    int mId;
    QString mName;
    int mFamily;
    double mPrice;
};

#endif // ARTICLE_H
