#pragma once
#include <string>
#include "npc.h"

class Elf : public Npc {
    public:
        Elf(int x, int y, const std::string& name);

        void accept(Visitor& visitor) override;

        void printInfo() const override;

        int getMoveDistance() const override;
        int getKillDistance() const override;

    private:
        static const std::string kType;
};