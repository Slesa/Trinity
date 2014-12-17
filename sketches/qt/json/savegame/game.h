#ifndef GAME_H
#define GAME_H

#include <QJsonObject>
#include <QList>

#include "character.h"
#include "level.h"

class Game
{
public:
    Game();

    enum SaveFormat {
        Json, Binary
    };

    const Character& player() const;
    const QList<Level>& levels() const;

    void newGame();
    bool loadGame(SaveFormat saveFormat);
    bool saveGame(SaveFormat saveFormat);

    void read(const QJsonObject& json);
    void write(QJsonObject& json);

private:
    Character mPlayer;
    QList<Level> mLevels;
};

#endif // GAME_H
