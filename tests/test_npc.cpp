#include <gtest/gtest.h>
#include "../include/npc.h"
#include "../include/elf.h"
#include "../include/rogue.h"
#include "../include/knight_errant.h"
#include <memory>

// Тесты создания NPC
TEST(NpcTest, CreateElf) {
    Elf Elf(100, 200, "Mishka");
    
    EXPECT_EQ(Elf.getX(), 100);
    EXPECT_EQ(Elf.getY(), 200);
    EXPECT_EQ(Elf.getName(), "Mishka");
    EXPECT_EQ(Elf.getType(), "Elf");
}

TEST(NpcTest, CreateRogue) {
    Rogue Rogue(150, 250, "Vypochka");
    
    EXPECT_EQ(Rogue.getX(), 150);
    EXPECT_EQ(Rogue.getY(), 250);
    EXPECT_EQ(Rogue.getName(), "Vypochka");
    EXPECT_EQ(Rogue.getType(), "Rogue");
}

TEST(NpcTest, CreateKnightErrant) {
    KnightErrant KnightErrant(50, 75, "Vyhuhol");
    
    EXPECT_EQ(KnightErrant.getX(), 50);
    EXPECT_EQ(KnightErrant.getY(), 75);
    EXPECT_EQ(KnightErrant.getName(), "Vyhuhol");
    EXPECT_EQ(KnightErrant.getType(), "KnightErrant");
}

// Тест расстояния между NPC
TEST(NpcTest, DistanceCalculation) {
    Elf Elf1(0, 0, "Elf1");
    Elf Elf2(3, 4, "Elf2");
    
    // Расстояние должно быть 5 (теорема Пифагора: 3^2 + 4^2 = 25, sqrt(25) = 5)
    EXPECT_DOUBLE_EQ(Elf1.distanceTo(Elf2), 5.0);
}

TEST(NpcTest, DistanceSamePosition) {
    KnightErrant KnightErrant1(100, 100, "KnightErrant1");
    KnightErrant KnightErrant2(100, 100, "KnightErrant2");
    
    EXPECT_DOUBLE_EQ(KnightErrant1.distanceTo(KnightErrant2), 0.0);
}

TEST(NpcTest, DistanceSymmetric) {
    Rogue Rogue(10, 20, "Rogue1");
    Elf Elf(50, 80, "Elf1");
    
    // Расстояние должно быть одинаковым в обе стороны
    EXPECT_DOUBLE_EQ(Rogue.distanceTo(Elf), Elf.distanceTo(Rogue));
}

// Тест координат на границах
TEST(NpcTest, BoundaryCoordinates) {
    Elf Elf1(0, 0, "MinCorner");
    EXPECT_EQ(Elf1.getX(), 0);
    EXPECT_EQ(Elf1.getY(), 0);
    
    Elf Elf2(500, 500, "MaxCorner");
    EXPECT_EQ(Elf2.getX(), 500);
    EXPECT_EQ(Elf2.getY(), 500);
}