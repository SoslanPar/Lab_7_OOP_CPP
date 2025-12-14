#include <gtest/gtest.h>
#include "../include/factory.h"
#include "../include/elf.h"
#include "../include/rogue.h"
#include "../include/knight_errant.h"
#include <memory>

// Тесты фабрики
TEST(FactoryTest, CreateElf) {
    auto Elf = NpcFactory::createNpc("Elf", "TestElf", 100, 200);
    
    ASSERT_NE(Elf, nullptr);
    EXPECT_EQ(Elf->getType(), "Elf");
    EXPECT_EQ(Elf->getName(), "TestElf");
    EXPECT_EQ(Elf->getX(), 100);
    EXPECT_EQ(Elf->getY(), 200);
}

TEST(FactoryTest, CreateRogue) {
    auto Rogue = NpcFactory::createNpc("Rogue", "TestRogue", 150, 250);
    
    ASSERT_NE(Rogue, nullptr);
    EXPECT_EQ(Rogue->getType(), "Rogue");
    EXPECT_EQ(Rogue->getName(), "TestRogue");
}

TEST(FactoryTest, CreateKnightErrant) {
    auto KnightErrant = NpcFactory::createNpc("KnightErrant", "TestKnightErrant", 50, 75);
    
    ASSERT_NE(KnightErrant, nullptr);
    EXPECT_EQ(KnightErrant->getType(), "KnightErrant");
    EXPECT_EQ(KnightErrant->getName(), "TestKnightErrant");
}

TEST(FactoryTest, CreateInvalidType) {
    EXPECT_THROW({
        auto npc = NpcFactory::createNpc("Dragon", "TestDragon", 100, 100);
    }, std::invalid_argument);
}

// Тесты загрузки из строки
TEST(FactoryTest, CreateFromStringElf) {
    std::string line = "Elf Mishka 100 200";
    auto Elf = NpcFactory::createFromString(line);
    
    ASSERT_NE(Elf, nullptr);
    EXPECT_EQ(Elf->getType(), "Elf");
    EXPECT_EQ(Elf->getName(), "Mishka");
    EXPECT_EQ(Elf->getX(), 100);
    EXPECT_EQ(Elf->getY(), 200);
}

TEST(FactoryTest, CreateFromStringRogue) {
    std::string line = "Rogue Vypochka 300 400";
    auto Rogue = NpcFactory::createFromString(line);
    
    ASSERT_NE(Rogue, nullptr);
    EXPECT_EQ(Rogue->getType(), "Rogue");
    EXPECT_EQ(Rogue->getName(), "Vypochka");
    EXPECT_EQ(Rogue->getX(), 300);
    EXPECT_EQ(Rogue->getY(), 400);
}

TEST(FactoryTest, CreateFromStringKnightErrant) {
    std::string line = "KnightErrant Vyhuhol 50 75";
    auto KnightErrant = NpcFactory::createFromString(line);
    
    ASSERT_NE(KnightErrant, nullptr);
    EXPECT_EQ(KnightErrant->getType(), "KnightErrant");
    EXPECT_EQ(KnightErrant->getName(), "Vyhuhol");
}

TEST(FactoryTest, CreateFromStringInvalidFormat) {
    std::string line = "Elf Mishka";  // Нет координат
    EXPECT_THROW({
        auto npc = NpcFactory::createFromString(line);
    }, std::runtime_error);
}

TEST(FactoryTest, CreateFromStringInvalidType) {
    std::string line = "Wolf Wolfie 100 200";
    EXPECT_THROW({
        auto npc = NpcFactory::createFromString(line);
    }, std::invalid_argument);
}

TEST(FactoryTest, CreateFromStringEmptyLine) {
    std::string line = "";
    EXPECT_THROW({
        auto npc = NpcFactory::createFromString(line);
    }, std::runtime_error);
}