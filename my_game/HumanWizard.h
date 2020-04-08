//
// Created by Vladimir on 06.04.2020.
//
#pragma once
#include "Wizard.h"

class HumanWizard : public Wizard {
  public:
    HumanWizard() {
        std::cout << "HumanWizard created" << std::endl;
    }
};