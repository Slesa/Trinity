#ifndef RUNNER_H
#define RUNNER_H

#include "settings.h"
#include "logger.h"
#include <QList>
#include <QStringList>
#include <QObject>
#include <QDebug>

class RunTask;

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

    void doFinish() { emit runFinished(); }
    void doFail() { emit runFailed(); }
    void doContinue() { emit continueRun(); }
    void doWaitForSsh() { emit waitForSsh(); }
    void doWaitForDot() { emit waitForDot(); }
signals:
    void canQuitChanged();
    void canBackChanged();
    void canContinueChanged();

    // In start page was run started
    void running();
    void runFinished();
    void runFailed();
    void continueRun();
    // Copy ssh key in cliboard where needed
    void waitForSsh();
    void waitForDot();

private:
    Settings& _settings;
    Logger& _logger;
    bool _canQuit;
    bool _canBack;
    bool _canContinue;

    QList<RunTask*>* _runTasks;
    RunTask* _currentTask;
};

#endif // RUNNER_H
