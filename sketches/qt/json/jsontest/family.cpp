#include "family.h"

Family::Family()
{
}

Family::Family(int id, const QString& name, int familyGroup)
    : mId(id)
    , mName(name)
    , mFamilyGroup(familyGroup)
{
}

void Family::read(const QJsonObject& json)
{
    mId = json["id"].toInt();
    mName = json["name"].toString();
    mFamilyGroup = json["familygroup"].toInt();
}

void Family::write(QJsonObject &json) const
{
    json["id"] = mId;
    json["name"] = mName;
    json["familygroup"] = mFamilyGroup;
}
