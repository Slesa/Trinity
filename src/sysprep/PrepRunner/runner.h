#ifndef RUNNER_H
#define RUNNER_H

#include "settings.h"
#include <QStringList>
#include <QObject>
#include <QDebug>

class Runner : public QObject
{
    Q_OBJECT
    static const char fileSshKey[];
    static const char pathDotFiles[];
public:
    explicit Runner(Settings& settings, QObject *parent = nullptr);
    Q_INVOKABLE void startRunner();

    bool hasRootRights();


private:
    Settings& _settings;
    QStringList _logfile;
        
    bool installSshKeys();
    bool installDotFiles();
    QString readFile(const char* fileName);
};

#endif // RUNNER_H
