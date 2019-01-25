#ifndef RUNNER_H
#define RUNNER_H

#include "settings.h"
#include <QStringList>
#include <QObject>
#include <QDebug>

enum SshResult {
    Ok, WaitForCopy, Failure
};

class Runner : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList logfile MEMBER _logfile NOTIFY logfileChanged)

    static const char strPathDotFiles[];
public:
    explicit Runner(Settings& settings, QObject *parent = nullptr);
    Q_INVOKABLE void startRunner();
    Q_INVOKABLE void continueRunner();

    bool hasRootRights();

signals:
    void logfileChanged();
    // In start page was run started
    void running();
    // Run failed
    void runFailed();
    // Copy ssh key in cliboard where needed
    void waitForSsh();

private:
    Settings& _settings;
    QStringList _logfile;

    static QString fileSshKey();
    static QString pathDotFiles();

    SshResult installSshKeys();
    // Returns true if no error occured
    bool installDotFiles();

    QString readFile(const QString& fileName);
    void appendLog(const QString& line);
    void appendLog(const QStringList& lines);
};

#endif // RUNNER_H
