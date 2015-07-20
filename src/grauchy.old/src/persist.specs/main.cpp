#include <QCoreApplication>
#include <QtTest>
#include "persist.specs.h"

int main(int argc, char** argv) 
{
    QCoreApplication app(argc, argv);

    bool success = true;

    PersistSpecs persistSpecs;
    success |= QTest::qExec(&persistSpecs, argc, argv);

    return success;
}
