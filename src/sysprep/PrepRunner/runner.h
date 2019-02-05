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
    Q_PROPERTY(bool canQuit MEMBER _canQuit NOTIFY canQuitChanged READ canQuit WRITE setCanQuit)
    Q_PROPERTY(bool canBack MEMBER _canBack NOTIFY canBackChanged READ canBack WRITE setCanBack)
    Q_PROPERTY(bool canContinue MEMBER _canContinue NOTIFY canContinueChanged READ canContinue WRITE setCanContinue)

public:
    explicit Runner(Settings& settings, Logger& logger, QObject *parent = nullptr);
    Q_INVOKABLE void startRunner();
    Q_INVOKABLE void stopRunner();
    Q_INVOKABLE void continueRunner();

    bool hasRootRights();
    static QString readFile(const QString& fileName);

    bool canQuit() const { return _canQuit; }
    void setCanQuit(bool value) { _canQuit = value; emit canQuitChanged(); }
    bool canBack() const { return _canBack; }
    void setCanBack(bool value) { _canBack = value; emit canBackChanged(); }
    bool canContinue() const { return _canContinue; }
    void setCanContinue(bool value) { _canContinue = value; emit canContinueChanged(); }

    void doFinish() { setCanBack(true); emit runFinished(); }
    void doFail() { setCanBack(true); emit runFailed(); }
    void doWaitForSsh() { setCanContinue(true); emit waitForSsh(); }
    void doWaitForDot() { setCanContinue(true); emit waitForDot(); }
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
