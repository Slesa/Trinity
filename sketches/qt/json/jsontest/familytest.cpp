#include <QString>
#include <QTest>
#include "family.h"
#include "familytest.h"

void FamilyTest::testFamilyJson()
{
    Family family(1, "Dishes", 1);
    QJsonObject familyObject;
    family.write(familyObject);

    Family compare;
    compare.read(familyObject);
    QCOMPARE(family.id(), compare.id());
    QCOMPARE(family.name(), compare.name());
    QCOMPARE(family.familyGroup(), compare.familyGroup());
}
