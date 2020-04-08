//
// Created by Vladimir on 06.04.2020.
//
#pragma once
#include "Warrior.h"

class HumanWarrior : public Warrior {
  public:
    HumanWarrior() {
        std::cout << "HumanWarrior created" << std::endl;
    }
};