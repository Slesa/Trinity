#include <QtCore>
#include <stdio.h>

class Factorial : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int x READ x WRITE setX)
    Q_PROPERTY(int fac READ fac WRITE setFac)
public:
    Factorial(QObject* parent=0)
        : QObject(parent), m_x(-1), m_fac(1)
    {}

    int x() const
    {
        return m_x;
    }
    void setX(int x)
    {
        if(x==m_x) return;
        m_x = x;
        emit xChanged(x);
    }

    int fac() const
    {
        return m_fac;
    }
    void setFac(int fac)
    {
        m_fac = fac;
    }

Q_SIGNALS:
    void xChanged(int value);

private:
    int m_x;
    int m_fac;
};

class FactorialLoopTransition : public QSignalTransition
{
public:
    FactorialLoopTransition(Factorial* fact)
        : QSignalTransition(fact, SIGNAL(xChanged(int))), m_fact(fact)
    {}

    virtual bool eventTest(QEvent *event) Q_DECL_OVERRIDE {
        if(!QSignalTransition::eventTest(event))
            return false;
        QStateMachine::SignalEvent *se = static_cast<QStateMachine::SignalEvent*>(event);
        return se->arguments().at(0).toInt() > 1;
    }
    virtual void onTransition(QEvent *event) Q_DECL_OVERRIDE {
        QStateMachine::SignalEvent *se = static_cast<QStateMachine::SignalEvent*>(event);
        int x = se->arguments().at(0).toInt();
        int fac = m_fact->property("fac").toInt();
        m_fact->setProperty("fac", x*fac);
        m_fact->setProperty("x", x-1);
        fprintf(stdout, "fac now %d\n", m_fact->property("fac").toInt());
    }
private:
    Factorial* m_fact;
};

class FactorialDoneTransition : public QSignalTransition
{
public:
    FactorialDoneTransition(Factorial* fact)
        :QSignalTransition(fact, SIGNAL(xChanged(int))), m_fact(fact)
    {}

    virtual bool eventTest(QEvent* event) Q_DECL_OVERRIDE {
        if(!QSignalTransition::eventTest(event))
            return false;
        QStateMachine::SignalEvent* se = static_cast<QStateMachine::SignalEvent*>(event);
        return se->arguments().at(0).toInt() <= 1;
    }

    virtual void onTransition(QEvent*) Q_DECL_OVERRIDE {
        fprintf(stdout, "%d\n", m_fact->property("fac").toInt());
    }
private:
    Factorial* m_fact;
};

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Factorial factorial;
    QStateMachine machine;

    QState* compute = new QState(&machine);
    compute->assignProperty(&factorial, "fac", 1);
    compute->assignProperty(&factorial, "x", 6);
    compute->addTransition(new FactorialLoopTransition(&factorial));

    QFinalState* done = new QFinalState(&machine);
    FactorialDoneTransition* doneTransition = new FactorialDoneTransition(&factorial);
    doneTransition->setTargetState(done);
    compute->addTransition(doneTransition);

    machine.setInitialState(compute);
    QObject::connect(&machine, SIGNAL(finished()), &app, SLOT(quit()));
    machine.start();

    return app.exec();
}

#include "main.moc"
