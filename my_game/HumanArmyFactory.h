//
// Created by Vladimir on 06.04.2020.
//
#pragma once

#include "HumanArcher.h"
#include "HumanWarrior.h"
#include "HumanWizard.h"

class HumanArmyFactory : public ArmyFactory {
    HumanArcher *createArcher() {
        return new HumanArcher;
    }

    HumanWarrior *createWarrior() {
        return new HumanWarrior;
    }

    HumanWizard *createWizard() {
        return new HumanWizard;
    }
};