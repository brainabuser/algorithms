//
// Created by Vladimir on 06.04.2020.
//

#include "Army.h"

void Army::add_archer(Archer *pArcher) {
    m_archer.push_back(pArcher);
}

void Army::add_warrior(Warrior *pWarrior) {
    m_warrior.push_back(pWarrior);
}

void Army::add_wizard(Wizard *pWizard) {
    m_wizard.push_back(pWizard);
}
