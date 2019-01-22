#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class QCommandLineParser;

class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool doSshKeys MEMBER _doSshKeys READ doSshKeys WRITE setSshKeys NOTIFY doSshKeysChanged)
    Q_PROPERTY(bool doFonts MEMBER _doFonts READ doFonts WRITE setFonts NOTIFY doFontsChanged)
    Q_PROPERTY(bool doCorePrograms MEMBER _doCorePrograms READ doCorePrograms WRITE setCorePrograms NOTIFY doCoreChanged)
    Q_PROPERTY(bool doXPrograms MEMBER _doXPrograms READ doXPrograms WRITE setXPrograms NOTIFY doXChanged)
    Q_PROPERTY(bool doWmPrograms MEMBER _doWmPrograms READ doWmPrograms WRITE setWmPrograms NOTIFY doWmChanged)
    Q_PROPERTY(bool doTexPrograms MEMBER _doTexPrograms READ doTexPrograms WRITE setTexPrograms NOTIFY doTexChanged)
    Q_PROPERTY(bool doGames MEMBER _doGames READ doGames WRITE setGames NOTIFY doGamesChanged)
public:
    explicit Settings(QObject *parent=nullptr);

    bool doSshKeys() const { return _doSshKeys; }
    void setSshKeys(bool value) { _doSshKeys = value; emit doSshKeysChanged(); }
    bool doFonts() const { return _doFonts; }
    void setFonts(bool value) { _doFonts = value; emit doFontsChanged(); }
    bool doOwnCube() const { return _doOwnCube; }
    void setOwnCube(bool value) { _doOwnCube = value; emit doOwnCubeChanged(); }
    bool doCorePrograms() const { return _doCorePrograms; }
    void setCorePrograms(bool value) { _doCorePrograms = value; emit doCoreChanged(); }
    bool doXPrograms() const { return _doXPrograms; }
    void setXPrograms(bool value) { _doXPrograms = value; emit doXChanged(); }
    bool doWmPrograms() const { return _doWmPrograms; }
    void setWmPrograms(bool value) { _doWmPrograms = value; emit doWmChanged(); }
    bool doTexPrograms() const { return _doTexPrograms; }
    void setTexPrograms(bool value) { _doTexPrograms = value; emit doTexChanged(); }
    bool doGames() const { return _doGames; }
    void setGames(bool value) { _doGames = value; emit doGamesChanged(); }

signals:
    void doSshKeysChanged();
    void doFontsChanged();
    void doOwnCubeChanged();
    void doCoreChanged();
    void doXChanged();
    void doWmChanged();
    void doTexChanged();
    void doGamesChanged();

private:
    bool _doSshKeys;
    bool _doFonts;
    bool _doOwnCube;
    bool _doCorePrograms;
    bool _doXPrograms;
    bool _doWmPrograms;
    bool _doTexPrograms;
    bool _doGames;
};

#endif // SETTINGS_H
