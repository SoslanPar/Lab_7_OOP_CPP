#include "include/arena.h"
#include "include/factory.h"
#include "include/console_observer.h"
#include "include/file_observer.h"
#include <iostream>
#include <memory>

int main() {
    try {
        std::cout << "=== Balagur Fate 3 - Async Battle ===" << std::endl;
        std::cout << std::endl;

        // Размер карты 100x100 как в задании
        Arena arena(100, 100);

        auto consoleObserver = std::make_shared<ConsoleObserver>();
        auto fileObserver = std::make_shared<FileObserver>("log.txt");
        
        arena.addObserver(consoleObserver);
        arena.addObserver(fileObserver);

        std::cout << "Generating 50 random NPCs..." << std::endl;
        arena.generateRandomNpcs(50);
        
        std::cout << "Initial State:" << std::endl;
        arena.printMap();

        std::cout << "Starting game for 30 seconds..." << std::endl;
        arena.startGame(30);

        std::cout << "Game Over!" << std::endl;
        arena.printSurvivors();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}