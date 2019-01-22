#ifndef RUNNER_H
#define RUNNER_H

#include "settings.h"
#include <QObject>
#include <QDebug>

class Runner : public QObject
{
    Q_OBJECT
public:
    explicit Runner(Settings& settings, QObject *parent = nullptr);
    Q_INVOKABLE void startRunner();

    bool hasRootRights();


private:

    void installSshKeys();

    Settings& _settings;
};

#endif // RUNNER_H
