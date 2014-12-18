#ifndef ARTICLE_H
#define ARTICLE_H

#include <QJsonObject>
#include <QString>
#include <QList>

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

    static Article read(const QJsonObject &json);
    QJsonObject write() const;

private:
    void readFrom(const QJsonObject& json);
    void writeTo(QJsonObject& json) const;

private:
    int mId;
    QString mName;
    int mFamily;
    double mPrice;
};

class Articles : public QList<Article>
{
public:
    static Articles read(const QJsonObject& json);
    QJsonObject write();

private:
    void readFrom(const QJsonObject& json);
    void writeTo(QJsonObject& json);
};

#endif // ARTICLE_H
