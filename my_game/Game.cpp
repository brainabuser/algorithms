//
// Created by Vladimir on 06.04.2020.
//

#include "Game.h"

Game::Game() {
    playing = true;
}

Game::~Game() {
    cout << "End of the game" << endl;
}

//Functions

void Game::mainMenu() {
    cout << "MAIN MENU" << "\n\n";
    cout << "0: Quit" << endl;
    cout << endl << "Choice: " << endl;
    cin >> choice;
    switch (choice) {
        case 0:
            playing = false;
            break;
    }
}

Army *Game::create_army(ArmyFactory &factory) {
    Army *ptr = new Army;
    ptr->add_archer(factory.createArcher());
    ptr->add_warrior(factory.createWarrior());
    ptr->add_wizard(factory.createWizard());
    return ptr;
}

