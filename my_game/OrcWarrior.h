//
// Created by Vladimir on 06.04.2020.
//
#pragma once
#include "Warrior.h"

class OrcWarrior : public Warrior {
  public:
    OrcWarrior() {
        std::cout << "OrcWarrior created" << std::endl;
    }
};