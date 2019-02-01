#include "runner.h"
#include <QClipboard>
#include <QFile>
#include <QDebug>


Runner::Runner(Settings& settings, Logger& logger, QObject *parent) : QObject(parent)
  , _settings(settings)
  , _logger(logger)
  , _canQuit(true)
  , _canBack(true)
  , _canContinue(true)
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
    emit running();
    _logger.appendLog("Started...");
    //auto sshstate = installSshKeys();
    /* switch(sshstate)
    {
    // ssh key already present
    case SshResult::Ok:
        continueRunner();
        break;
    case SshResult::WaitForCopy:
        emit waitForSsh(); // Wait for input ssh keys where needed
        break;
    // default:
    //    emit runFailed(); // This run failed...
    } */
}

void Runner::stopRunner() {
    emit runStopped();
}

void Runner::continueRunner() {
    installDotFiles();
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

