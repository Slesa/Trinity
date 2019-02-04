#include "runner.h"
#include "runtask.h"
#include <QCoreApplication>
#include <QProcess>
#include <QClipboard>
#include <QFile>
#include <QDebug>


Runner::Runner(Settings& settings, Logger& logger, QObject *parent) : QObject(parent)
  , _settings(settings)
  , _logger(logger)
  , _canQuit(true)
  , _canBack(true)
  , _canContinue(true)
  , _currentTask(nullptr)
{
}

bool Runner::hasRootRights() {
    QProcess process;
    QStringList params("-nv");
    process.start("sudo", params);
    process.waitForFinished();
    if( process.exitCode()==0 )
        return true;
/*    QProcess sudoProc;
    QStringList sudoParams;
    sudoParams << "sudo" << "./PrepRunner";
    qDebug() << "start sudo";
    sudoProc.startDetached("xterm", params);
    qDebug() << "wait for sudo";
    sudoProc.waitForFinished(0);
    qDebug() << "sudo started";*/
    return false;
}

void Runner::startRunner() {
    _logger.clearLog();
    _runTasks = RunTask::createTasks(*this, _settings, _logger);
    emit running();
    _logger.appendLog(tr("Started, got %1 tasks...").arg(_runTasks->count()));

    continueRunner();
}

void Runner::stopRunner() {
    emit runFinished();
}

void Runner::continueRunner() {
    QCoreApplication::processEvents();
    if( _currentTask!=nullptr) delete _currentTask;

    emit continueRun();
    _currentTask = _runTasks->takeFirst();
    _currentTask->execute();
}





QString Runner::readFile(const QString& fileName) {
    QString result;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QFile::Text)) {
        qCritical() << "Error: could not read file " << fileName << ": " << file.errorString();
        return result;
    }

    QTextStream in(&file);
    result = in.readAll();
    qDebug() << "ssh key read as " << result;
    file.close();
    return result;
}

