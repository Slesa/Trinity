#include "commandlineparser.h"
#include <QDebug>

CommandLineParser::CommandLineParser()
{
    initialize();
}

CommandLineParser::~CommandLineParser()
{
    delete _rescueOption;
    delete _showOption;
    delete _optionsOption;
    delete _multipleOption;
}


void CommandLineParser::parse(const QStringList& params)
{
    qDebug() << "Params: " << params;
    //_parser.parse(QStringList() << params << "-r" << "-rescue" << "-help");
    _parser.parse(QStringList() << "x" << "-r");
    //_parser.parse(params);

    qDebug() << _parser.optionNames();
    qDebug() << "Rescue? " << _parser.isSet(*_rescueOption);
    qDebug() << "Rescue? " << _parser.isSet("rescue");
    qDebug() << "Rescue? " << _parser.isSet("r");
}

void CommandLineParser::initialize()
{
    _parser.setApplicationDescription(tr("Graunchy - remember the shortcuts"));
    _parser.addVersionOption();
    _parser.addHelpOption();

    _rescueOption = new QCommandLineOption(QStringList() << "r" /*<< "rescue"*/, tr("Reset skin and position and show the main window."));
    //_rescueOption = new QCommandLineOption("r", tr("Reset skin and position and show the main window."));
    _parser.addOption(*_rescueOption);
    _showOption = new QCommandLineOption(QStringList() << "s" << "show", tr("Show the main window"));
    _parser.addOption(*_showOption);
    _optionsOption = new QCommandLineOption(QStringList() << "o" << "options", tr("Show the options dialog"));
    _parser.addOption(*_optionsOption);
    _multipleOption = new QCommandLineOption(QStringList() << "m" << "multiple", tr("Allow multiple instances"));
    _parser.addOption(*_multipleOption);

//			else if (arg.compare("exit", Qt::CaseInsensitive) == 0)
//			{
//				command |= Exit;
//			}
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

