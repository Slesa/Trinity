#include "maincontroller.h"

MainController::MainController(QObject *parent)
    : QObject(parent)
{
    setProperty( tr("Hello world") );
    changeAttribute( tr("English") );
}

