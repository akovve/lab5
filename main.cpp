#include <iostream>
#include <memory>
#include <vector>
#include <limits>
#include <cstdlib>

// Заголовочные файлы заданий
#include "task.h"
#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "task4.h"
#include "task5.h"
#include "task6.h"

using namespace file_processor;

void initRussianLocale() {
#ifdef _WIN32
    system("chcp 65001 > nul");
#else
    setlocale(LC_ALL, "ru_RU.UTF-8");
#endif
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void displayMenu() {
    std::cout << "\nЛАБОРАТОРНАЯ РАБОТА №5 - РАБОТА С ФАЙЛАМИ\n";
    
    std::cout << "\nВЫБЕРИТЕ ЗАДАНИЕ ДЛЯ ВЫПОЛНЕНИЯ:\n";
    std::cout << "\n 1. Задание 1: Фильтрация кратных чисел в бинарном файле\n";
    std::cout << " 2. Задание 2: Матрица и поиск столбца с максимальным произведением\n";
    std::cout << " 3. Задание 3: Поиск игрушек для 3-летнего ребенка (кроме мяча)\n";
    std::cout << " 4. Задание 4: Сумма максимального и минимального в текстовом файле\n";
    std::cout << " 5. Задание 5: Сумма четных элементов в текстовом файле\n";
    std::cout << " 6. Задание 6: Фильтрация строк без русских букв\n";
    std::cout << " 7. ВЫПОЛНИТЬ ВСЕ ЗАДАНИЯ\n";
    std::cout << " 0. ВЫХОД\n\n";
    std::cout << "Ваш выбор (0-7): ";
}

// Функция для ожидания нажатия Enter
void waitForEnter() {
    std::cout << "\nНажмите Enter для продолжения...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

int main() {
    initRussianLocale();
    
    // Создаем вектор с заданиями
    std::vector<std::unique_ptr<Task>> tasks;
    
    // Инициализируем все задания
    tasks.push_back(std::make_unique<Task1>());
    tasks.push_back(std::make_unique<Task2>());
    tasks.push_back(std::make_unique<Task3>());
    tasks.push_back(std::make_unique<Task4>());
    tasks.push_back(std::make_unique<Task5>());
    tasks.push_back(std::make_unique<Task6>());
    
    int choice = -1;
    
    while (choice != 0) {
        clearScreen();
        displayMenu();
        std::cin >> choice;
        
        // Очищаем буфер ввода
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case 0:
                std::cout << "\nВыход из программы...\n";
                break;
                
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                if (choice - 1 < static_cast<int>(tasks.size())) {
                    clearScreen();
                    std::cout << "          ЗАДАНИЕ " << choice << ": ";
                    std::cout << tasks[choice - 1]->getName() << "\n";
                    
                    tasks[choice - 1]->execute();
                    waitForEnter();
                }
                break;
                
            case 7:
                clearScreen();
                std::cout << "          ВЫПОЛНЕНИЕ ВСЕХ ЗАДАНИЙ\n";
                
                for (size_t i = 0; i < tasks.size(); i++) {
                    std::cout << "\n" << std::string(60, '=') << "\n";
                    std::cout << "ЗАДАНИЕ " << (i + 1) << ": " 
                              << tasks[i]->getName() << "\n";
                    std::cout << std::string(60, '=') << "\n\n";
                    
                    tasks[i]->execute();
                    
                    if (i < tasks.size() - 1) {
                        std::cout << "\n\n";
                        std::cout << "Нажмите Enter для перехода к следующему заданию...";
                        std::cin.get();
                        clearScreen();
                    }
                }
                
                std::cout << "\nВсе задания выполнены\n";
                waitForEnter();
                break;
                
            default:
                std::cout << "\nОшибка: неверный выбор.\n";
                waitForEnter();
                break;
        }
    }
    
    return 0;
}