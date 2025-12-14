#include <memory>
#include <iostream>
#include "../include/factory.h"
#include "../include/rogue.h"
#include "../include/elf.h"
#include "../include/knight_errant.h"
#include <sstream>
#include <stdexcept>

std::unique_ptr<Npc> NpcFactory::createNpc(
    const std::string& type,
    const std::string& name,
    int x,
    int y)
    {
        if (type == "Rogue") {
            return std::make_unique<Rogue>(x, y, name);
        } else if (type == "KnightErrant") {
            return std::make_unique<KnightErrant>(x, y, name);
        } else if (type == "Elf") {
            return std::make_unique<Elf>(x, y, name);
        } else {
            throw std::invalid_argument("Unknown NPC type: " + type);
        }   
    }

std::unique_ptr<Npc> NpcFactory::createFromString(const std::string& line) {
    std::istringstream iss(line);
    std::string type, name;
    int x, y;

    iss >> type >> name >> x >> y;
    
    if (iss.fail()) {
        throw std::runtime_error("Failed to read line: " + line);
    }

    return createNpc(type, name, x ,y);
}