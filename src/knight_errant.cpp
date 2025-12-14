#include "../include/knight_errant.h"
#include "../include/visitor.h"
#include <iostream>
#include <cmath>
#include <ostream>

KnightErrant::KnightErrant(int x, int y, const std::string& name)
    : Npc(x, y, kType, name) {}

const std::string KnightErrant::kType = "KnightErrant";

void KnightErrant::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void KnightErrant::printInfo() const {
    std::cout << "KnightErrant Info - Name: " << getName()
              << ", Position: (" << getX() << ", " << getY() << ")"
              << std::endl;
}

int KnightErrant::getMoveDistance() const {
    return 30;
}

int KnightErrant::getKillDistance() const {
    return 10;
}