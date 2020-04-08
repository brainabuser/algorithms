//
// Created by Vladimir on 06.04.2020.
//
#pragma once
#ifndef MY_GAME_GAME_H
#define MY_GAME_GAME_H

#include <iostream>
#include "Army.h"
#include "ArmyFactory.h"

using namespace std;

class Game {
  private:
    bool playing;
    int choice;
  public:
    Game();
    virtual ~Game();
    //Functions
    void mainMenu();
    Army *create_army(ArmyFactory &factory);
    //Accessors
    inline bool getPlaying() { return this->playing; }
};

#endif //MY_GAME_GAME_H
