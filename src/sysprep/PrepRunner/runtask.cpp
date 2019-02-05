#include "runtask.h"
#include "runner.h"
#include "getdotfilestask.h"
#include "installsshkeytask.h"

RunTask::RunTask(Runner& runner, Settings& settings, Logger& logger, QObject* parent) : QObject(parent)
  , _runner(runner)
  , _settings(settings)
  , _logger(logger)
{
}

QList<RunTask*>* RunTask::createTasks(Runner& runner, Settings& settings, Logger& logger) {
    auto result = new QList<RunTask*>();

    auto installSshKeyTask = new InstallSshKeyTask(runner, settings, logger);
    appendTask(result, runner, installSshKeyTask);

    auto getDotFilesTask = new GetDotFilesTask(runner, settings, logger);
    appendTask(result, runner, getDotFilesTask);

    return result;
}

void RunTask::appendTask(QList<RunTask*>* list, Runner& runner, RunTask* task) {
    if( task->shouldExecute() ) {
        connect(task, SIGNAL(finished()), &runner, SLOT(cont));
        list->append(task);
    }
    else
        delete task;
}
