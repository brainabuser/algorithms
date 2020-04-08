//
// Created by Vladimir on 06.04.2020.
//
#pragma once

#include "OrcArcher.h"
#include "OrcWarrior.h"
#include "OrcWizard.h"

class OrcArmyFactory : public ArmyFactory {
    OrcArcher *createArcher() {
        return new OrcArcher;
    }

    OrcWarrior *createWarrior() {
        return new OrcWarrior;
    }

    OrcWizard *createWizard() {
        return new OrcWizard;
    }
};