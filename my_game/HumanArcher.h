//
// Created by Vladimir on 06.04.2020.
//
#pragma once
#include "Archer.h"

class HumanArcher : public Archer {
  public:
    HumanArcher() {
        std::cout << "HumanArcher created" << std::endl;
    }
};