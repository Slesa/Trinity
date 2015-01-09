#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

#include <QCommandLineParser>

class QStringList;

class CommandLineParser : QObject
{
    Q_OBJECT
public:
    static const char* argRescue;
public:
    CommandLineParser();
    ~CommandLineParser();
    void parse(const QStringList& params);

    bool doRescue () const { return _parser.isSet(*_rescueOption); }
    bool doShow() const { return _parser.isSet(*_showOption); }
    bool doOptions() const { return _parser.isSet(*_optionsOption); }
    bool doMultiple() const { return _parser.isSet(*_multipleOption); }
private:
    void initialize();
private:
    QCommandLineParser _parser;
    QCommandLineOption* _rescueOption;
    QCommandLineOption* _showOption;
    QCommandLineOption* _optionsOption;
    QCommandLineOption* _multipleOption;
};

#endif // COMMANDLINEPARSER_H
