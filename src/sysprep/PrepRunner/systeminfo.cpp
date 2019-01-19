#include "systeminfo.h"
#include <QSysInfo>
#include <QProcess>
#include <QDebug>

const char* SystemInfo::strLinux = "linux";
const char* SystemInfo::wmWindows = "windows";
const char* SystemInfo::wmXfce = "xfce";
const char* SystemInfo::wmKde = "kde";
const char* SystemInfo::wmUnknown = "unknown";
const char* SystemInfo::appXfce = "xfce4-panel";
const char* SystemInfo::appKde = "kde4-panel";

SystemInfo::SystemInfo()
{
    qDebug() << "Build abi...........:   " << QSysInfo::buildAbi();
    qDebug() << "Build architecture..:   " << QSysInfo::buildCpuArchitecture();
    qDebug() << "CPU architecture....:   " << QSysInfo::currentCpuArchitecture();
    _kernelType = QSysInfo::kernelType();
    qDebug() << "Kernel type.........:   " << QSysInfo::kernelType();
    qDebug() << "Kernel version......:   " << QSysInfo::kernelVersion();
    qDebug() << "Machine host name...:   " << QSysInfo::machineHostName();
    //QByteArray	machineUniqueId()
    _osName = QSysInfo::prettyProductName();
    qDebug() << "Pretty product name.:   " << QSysInfo::prettyProductName();
    _distribution = QSysInfo::productType();
    qDebug() << "Product type........:   " << QSysInfo::productType();
    qDebug() << "Product version.....:   " << QSysInfo::productVersion();

    qDebug() << "Is linux?...........:   " << (isLinux() ? "Yes" : "No");
    _wmName = determineWm();
    qDebug() << "Window manager......:   " << _wmName;

    emit dataChanged();
}

bool SystemInfo::isLinux() const {
    return QSysInfo::kernelType() == strLinux;
}

QString SystemInfo::determineWm() const {
    if( isLinux() ) {
        if( isProcessRunning(appXfce))
            return wmXfce;
        if( isProcessRunning(appKde))
            return wmKde;
        return wmUnknown;
    }
    return wmWindows;
}

bool SystemInfo::isProcessRunning(const char* app) const {
    QProcess process;
    QStringList params(app);
    process.start("pidof", params);
    process.waitForFinished();
    QString result( process.readAllStandardOutput());
    return !result.isEmpty();
}
