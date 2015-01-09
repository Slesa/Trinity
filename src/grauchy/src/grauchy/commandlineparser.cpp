#include "commandlineparser.h"
#include <QDebug>

const char* CommandLineParser::argRescue = "rescue";
const char* CommandLineParser::argShow = "show";
const char* CommandLineParser::argOptions = "options";
const char* CommandLineParser::argMultiple = "multiple";
const char* CommandLineParser::argExit = "exit";

CommandLineParser::CommandLineParser()
{
    initialize();
}

void CommandLineParser::process(const QCoreApplication& app)
{
    _parser.process(app);
}

void CommandLineParser::parse(const QStringList& params)
{
    QStringList args;
    args << "@" << params; // Fake first argument (program name)
    _parser.parse(args);
}

void CommandLineParser::initialize()
{
    _parser.setApplicationDescription(tr("Graunchy - remember the shortcuts"));
    _parser.addVersionOption();
    _parser.addHelpOption();

    QCommandLineOption rescueOption(QStringList() << "r" << argRescue, tr("Reset skin and position and show the main window."));
    _parser.addOption(rescueOption);

    QCommandLineOption showOption(QStringList() << "s" << argShow, tr("Show the main window"));
    _parser.addOption(showOption);

    QCommandLineOption optionsOption(QStringList() << "o" << argOptions, tr("Show the options dialog"));
    _parser.addOption(optionsOption);

    QCommandLineOption multipleOption(QStringList() << "m" << argMultiple, tr("Allow multiple instances"));
    _parser.addOption(multipleOption);

    QCommandLineOption exitOption(QStringList() << "x" << argExit, tr("Exit a running instance"));
    _parser.addOption(exitOption);

//			else if (arg.compare("log", Qt::CaseInsensitive) == 0)
//			{
//                qInstallMessageHandler(fileLogMsgHandler);
//			}
//			else if (arg.compare("profile", Qt::CaseInsensitive) == 0)
//			{
//				if (++i < args.length())
//				{
//					settings.setProfileName(args[i]);
//				}
//			}
}

