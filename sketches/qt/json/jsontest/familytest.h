#ifndef FAMILYTEST_H
#define FAMILYTEST_H
#include <QObject>


class FamilyTest : public QObject
{
    Q_OBJECT

private slots:
    void testFamilyJson();
};

#endif // FAMILYTEST_H
