//
// Created by Vladimir on 05.04.2020.
//
#pragma once
#ifndef MY_GAME_CHARACTER_H
#define MY_GAME_CHARACTER_H

#include <iostream>

using namespace std;

class Character {
  private:
    int health;
    int armor;
    int luck;
    int mana;
    int damage;
  public:
    Character();
    virtual ~Character();

    //Accessors
    inline const int &getHP() { return this->health; }
    inline const int &getArm() { return this->armor; }
    inline const int &getLuck() { return this->luck; }
    inline const int &getMana() { return this->mana; }
    inline const int &getDmg() { return this->damage; }
};

#endif //MY_GAME_CHARACTER_H
