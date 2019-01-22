#include "settings.h"
#include <QCommandLineParser>

Settings::Settings(QObject *parent) : QObject(parent)
  , _doSshKeys(true)
  , _doFonts(true)
  , _doOwnCube(true)
  , _doCorePrograms(true)
  , _doXPrograms(true)
  , _doWmPrograms(true)
  , _doTexPrograms(true)
  , _doGames(true)
{
}
