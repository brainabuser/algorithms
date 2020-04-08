//
// Created by Vladimir on 06.04.2020.
//
#pragma once

#include "Wizard.h"

class OrcWizard : public Wizard {
  public:
    OrcWizard() {
        std::cout << "OrcWizard created" << std::endl;
    }
};