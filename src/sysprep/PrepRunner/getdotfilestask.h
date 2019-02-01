#ifndef GETDOTFILESTASK_H
#define GETDOTFILESTASK_H

#include <QProcess>
#include "runtask.h"

class GetDotFilesTask : public RunTask
{
    static const char strPathDotFiles[];
public:
    explicit GetDotFilesTask(Settings& settings, Logger& logger, QObject* parent=nullptr);

    virtual bool shouldExecute();
    virtual void execute();

private slots:
    void onDotFileExit(int exitCode, QProcess::ExitStatus exitStatus);

private:
    QProcess* _procDotFiles;
    static QString pathDotFiles();
};

#endif // GETDOTFILESTASK_H
