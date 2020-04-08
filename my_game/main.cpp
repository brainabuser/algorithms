#include "Game.h"
#include "HumanArmyFactory.h"
#include "OrcArmyFactory.h"

int main() {
    Game game;
    while (game.getPlaying()) {
        HumanArmyFactory human_factory;
        OrcArmyFactory orc_factory;
        Army *humans = game.create_army(human_factory);
        Army *orcs = game.create_army(orc_factory);
        game.mainMenu();
    }
    return 0;
}