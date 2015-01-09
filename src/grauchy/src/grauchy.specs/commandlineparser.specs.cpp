#include "commandlineparser.h"
#include <QtTest/QtTest>

class CommandLineParserSpecs : public QObject
{
    Q_OBJECT

private slots:
    void option_is_false_per_default();
    void rescue_is_set_with_long_arg();
    /*
    void rescue_is_set_with_short_arg();
    void show_is_set_with_long_arg();
    void show_is_set_with_short_arg();
    void options_is_set_with_long_arg();
    void options_is_set_with_short_arg();
    void multiple_is_set_with_long_arg();
    void multiple_is_set_with_short_arg();
    */
};


void CommandLineParserSpecs::option_is_false_per_default()
{
    CommandLineParser parser;
    bool rescue = parser.doRescue();
    QCOMPARE(rescue, false);
}

void CommandLineParserSpecs::rescue_is_set_with_long_arg()
{
    CommandLineParser parser;
    parser.parse(QStringList() << "--rescue");
    bool rescue = parser.doRescue();
    QCOMPARE(rescue, true);
}
/*
void CommandLineParserSpecs::rescue_is_set_with_short_arg()
{
    CommandLineParser parser;
    parser.parse(QStringList() << "-r");
    bool rescue = parser.doRescue();
    QCOMPARE(rescue, true);
}

void CommandLineParserSpecs::show_is_set_with_long_arg()
{
    CommandLineParser parser;
    parser.parse(QStringList() << "-show");
    bool show = parser.doShow();
    QCOMPARE(show, true);
}

void CommandLineParserSpecs::show_is_set_with_short_arg()
{
    CommandLineParser parser;
    parser.parse(QStringList() << "-s");
    bool show = parser.doShow();
    QCOMPARE(show, true);
}

void CommandLineParserSpecs::options_is_set_with_long_arg()
{
    CommandLineParser parser;
    parser.parse(QStringList() << "-options");
    bool option = parser.doOptions();
    QCOMPARE(option, true);
}

void CommandLineParserSpecs::options_is_set_with_short_arg()
{
    CommandLineParser parser;
    parser.parse(QStringList() << "-o");
    bool option = parser.doOptions();
    QCOMPARE(option, true);
}

void CommandLineParserSpecs::multiple_is_set_with_long_arg()
{
    CommandLineParser parser;
    parser.parse(QStringList() << "-multiple");
    bool multiple = parser.doMultiple();
    QCOMPARE(multiple, true);
}

void CommandLineParserSpecs::multiple_is_set_with_short_arg()
{
    CommandLineParser parser;
    parser.parse(QStringList() << "-m");
    bool multiple = parser.doMultiple();
    QCOMPARE(multiple, true);
}
*/

QTEST_MAIN(CommandLineParserSpecs)
#include "commandlineparser.specs.moc"

/*
CommandLineParser::~CommandLineParser()
{
    delete _rescueOption;
    delete _showOption;
    delete _optionsOption;
    delete _multipleOption;
}


void CommandLineParser::parse(const QCoreApplication& app)
{
    _parser.process(app);
}

void CommandLineParser::initialize()
{
    _parser.setApplicationDescription(tr("Graunchy - remember the shortcuts"));
    _parser.addVersionOption();
    _parser.addHelpOption();

    _rescueOption = new QCommandLineOption(QStringList() << "r" << "rescue", tr("Reset skin and position and show the main window."));
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

*/
