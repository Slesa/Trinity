#include "runner.h"
#include <QGuiApplication>
#include <QClipboard>
#include <QDesktopServices>
#include <QUrl>
#include <QFile>
#include <QDir>
#include <QProcess>
#include <QDebug>

const char Runner::fileSshKey[] = "~/.ssh/id_rsa.pub";
const char Runner::pathDotFiles[] = "~/.dotfiles";

Runner::Runner(Settings& settings, QObject *parent) : QObject(parent)
    , _settings(settings)
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
    installSshKeys();
    installDotFiles();
}

bool Runner::installSshKeys() {
    if( !_settings.doSshKeys() )
        return false;
    _logfile << "Installing SSH keys";
    if (QFile::exists(fileSshKey)) {
        _logfile << "[Skip] SSH file already present";
        return false;
    }
    QProcess process;
    auto params = QStringList() << "-b" << "2048" << "-t" << "rsa" << "-f" << fileSshKey << "-q" << "-N" << "";
    process.start("ssh-keygen", params);
    process.waitForFinished();
    if( process.exitCode()!=0 ) {
        _logfile << "[Failed] Could not generate SSH file";
        return false;
    }

    auto sshKey = readFile(fileSshKey);
    QClipboard* clipboard = QGuiApplication::clipboard();
    clipboard->setText(sshKey);

    QDesktopServices::openUrl(QUrl("https://github.com/settings/keys"));
    QDesktopServices::openUrl(QUrl("https://gitlab.com/profile/keys"));
    _logfile << "[Ok] SSH keys created";
    return true;
}

bool Runner::installDotFiles() {
    _logfile << "Installing dot files";
    QProcess process;
    QStringList params;
    if (QDir(pathDotFiles).exists()) {
        _logfile << "[...] dot files already present, updating";
        params << "pull" << "origin" << "master";
    }
    else {
        _logfile << "[...] cloning from server";
        params << "clone" << "git@github.com:slesa/DotFiles" << pathDotFiles;
    }
    process.start("git", params);
    process.waitForFinished();
    if( process.exitCode()!=0 ) {
        _logfile << "[Failed] Could not get latest dot files";
        return false;
    }
    _logfile << "[Ok] dot files created";
    return true;
}



QString Runner::readFile(const char* fileName) {
    QString result;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error: could not read file "<< file.errorString();
        return result;
    }

    QTextStream in(&file);
    while(!in.atEnd()) {
        result += in.readLine() + "\n";
    }
    file.close();
    return result;
}
