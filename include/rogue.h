#pragma once
#include <string>
#include "npc.h"

class Rogue : public Npc {
    public:
        Rogue(int x, int y, const std::string& name);

        void accept(Visitor& visitor) override;

        void printInfo() const override;

        int getMoveDistance() const override;
        int getKillDistance() const override;

    private:
        static const std::string kType;
};