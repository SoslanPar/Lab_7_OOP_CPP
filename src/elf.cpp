#include "../include/elf.h"
#include "../include/visitor.h"
#include <iostream>
#include <cmath>
#include <ostream>

Elf::Elf(int x, int y, const std::string& name)
    : Npc(x, y, kType, name) {}

const std::string Elf::kType = "Elf";

void Elf::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void Elf::printInfo() const {
    std::cout << "Elf Info - Name: " << getName()
              << ", Position: (" << getX() << ", " << getY() << ")"
              << std::endl;
}

int Elf::getMoveDistance() const {
    return 10;
}

int Elf::getKillDistance() const {
    return 50;
}