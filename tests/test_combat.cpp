#include <gtest/gtest.h>
#include "../include/combat_visitor.h"
#include "../include/arena.h"
#include "../include/factory.h"
#include "../include/console_observer.h"
#include "../include/file_observer.h"
#include <memory>
#include <fstream>

// Тесты боевой системы
TEST(CombatTest, ElfVsElf) {
    CombatVisitor visitor;
    auto Elf1 = NpcFactory::createNpc("Elf", "Elf1", 0, 0);
    auto Elf2 = NpcFactory::createNpc("Elf", "Elf2", 10, 10);
    
    // Медведь не атакует медведя
    EXPECT_FALSE(visitor.canKill(Elf1.get(), Elf2.get()));
    EXPECT_FALSE(visitor.canKill(Elf2.get(), Elf1.get()));
}

TEST(CombatTest, ElfVsRogue) {
    CombatVisitor visitor;
    auto Elf = NpcFactory::createNpc("Elf", "Elf1", 0, 0);
    auto Rogue = NpcFactory::createNpc("Rogue", "Rogue", 10, 10);
    
    // Медведь ест выпь
    EXPECT_TRUE(visitor.canKill(Elf.get(), Rogue.get()));
    // Выпь не атакует
    EXPECT_FALSE(visitor.canKill(Rogue.get(), Elf.get()));
}

TEST(CombatTest, ElfVsKnightErrant) {
    CombatVisitor visitor;
    auto Elf = NpcFactory::createNpc("Elf", "Elf1", 0, 0);
    auto KnightErrant = NpcFactory::createNpc("KnightErrant", "KnightErrant1", 10, 10);
    
    // Медведь ест выхухоль
    EXPECT_TRUE(visitor.canKill(Elf.get(), KnightErrant.get()));
    // Выхухоль убивает медведя
    EXPECT_TRUE(visitor.canKill(KnightErrant.get(), Elf.get()));
}

TEST(CombatTest, RogueVsAnyone) {
    CombatVisitor visitor;
    auto Rogue = NpcFactory::createNpc("Rogue", "Rogue1", 0, 0);
    auto Elf = NpcFactory::createNpc("Elf", "Elf1", 10, 10);
    auto KnightErrant = NpcFactory::createNpc("KnightErrant", "KnightErrant1", 20, 20);
    
    // Выпь никого не атакует
    EXPECT_FALSE(visitor.canKill(Rogue.get(), Elf.get()));
    EXPECT_FALSE(visitor.canKill(Rogue.get(), KnightErrant.get()));
    EXPECT_FALSE(visitor.canKill(Rogue.get(), Rogue.get()));
}

TEST(CombatTest, KnightErrantVsElf) {
    CombatVisitor visitor;
    auto KnightErrant = NpcFactory::createNpc("KnightErrant", "KnightErrant1", 0, 0);
    auto Elf = NpcFactory::createNpc("Elf", "Elf1", 10, 10);
    
    // Выхухоль убивает медведя
    EXPECT_TRUE(visitor.canKill(KnightErrant.get(), Elf.get()));
}

TEST(CombatTest, KnightErrantVsRogue) {
    CombatVisitor visitor;
    auto KnightErrant = NpcFactory::createNpc("KnightErrant", "KnightErrant1", 0, 0);
    auto Rogue = NpcFactory::createNpc("Rogue", "Rogue1", 10, 10);
    
    // Выхухоль не атакует выпь
    EXPECT_FALSE(visitor.canKill(KnightErrant.get(), Rogue.get()));
}

TEST(CombatTest, KnightErrantVsKnightErrant) {
    CombatVisitor visitor;
    auto KnightErrant1 = NpcFactory::createNpc("KnightErrant", "KnightErrant1", 0, 0);
    auto KnightErrant2 = NpcFactory::createNpc("KnightErrant", "KnightErrant2", 10, 10);
    
    // Выхухоль не атакует выхухоль
    EXPECT_FALSE(visitor.canKill(KnightErrant1.get(), KnightErrant2.get()));
}

