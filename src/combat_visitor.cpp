#include "../include/combat_visitor.h"

bool CombatVisitor::canKill(Npc* attacker, Npc* defender) {
    if (attacker->getType() == "Elf") {
        return elfVs(defender->getType());
    } else if (attacker->getType() == "Rogue") {
        return rogueVs(defender->getType());
    } else if (attacker->getType() == "KnightErrant") {
        return knight_errantVs(defender->getType());
    }
    return false;
}

bool CombatVisitor::elfVs(const std::string& defenderType) {
    // Эльф убивает рыцарей
    return (defenderType == "KnightErrant");
}

bool CombatVisitor::rogueVs(const std::string& defenderType) {
    // Разбойник убивает эльфов
    return (defenderType == "Elf");
}

bool CombatVisitor::knight_errantVs(const std::string& defenderType) {
    // Рыцарь убивает разбойников
    return (defenderType == "Rogue");
}