#include "runner.h"
#include <QFile>
#include <QProcess>
#include <QDebug>

Runner::Runner(QObject *parent) : QObject(parent)
  , _doSshKeys(true)
  , _doCorePrograms(true)
  , _doXPrograms(true)
  , _doWmPrograms(true)
  , _doTexPrograms(true)
  , _doGames(true)
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
}

void Runner::installSshKeys() {
    if( !doSshKeys() )
        return;

    if (QFile::exists("~/.ssh/id_rsa.pub"))
        return;


}
