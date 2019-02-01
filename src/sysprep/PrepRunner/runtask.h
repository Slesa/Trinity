#ifndef RUNTASK_H
#define RUNTASK_H

#include <QObject>
#include "settings.h"
#include "logger.h"

class RunTask : public QObject
{
    Q_OBJECT
public:
    explicit RunTask(Settings& settings, Logger& logger, QObject* parent=nullptr);
    virtual ~RunTask() {}

    virtual bool shouldExecute() = 0;
    virtual void execute() = 0;

signals:
    void finished();
    void failed();

protected:
    Settings& _settings;
    Logger& _logger;
};

#endif // RUNTASK_H
