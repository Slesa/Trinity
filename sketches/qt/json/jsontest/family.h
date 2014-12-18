#ifndef FAMILY_H
#define FAMILY_H

#include <QJsonObject>
#include <QString>

class Family
{
public:
    Family();
    Family(int id, const QString& name, int familyGroup);

    int id() const { return mId; }
    void setId(int id) { mId = id; }

    QString name() const { return mName; }
    void setName(const QString& name) { mName = name; }

    int familyGroup() const { return mFamilyGroup; }
    void setFamilyGroup(int familyGroup) { mFamilyGroup = familyGroup; }

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;

private:
    int mId;
    QString mName;
    int mFamilyGroup;
};

#endif // FAMILY_H
