#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>

class Logger : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList logfile MEMBER _logfile NOTIFY logfileChanged)
public:
    explicit Logger(QObject *parent = nullptr);
    void clearLog();
    void appendLog(const QString& line);
    void appendLog(const QStringList& lines);

signals:
    void logfileChanged();

private:
    QStringList _logfile;
};

#endif // LOGGER_H
