#include <QCoreApplication>
#include <QTextCodec>
#include <QtTest>
#include "jsontest.h"
#include "articletest.h"
#include "familytest.h"

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    bool success = true;

    ArticleTest articleSuite;
    success |= QTest::qExec(&articleSuite, argc, argv);

    FamilyTest familySuite;
    success |= QTest::qExec(&familySuite, argc, argv);

    JsonTest jsonSuite;
    success |= QTest::qExec(&jsonSuite, argc, argv);

    return success;
}
