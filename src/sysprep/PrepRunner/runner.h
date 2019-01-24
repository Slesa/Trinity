#ifndef RUNNER_H
#define RUNNER_H

#include "settings.h"
#include <QStringList>
#include <QObject>
#include <QDebug>

class Runner : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList logfile MEMBER _logfile NOTIFY logfileChanged)
public:
    explicit Runner(Settings& settings, QObject *parent = nullptr);
    Q_INVOKABLE void startRunner();
    Q_INVOKABLE void continueRunner();

    bool hasRootRights();

signals:
    void logfileChanged();
    void running();
    void waitForSsh();

private:
    Settings& _settings;
    QStringList _logfile;

    static QString fileSshKey();
    static QString pathDotFiles();

    bool installSshKeys();
    bool installDotFiles();
    QString readFile(const QString& fileName);
    void appendLog(const QString& line);
    void appendLog(const QStringList& lines);
};

#endif // RUNNER_H
