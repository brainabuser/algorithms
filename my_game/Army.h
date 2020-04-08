//
// Created by Vladimir on 06.04.2020.
//
#pragma once

#include "Archer.h"
#include "Warrior.h"
#include "Wizard.h"
#include <vector>

class Army {
  private:
    vector<Archer *> m_archer;
    vector<Warrior *> m_warrior;
    vector<Wizard *> m_wizard;
  public:
    void action();
    void add_archer(Archer *pArcher);
    void add_warrior(Warrior *pWarrior);
    void add_wizard(Wizard *pWizard);
    ~Army() {};
};