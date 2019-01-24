#include "runner.h"
#include <QGuiApplication>
#include <QClipboard>
#include <QDesktopServices>
#include <QUrl>
#include <QFile>
#include <QDir>
#include <QProcess>
#include <QDebug>

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
    emit running();
    installSshKeys();
}

void Runner::continueRunner() {
    installDotFiles();
}

bool Runner::installSshKeys() {
    if( !_settings.doSshKeys() )
        return false;
    auto filename = fileSshKey();
    appendLog(QString("Installing SSH keys in %1...").arg(filename));
    if (QFile::exists(filename)) {
        appendLog("[Skip] SSH file already present");
        return false;
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
        return false;
    }

    auto sshKey = readFile(filename+".pub");
    appendLog("SSH key is "+sshKey);
    if( sshKey.isEmpty() ) {
        appendLog("[Error] SSH is empty");
        return false;
    }
    QClipboard* clipboard = QGuiApplication::clipboard();
    clipboard->setText(sshKey);

    QDesktopServices::openUrl(QUrl("https://github.com/settings/keys"));
    QDesktopServices::openUrl(QUrl("https://gitlab.com/profile/keys"));
    appendLog("[Ok] SSH keys created");
    emit waitForSsh();
    return true;
}

bool Runner::installDotFiles() {
    appendLog("Installing dot files...");
    auto path = pathDotFiles();
    QProcess process;
    QStringList params;
    if (QDir(path).exists()) {
        appendLog("[...] dot files already present, updating");
        params << "pull" << "origin" << "master";
    }
    else {
        appendLog("[...] cloning from server");
        params << "clone" << "git@github.com:slesa/DotFiles" << path;
    }
    process.start("git", params);
    process.waitForFinished();
    appendLog( QString(process.readAllStandardOutput()).split("\n") );

    if( process.exitCode()!=0 ) {
        appendLog( QString(process.readAllStandardError()).split("\n") );
        appendLog("[Failed] Could not get latest dot files");
        return false;
    }
    appendLog("[Ok] dot files created");
    return true;
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
    return QStandardPaths::locate(QStandardPaths::HomeLocation, ".dotfiles", QStandardPaths::LocateDirectory);
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
