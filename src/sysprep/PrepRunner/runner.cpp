#include "runner.h"
#include <QGuiApplication>
#include <QClipboard>
#include <QDesktopServices>
#include <QUrl>
#include <QFile>
#include <QDir>
#include <QDebug>

const char Runner::strPathDotFiles[] = ".dotfiles";

Runner::Runner(Settings& settings, QObject *parent) : QObject(parent)
  , _settings(settings)
  , _procDotFiles(nullptr)
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
    emit running();
    auto sshstate = installSshKeys();
    switch(sshstate)
    {
    // ssh key already present
    case SshResult::Ok:
        continueRunner();
        break;
    case SshResult::WaitForCopy:
        emit waitForSsh(); // Wait for input ssh keys where needed
        break;
    default:
        emit runFailed(); // This run failed...
    }
}

void Runner::continueRunner() {
    installDotFiles();
}

SshResult Runner::installSshKeys() {
    if( !_settings.doSshKeys() )
        return SshResult::Ok;
    auto filename = fileSshKey();
    appendLog(QString("Installing SSH keys in %1...").arg(filename));
    if (QFile::exists(filename)) {
        appendLog("[Skip] SSH file already present");
        return SshResult::Ok;
    }

    QProcess process;
    QStringList params;
    params << "-b" << "4096" << "-t" << "rsa" << "-f" << filename << "-q" << "-N" << "";
    process.start("ssh-keygen", params);
    process.waitForFinished();
//    appendLog( QString(process.readAllStandardOutput()).split("\n") );

    if( process.exitCode()!=0 ) {
        appendLog( QString(process.readAllStandardError()).split("\n") );
        appendLog("[Failed] Could not generate SSH file");
        return SshResult::Failure;
    }

    auto sshKey = readFile(filename+".pub");
    appendLog("SSH key is "+sshKey);
    if( sshKey.isEmpty() ) {
        appendLog("[Error] SSH is empty");
        return SshResult::Failure;
    }
    QClipboard* clipboard = QGuiApplication::clipboard();
    clipboard->setText(sshKey);

    QDesktopServices::openUrl(QUrl("https://github.com/settings/keys"));
    QDesktopServices::openUrl(QUrl("https://gitlab.com/profile/keys"));
    appendLog("[Ok] SSH keys created");
    return SshResult::WaitForCopy;
}

void Runner::installDotFiles() {
    appendLog("Installing dot files...");
    auto path = pathDotFiles();
    _procDotFiles = new QProcess(this);
    connect(_procDotFiles, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onDotFileExit(int, QProcess::ExitStatus)));
    QStringList params;
    if (QDir(path).exists()) {
        _procDotFiles->setWorkingDirectory(path);
        appendLog("[...] dot files already present, updating");
        params << "pull" << "origin" << "master";
    }
    else {
        _procDotFiles->setWorkingDirectory(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
        appendLog("[...] cloning from server");
        params << "clone" << "git@github.com:slesa/DotFiles" << strPathDotFiles;
    }
    _procDotFiles->start("git", params);
    emit waitForDot();
}

void Runner::onDotFileExit(int exitCode, QProcess::ExitStatus exitStatus) {
    appendLog( QString(_procDotFiles->readAllStandardOutput()).split("\n") );

    if( exitStatus==QProcess::ExitStatus::CrashExit || exitCode!=0 ) {
        appendLog( QString(_procDotFiles->readAllStandardError()).split("\n") );
        appendLog("[Failed] Could not get latest dot files");
        emit runFailed(); // This run failed...
        return;
    }
    appendLog("[Ok] dot files created");
}

QString Runner::fileSshKey() {
    //const char Runner::fileSshKey[] = "~/.ssh/id_rsa.pub";
    auto fn = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.ssh/id_rsa";
    //auto fn = QStandardPaths::locate(QStandardPaths::HomeLocation, ".ssh/id_rsa.pub", QStandardPaths::LocateFile);
    qDebug() << "ssh key file name: " << fn;
    return fn;
}
QString Runner::pathDotFiles() {
    //const char Runner::pathDotFiles[] = "~/.dotfiles";
    auto fn = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/" + strPathDotFiles;
    qDebug() << "dotfiles dir name: " << fn;
    return fn;
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

void Runner::appendLog(const QString& line) {
    qDebug() << line;
    _logfile << line;
    emit logfileChanged();
}
void Runner::appendLog(const QStringList& lines) {
    for(const QString& line : lines) {
        if( !line.isEmpty()) appendLog(line);
    }
}
