#include <QCoreApplication>
#include "game.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Game game;
    game.newGame();

    if(!game.saveGame(Game::Json))
        return 1;
    if(!game.saveGame(Game::Binary))
        return 1;

    Game fromJson;
    if(!fromJson.loadGame(Game::Json))
        return 1;

    Game fromBinary;
    if(!fromBinary.loadGame(Game::Binary))
        return 1;

    return 0;
}