// Тесты боевого режима на арене
TEST(CombatTest, BattleOutOfRange) {
    Arena arena;
    auto observer = std::make_shared<ConsoleObserver>();
    arena.addObserver(observer);
    
    // NPC далеко друг от друга
    arena.addNpc(NpcFactory::createNpc("Elf", "Elf1", 0, 0));
    arena.addNpc(NpcFactory::createNpc("Rogue", "Rogue1", 400, 400));
    
    EXPECT_EQ(arena.getNpcCount(), 2);
    
    // Дальность боя 100 - NPC не достают друг до друга
    arena.startBattle(100.0);
    
    // Оба должны выжить
    EXPECT_EQ(arena.getNpcCount(), 2);
}

TEST(CombatTest, BattleInRange) {
    Arena arena;
    auto observer = std::make_shared<ConsoleObserver>();
    arena.addObserver(observer);
    
    // Медведь и выпь близко
    arena.addNpc(NpcFactory::createNpc("Elf", "Elf1", 100, 100));
    arena.addNpc(NpcFactory::createNpc("Rogue", "Rogue1", 110, 110));
    
    EXPECT_EQ(arena.getNpcCount(), 2);
    
    // Дальность боя 50 метров
    arena.startBattle(50.0);
    
    // Медведь убивает выпь
    EXPECT_EQ(arena.getNpcCount(), 1);
}

TEST(CombatTest, MutualKill) {
    Arena arena;
    auto observer = std::make_shared<ConsoleObserver>();
    arena.addObserver(observer);
    
    // Медведь и выхухоль близко
    arena.addNpc(NpcFactory::createNpc("Elf", "Elf1", 100, 100));
    arena.addNpc(NpcFactory::createNpc("KnightErrant", "KnightErrant1", 105, 105));
    
    EXPECT_EQ(arena.getNpcCount(), 2);
    
    // Дальность боя 50 метров
    arena.startBattle(50.0);
    
    // Оба убивают друг друга
    EXPECT_EQ(arena.getNpcCount(), 0);
}

TEST(CombatTest, ComplexBattle) {
    Arena arena;
    auto observer = std::make_shared<ConsoleObserver>();
    arena.addObserver(observer);
    
    // Создаём группу NPC
    arena.addNpc(NpcFactory::createNpc("Elf", "Elf1", 100, 100));
    arena.addNpc(NpcFactory::createNpc("Elf", "Elf2", 110, 110));
    arena.addNpc(NpcFactory::createNpc("Rogue", "Rogue1", 105, 105));
    arena.addNpc(NpcFactory::createNpc("KnightErrant", "KnightErrant1", 115, 115));
    
    EXPECT_EQ(arena.getNpcCount(), 4);
    
    // Запускаем бой с большой дальностью
    arena.startBattle(100.0);
    
    // Медведи убивают выпь, выхухоль убивает медведей, медведи убивают выхухоль
    // Должен остаться 0 или минимум NPC
    EXPECT_LE(arena.getNpcCount(), 2);
}

TEST(CombatTest, ElfsSurviveAlone) {
    Arena arena;
    auto observer = std::make_shared<ConsoleObserver>();
    arena.addObserver(observer);
    
    // Только медведи
    arena.addNpc(NpcFactory::createNpc("Elf", "Elf1", 100, 100));
    arena.addNpc(NpcFactory::createNpc("Elf", "Elf2", 110, 110));
    arena.addNpc(NpcFactory::createNpc("Elf", "Elf3", 120, 120));
    
    EXPECT_EQ(arena.getNpcCount(), 3);
    
    arena.startBattle(100.0);
    
    // Медведи не атакуют друг друга - все выживают
    EXPECT_EQ(arena.getNpcCount(), 3);
}

TEST(CombatTest, FileObserverLogging) {
    std::string logfile = "test_combat_log.txt";
    
    Arena arena;
    auto observer = std::make_shared<FileObserver>(logfile);
    arena.addObserver(observer);
    
    arena.addNpc(NpcFactory::createNpc("Elf", "Elf1", 100, 100));
    arena.addNpc(NpcFactory::createNpc("Rogue", "Rogue1", 110, 110));
    
    arena.startBattle(50.0);
    
    // Проверяем что файл создан
    std::ifstream file(logfile);
    ASSERT_TRUE(file.is_open());
    
    std::string line;
    bool hasContent = false;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            hasContent = true;
            break;
        }
    }
    file.close();
    
    EXPECT_TRUE(hasContent);
    
    // Удаляем тестовый файл
    std::remove(logfile.c_str());
}