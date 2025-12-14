#pragma once

class Elf;
class Rogue;
class KnightErrant;

class Visitor {
    public:
        virtual ~Visitor() = default;

        // Постелитель к кажому типу NPC
        virtual void visit(Elf& bear) = 0;
        virtual void visit(Rogue& desman) = 0;
        virtual void visit(KnightErrant& bittern) = 0;
};