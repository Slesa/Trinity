#ifndef GETDOTFILESTASK_H
#define GETDOTFILESTASK_H

#include <QProcess>
#include "runtask.h"

class GetDotFilesTask : public RunTask
{
    static const char strPathDotFiles[];
public:
    explicit GetDotFilesTask(Runner& runner, Settings& settings, Logger& logger, QObject* parent=nullptr);

    virtual bool shouldExecute() override;
    virtual void execute() override;

private slots:
    void onDotFileExit(int exitCode, QProcess::ExitStatus exitStatus);
    void readStdOut();
    void readStdErr();

private:
    QProcess* _procDotFiles;
    static QString pathDotFiles();
};

#endif // GETDOTFILESTASK_H
