#include "installsshkeytask.h"
#include "runner.h"
#include <QClipboard>
#include <QDesktopServices>
#include <QGuiApplication>
#include <QProcess>
#include <QUrl>
#include <QFile>
#include <QDebug>

InstallSshKeyTask::InstallSshKeyTask(Runner& runner, Settings& settings, Logger& logger, QObject* parent) : RunTask(runner, settings, logger, parent)
{
}

bool InstallSshKeyTask::shouldExecute() {
    return _settings.doSshKeys();
}

void InstallSshKeyTask::execute() {
    auto filename = fileSshKey();
    _logger.appendLog(QString("Installing SSH keys in %1...").arg(filename));
    if (QFile::exists(filename)) {
        _logger.appendLog("[Skip] SSH file already present");
        _runner.continueRunner();
        return;
    }

    QProcess process;
    QStringList params;
    params << "-b" << "4096" << "-t" << "rsa" << "-f" << filename << "-q" << "-N" << "";
    process.start("ssh-keygen", params);
    process.waitForFinished();
//    appendLog( QString(process.readAllStandardOutput()).split("\n") );

    if( process.exitCode()!=0 ) {
        _logger.appendLog( QString(process.readAllStandardError()).split("\n") );
        _logger.appendLog("[Failed] Could not generate SSH file");
        _runner.doFail();
        return;
    }

    auto sshKey = Runner::readFile(filename+".pub");
    _logger.appendLog("SSH key is "+sshKey);
    if( sshKey.isEmpty() ) {
        _logger.appendLog("[Error] SSH is empty");
        _runner.doFail();
        return;
    }
    QClipboard* clipboard = QGuiApplication::clipboard();
    clipboard->setText(sshKey);

    QDesktopServices::openUrl(QUrl("https://github.com/settings/keys"));
    QDesktopServices::openUrl(QUrl("https://gitlab.com/profile/keys"));
    _logger.appendLog("[Ok] SSH keys created");
    _runner.doWaitForSsh();

}

QString InstallSshKeyTask::fileSshKey() {
    //const char Runner::fileSshKey[] = "~/.ssh/id_rsa.pub";
    auto fn = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.ssh/id_rsa";
    //auto fn = QStandardPaths::locate(QStandardPaths::HomeLocation, ".ssh/id_rsa.pub", QStandardPaths::LocateFile);
    qDebug() << "ssh key file name: " << fn;
    return fn;
}
