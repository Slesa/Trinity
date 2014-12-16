#include "trafficlight.h"
#include "trafficlightwidget.h"
#include <QVBoxLayout>
#include <QStateMachine>
#include <QTimer>
#include <QFinalState>

QState* createLightState(LightWidget* light, int duration, QState* parent=0)
{
    QState* lightState = new QState(parent);
    QTimer* timer = new QTimer(lightState);
    timer->setInterval(duration);
    timer->setSingleShot(true);

    QState* timing = new QState(lightState);
    QObject::connect(timing, SIGNAL(entered()), light, SLOT(turnOn()));
    QObject::connect(timing, SIGNAL(entered()), timer, SLOT(start()));
    QObject::connect(timing, SIGNAL(exited()), light, SLOT(turnOff()));

    QFinalState* done = new QFinalState(lightState);
    timing->addTransition(timer, SIGNAL(timeout()), done);
    lightState->setInitialState(timing);
    return lightState;
}


TrafficLight::TrafficLight(QWidget* parent)
    : QWidget(parent)
{
    QVBoxLayout* vbox = new QVBoxLayout(this);
    TrafficLightWidget* widget = new TrafficLightWidget();
    vbox->addWidget(widget);
    vbox->setMargin(0);

    QStateMachine* machine = new QStateMachine(this);

    QState* redGoingYellow = createLightState(widget->redLight(), 3000);
    redGoingYellow->setObjectName("redGoingYellow");

    QState* yellowGoingGreen = createLightState(widget->yellowLight(), 1000);
    yellowGoingGreen->setObjectName("yellowGoingGreen");
    redGoingYellow->addTransition(redGoingYellow, SIGNAL(finished()), yellowGoingGreen);

    QState* greenGoingYellow = createLightState(widget->greenLight(), 3000);
    greenGoingYellow->setObjectName("greenGoingYellow");
    yellowGoingGreen->addTransition(yellowGoingGreen, SIGNAL(finished()), greenGoingYellow);


    QState* yellowGoingRed = createLightState(widget->yellowLight(), 1000);
    yellowGoingRed->setObjectName("yellowGoingRed");
    greenGoingYellow->addTransition(greenGoingYellow, SIGNAL(finished()), yellowGoingRed);
    yellowGoingRed->addTransition(yellowGoingRed, SIGNAL(finished()), redGoingYellow);


    machine->addState(redGoingYellow);
    machine->addState(yellowGoingGreen);
    machine->addState(greenGoingYellow);
    machine->addState(yellowGoingRed);
    machine->setInitialState(redGoingYellow);
    machine->start();
}

