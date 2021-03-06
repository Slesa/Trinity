#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

#include <QCommandLineParser>

class QStringList;
class QCoreApplication;

class CommandLineParser : QObject
{
    Q_OBJECT
public:
    static const char* argRescue;
    static const char* argShow;
    static const char* argOptions;
    static const char* argMultiple;
    static const char* argExit;
    static const char* argLog;
public:
    CommandLineParser();

    void process(const QCoreApplication& app);
    void parse(const QStringList& params);

    bool doRescue () const { return _parser.isSet(argRescue); }
    bool doShow() const { return _parser.isSet(argShow); }
    bool doOptions() const { return _parser.isSet(argOptions); }
    bool doMultiple() const { return _parser.isSet(argMultiple); }
    bool doExit() const { return _parser.isSet(argExit); }
    bool doLog() const { return _parser.isSet(argLog); }
private:
    void initialize();
private:
    QCommandLineParser _parser;
};

#endif // COMMANDLINEPARSER_H
