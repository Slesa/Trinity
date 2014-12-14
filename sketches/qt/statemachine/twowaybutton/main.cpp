#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPushButton button;
    QStateMachine machine;

    QState* off = new QState();
    off->assignProperty(&button, "text", "off");
    off->setObjectName("off");

    QState* on = new QState();
    on->assignProperty(&button, "text", "On");
    on->setObjectName("on");

    off->addTransition(&button, SIGNAL(clicked()), on);
    on->addTransition(&button, SIGNAL(clicked()), off);

    machine.addState(off);
    machine.addState(on);
    machine.setInitialState(off);
    machine.start();

    button.resize(100, 50);
    button.show();

    return a.exec();
}
