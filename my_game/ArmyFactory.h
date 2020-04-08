//
// Created by Vladimir on 06.04.2020.
//
#pragma once
#include "Archer.h"
#include "Warrior.h"
#include "Wizard.h"

class ArmyFactory {
  public:
    virtual Archer *createArcher() = 0;
    virtual Warrior *createWarrior() = 0;
    virtual Wizard *createWizard() = 0;
    virtual ~ArmyFactory() {};
};