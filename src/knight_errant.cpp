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
    // Специфическая информация для медведя
    std::cout << "KnightErrant Info - Name: " << getName()
              << ", Position: (" << getX() << ", " << getY() << ")"
              << std::endl;
}