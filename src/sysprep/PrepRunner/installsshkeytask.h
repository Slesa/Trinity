#ifndef INSTALLSSHKEYTASK_H
#define INSTALLSSHKEYTASK_H

#include "runtask.h"

class InstallSshKeyTask : public RunTask
{
public:
    explicit InstallSshKeyTask(Runner& runner, Settings& settings, Logger& logger, QObject* parent=nullptr);

    virtual bool shouldExecute() override;
    virtual void execute() override;

private:
    static QString fileSshKey();
};

#endif // INSTALLSSHKEYTASK_H
