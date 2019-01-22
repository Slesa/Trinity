#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H
#include <QString>
#include <QCommandLineOption>

class Settings;
class QCommandLineParser;
class QCoreApplication;

class CommandLineParser
{
public:
    static void readArguments(QCoreApplication& app, Settings& settings);
private:
    static void initialize(QCommandLineParser& parser);
    static QCommandLineOption addArgOption(QCommandLineParser& parser, const char* shortName, const QString& text);
    static QCommandLineOption addArgOption(QCommandLineParser& parser, const char* shortName, const char* longName, const QString& text);
};

#endif // COMMANDLINEPARSER_H
