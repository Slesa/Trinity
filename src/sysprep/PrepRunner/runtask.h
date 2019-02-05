#ifndef RUNTASK_H
#define RUNTASK_H

#include <QList>
#include <QObject>
#include "settings.h"
#include "logger.h"

class Runner;
class RunTask : public QObject
{
    Q_OBJECT
public:
    explicit RunTask(Runner& runner, Settings& settings, Logger& logger, QObject* parent=nullptr);
    virtual ~RunTask() {}

    virtual bool shouldExecute() = 0;
    virtual void execute() = 0;

    static QList<RunTask*>* createTasks(Runner& runner, Settings& settings, Logger& logger);
signals:
    void finished();
    void failed();

protected:
    Runner& _runner;
    Settings& _settings;
    Logger& _logger;

private:
    static void appendTask(QList<RunTask*>* list, Runner& runner, RunTask* task);
};

#endif // RUNTASK_H
