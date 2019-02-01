#include "logger.h"
#include <QDebug>

Logger::Logger(QObject *parent) : QObject(parent)
{
}

void Logger::clearLog() {
    _logfile.clear();
    emit logfileChanged();
}
void Logger::appendLog(const QString& line) {
    qDebug() << line;
    _logfile << line;
    emit logfileChanged();
}
void Logger::appendLog(const QStringList& lines) {
    for(const QString& line : lines) {
        if( !line.isEmpty()) appendLog(line);
    }
}

