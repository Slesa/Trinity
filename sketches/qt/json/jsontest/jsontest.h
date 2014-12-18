#ifndef TST_JSONTEST_H
#define TST_JSONTEST_H
#include <QObject>

class JsonTest : public QObject
{
    Q_OBJECT

public:
    JsonTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testArticlesJson();
};


#endif // TST_JSONTEST_H

