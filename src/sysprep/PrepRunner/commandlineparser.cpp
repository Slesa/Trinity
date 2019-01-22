#include <QCommandLineParser>
#include <QCoreApplication>
#include "commandlineparser.h"
#include "settings.h"

void CommandLineParser::readArguments(QCoreApplication& app, Settings& settings) {
    QCommandLineParser parser;
    initialize(parser);

//    auto doSshKeys = addArgOption(parser, "s", "ssh",  QCoreApplication::translate("main", "Install SSH keys."));
    auto noSshKeys = addArgOption(parser, "ns", "nossh",  QCoreApplication::translate("main", "Do not install SSH keys."));
//    auto doFonts = addArgOption(parser, "f", "fonts",  QCoreApplication::translate("main", "Install Fonts."));
    auto noFonts = addArgOption(parser, "nf", "nofonts",  QCoreApplication::translate("main", "Do not install Fonts."));
//    auto doOwnCube = addArgOption(parser, "o", "owncube",  QCoreApplication::translate("main", "Install OwnQube."));
    auto noOwnCube = addArgOption(parser, "no", "noowncube",  QCoreApplication::translate("main", "Do not install OwnQube."));
//    auto doCorePrograms = addArgOption(parser, "c", "core",  QCoreApplication::translate("main", "Install Core programs."));
    auto noCorePrograms = addArgOption(parser, "nc", "nocore",  QCoreApplication::translate("main", "Do not install Core programs."));
//    auto doXPrograms = addArgOption(parser, "x", QCoreApplication::translate("main", "Install X programs."));
    auto noXPrograms = addArgOption(parser, "nx", "nox",  QCoreApplication::translate("main", "Do not install X programs."));
//    auto doWmPrograms = addArgOption(parser, "w", "wm", QCoreApplication::translate("main", "Install WM dependent programs."));
    auto noWmPrograms = addArgOption(parser, "nw", "nowm", QCoreApplication::translate("main", "Do not install WM dependent programs."));
//    auto doTexPrograms = addArgOption(parser, "t", "tex", QCoreApplication::translate("main", "Install TeX programs."));
    auto noTexPrograms = addArgOption(parser, "nt", "notex", QCoreApplication::translate("main", "Do not install TeX programs."));
//    auto doGames = addArgOption(parser, "g", "games", QCoreApplication::translate("main", "Install Games."));
    auto noGames = addArgOption(parser, "ng", "nogames", QCoreApplication::translate("main", "Do not install Games."));

    parser.process(app);
//    if( parser.isSet(doSshKeys) ) settings.setSshKeys(true);
    if( parser.isSet(noSshKeys) ) settings.setSshKeys(false);
//    if( parser.isSet(doFonts) ) settings.setFonts(true);
    if( parser.isSet(noFonts) ) settings.setFonts(false);
//    if( parser.isSet(doOwnCube) ) settings.setOwnCube(true);
    if( parser.isSet(noOwnCube) ) settings.setOwnCube(false);
//    if( parser.isSet(doCorePrograms) ) settings.setCorePrograms(true);
    if( parser.isSet(noCorePrograms) ) settings.setCorePrograms(false);
//    if( parser.isSet(doXPrograms) ) settings.setXPrograms(true);
    if( parser.isSet(noXPrograms) ) settings.setXPrograms(false);
//    if( parser.isSet(doWmPrograms) ) settings.setWmPrograms(true);
    if( parser.isSet(noWmPrograms) ) settings.setWmPrograms(false);
//    if( parser.isSet(doTexPrograms) ) settings.setTexPrograms(true);
    if( parser.isSet(noTexPrograms) ) settings.setTexPrograms(false);
//    if( parser.isSet(doGames) ) settings.setGames(true);
    if( parser.isSet(noGames) ) settings.setGames(false);
}

void CommandLineParser::initialize(QCommandLineParser& parser) {
    parser.addHelpOption();
    parser.addVersionOption();
    parser.setApplicationDescription("Preparation Runner");
}


QCommandLineOption CommandLineParser::addArgOption(QCommandLineParser& parser, const char* shortName, const QString& text) {
    QCommandLineOption option(shortName, text);
    parser.addOption(option);
    return option;
}

QCommandLineOption CommandLineParser::addArgOption(QCommandLineParser& parser, const char* shortName, const char* longName, const QString& text) {
    QCommandLineOption option(QStringList() << shortName << longName, text);
    parser.addOption(option);
    return option;
}
