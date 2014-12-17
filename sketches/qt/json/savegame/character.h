#ifndef CHARACTER_H
#define CHARACTER_H

#include <QJsonObject>
#include <QString>

class Character
{
public:
    enum ClassType {
        Warrior, Mage, Archer
    };

    Character();
    Character(const QString& name, int level, ClassType classType);

    QString name() const { return mName; }
    void setName(const QString& name) { mName = name; }

    int level() const { return mLevel; }
    void setLevel(int level) { mLevel = level; }

    ClassType classType() const { return mClassType; }
    void setClassType(ClassType classType) { mClassType = classType; }

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;

private:
    QString mName;
    int mLevel;
    ClassType mClassType;
};

#endif // CHARACTER_H
