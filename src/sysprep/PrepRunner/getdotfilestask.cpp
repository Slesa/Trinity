#include "getdotfilestask.h"
#include "runner.h"
#include <QDesktopServices>
#include <QDir>
#include <QDebug>

const char GetDotFilesTask::strPathDotFiles[] = ".dotfiles";

GetDotFilesTask::GetDotFilesTask(Runner& runner, Settings& settings, Logger& logger, QObject* parent) : RunTask(runner, settings, logger, parent)
  , _procDotFiles(nullptr)
{
}

bool GetDotFilesTask::shouldExecute() {
    return true;
}

void GetDotFilesTask::execute() {
    _logger.appendLog("Installing dot files...");
    auto path = pathDotFiles();
    _procDotFiles = new QProcess(this);
    connect(_procDotFiles, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onDotFileExit(int, QProcess::ExitStatus)));
    QStringList params;
    if (QDir(path).exists()) {
        _procDotFiles->setWorkingDirectory(path);
        _logger.appendLog("[...] dot files already present, updating");
        params << "pull" << "origin" << "master";
    }
    else {
        _procDotFiles->setWorkingDirectory(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
        _logger.appendLog("[...] cloning from server");
        params << "clone" << "git@github.com:slesa/DotFiles" << strPathDotFiles;
    }
    _procDotFiles->start("git", params);
    _runner.doWaitForDot();
}

void GetDotFilesTask::onDotFileExit(int exitCode, QProcess::ExitStatus exitStatus) {
    _logger.appendLog( QString(_procDotFiles->readAllStandardOutput()).split("\n") );

    if( exitStatus==QProcess::ExitStatus::CrashExit || exitCode!=0 ) {
        _logger.appendLog( QString(_procDotFiles->readAllStandardError()).split("\n") );
        _logger.appendLog("[Failed] Could not get latest dot files");
        emit failed(); // This run failed...
        return;
    }
    _logger.appendLog("[Ok] dot files created");
    emit finished();
}


QString GetDotFilesTask::pathDotFiles() {
    //const char Runner::pathDotFiles[] = "~/.dotfiles";
    auto fn = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/" + strPathDotFiles;
    qDebug() << "dotfiles dir name: " << fn;
    return fn;
}
