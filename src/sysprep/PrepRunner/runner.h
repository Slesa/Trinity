#ifndef RUNNER_H
#define RUNNER_H

#include "settings.h"
#include "logger.h"
#include <QStringList>
#include <QObject>
#include <QDebug>

class Runner : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool canQuit MEMBER _canQuit NOTIFY canQuitChanged)
    Q_PROPERTY(bool canBack MEMBER _canBack NOTIFY canBackChanged)
    Q_PROPERTY(bool canContinue MEMBER _canContinue NOTIFY canContinueChanged)

public:
    explicit Runner(Settings& settings, Logger& logger, QObject *parent = nullptr);
    Q_INVOKABLE void startRunner();
    Q_INVOKABLE void stopRunner();
    Q_INVOKABLE void continueRunner();

    bool hasRootRights();
    static QString readFile(const QString& fileName);

signals:
    void canQuitChanged();
    void canBackChanged();
    void canContinueChanged();

    // In start page was run started
    void running();
    void runStopped();
    void runFailed();
    // Copy ssh key in cliboard where needed
    void waitForSsh();
    void waitForDot();

private:
    Settings& _settings;
    Logger& _logger;
    bool _canQuit;
    bool _canBack;
    bool _canContinue;
};

#endif // RUNNER_H
