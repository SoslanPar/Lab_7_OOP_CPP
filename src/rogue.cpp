#include "../include/rogue.h"
#include "../include/visitor.h"
#include <iostream>
#include <cmath>
#include <ostream>

Rogue::Rogue(int x, int y, const std::string& name)
    : Npc(x, y, kType, name) {}

const std::string Rogue::kType = "Rogue";

void Rogue::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void Rogue::printInfo() const {
    std::cout << "Rogue Info - Name: " << getName()
              << ", Position: (" << getX() << ", " << getY() << ")"
              << std::endl;
}

int Rogue::getMoveDistance() const {
    return 10;
}

int Rogue::getKillDistance() const {
    return 10;
}