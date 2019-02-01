#ifndef INSTALLSSHKEYTASK_H
#define INSTALLSSHKEYTASK_H

#include "runtask.h"

class InstallSshKeyTask : public RunTask
{
public:
    explicit InstallSshKeyTask(Settings& settings, Logger& logger, QObject* parent=nullptr);

    virtual bool shouldExecute();
    virtual void execute();

private:
    static QString fileSshKey();
};

#endif // INSTALLSSHKEYTASK_H
