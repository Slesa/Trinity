#include "game.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>

Game::Game()
{
}

const Character& Game::player() const
{
    return mPlayer;
}

const QList<Level>& Game::levels() const
{
    return mLevels;
}

void Game::newGame()
{
    mPlayer = Character();
    mPlayer.setName(QStringLiteral("Hero"));
    mPlayer.setClassType(Character::Archer);
    mPlayer.setLevel(15);

    mLevels.clear();

    Level village;
    QList<Character> villageNpcs;
    villageNpcs.append(Character(QStringLiteral("Barry the Blacksmith"), 10, Character::Warrior));
    villageNpcs.append(Character(QStringLiteral("Terry the Trader"), 10, Character::Warrior));
    village.setNpcs(villageNpcs);
    mLevels.append(village);

    Level dungeon;
    QList<Character> dungeonNpcs;
    dungeonNpcs.append(Character(QStringLiteral("Eric the Evil"), 20, Character::Mage));
    dungeonNpcs.append(Character(QStringLiteral("Eric's Sidekick #1"), 5, Character::Warrior));
    dungeonNpcs.append(Character(QStringLiteral("Eric's Sidekick #2"), 5, Character::Warrior));
    dungeon.setNpcs(dungeonNpcs);
    mLevels.append(dungeon);
}

bool Game::loadGame(SaveFormat saveFormat)
{
    QFile loadFile(saveFormat==Json
                    ? QStringLiteral("save.json")
                    : QStringLiteral("save.dat"));
    if(!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(saveFormat==Json
                          ? QJsonDocument::fromJson(saveData)
                          : QJsonDocument::fromBinaryData(saveData));
    read(loadDoc.object());
    return true;
}

bool Game::saveGame(SaveFormat saveFormat)
{
    QFile saveFile(saveFormat==Json
                   ? QStringLiteral("save.json")
                   : QStringLiteral("save.dat"));
    if(!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject gameObject;
    write(gameObject);
    QJsonDocument saveDoc(gameObject);
    saveFile.write(saveFormat==Json
                   ? saveDoc.toJson()
                   : saveDoc.toBinaryData());
    return true;
}

void Game::read(const QJsonObject &json)
{
    mPlayer.read(json["player"].toObject());

    mLevels.clear();
    QJsonArray levelArray = json["levels"].toArray();
    for(int levelIndex = 0; levelIndex < levelArray.size(); ++levelIndex) {
        QJsonObject levelObject = levelArray[levelIndex].toObject();
        Level level;
        level.read(levelObject);
        mLevels.append(level);
    }
}

void Game::write(QJsonObject &json)
{
    QJsonObject playerObject;
    mPlayer.write(playerObject);
    json["player"] = playerObject;

    QJsonArray levelArray;
    foreach(const Level level, mLevels) {
        QJsonObject levelObject;
        level.write(levelObject);
        levelArray.append(levelObject);
    }
    json["levels"] = levelArray;
}
