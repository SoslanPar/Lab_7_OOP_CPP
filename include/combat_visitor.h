#pragma once
#include "knight_errant.h"
#include "rogue.h"
#include "visitor.h"
#include "npc.h"

class CombatVisitor : public Visitor {
    public:
        bool canKill(Npc* attacker, Npc* defender);

        void visit(Rogue&) override {}
        void visit(Elf&) override {}
        void visit(KnightErrant&) override {}
    private:
        bool elfVs(const std::string& defenderType);
        bool rogueVs(const std::string& defenderType);
        bool knight_errantVs(const std::string&);
};