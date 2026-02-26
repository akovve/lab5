#include "task1.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

namespace file_processor {

Task1::Task1(const std::string& source, const std::string& dest, int k)
    : sourcePath_(source), destPath_(dest), k_(k) {}

void Task1::fillBinaryFileWithRandomNumbers(int count) {
    std::ofstream out_file(sourcePath_, std::ios::binary);
    if (!out_file) {
        std::cerr << "Ошибка открытия файла: " << sourcePath_ << std::endl;
        return;
    }
    
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = 0; i < count; ++i) {
        int num = std::rand() % 100 + 1;
        out_file.write(reinterpret_cast<const char*>(&num), sizeof(num));
    }
    
    out_file.close();
}

void Task1::printBinaryFileContents(const std::string& description) const {
    std::cout << description << ":" << std::endl;
    std::ifstream in_file(sourcePath_, std::ios::binary);
    if (!in_file) {
        std::cout << "  Файл не найден" << std::endl;
        return;
    }
    
    int num;
    int count = 0;
    while (in_file.read(reinterpret_cast<char*>(&num), sizeof(num))) {
        std::cout << "  " << num;
        if (++count % 10 == 0) {
            std::cout << std::endl;
        } else {
            std::cout << " ";
        }
    }
    
    if (count % 10 != 0) {
        std::cout << std::endl;
    }
    
    if (count == 0) {
        std::cout << "  Файл пуст" << std::endl;
    } else {
        std::cout << "  Всего элементов: " << count << std::endl;
    }
    
    in_file.close();
}

void Task1::filterMultiples() {
    std::ifstream in_file(sourcePath_, std::ios::binary);
    std::ofstream out_file(destPath_, std::ios::binary);
    
    if (!in_file || !out_file) {
        std::cerr << "Ошибка открытия файлов" << std::endl;
        return;
    }
    
    int num;
    while (in_file.read(reinterpret_cast<char*>(&num), sizeof(num))) {
        if (num % k_ != 0) {
            out_file.write(reinterpret_cast<const char*>(&num), sizeof(num));
        }
    }
    
    in_file.close();
    out_file.close();
}

void Task1::execute() {
    std::cout << "\nЗАДАНИЕ 1: Фильтрация кратных чисел в бинарном файле" << std::endl;
    std::cout << "Условие: Получить в другом файле все компоненты исходного файла,\n"
              << "         кроме тех, которые кратны " << k_ << "\n" << std::endl;

    fillBinaryFileWithRandomNumbers(20);
    printBinaryFileContents("Исходный файл (" + sourcePath_ + ")");

    std::cout << "\nФильтруем числа, кратные " << k_ << "..." << std::endl;
    filterMultiples();
    
    std::cout << "\nОтфильтрованный файл (" << destPath_ << "):" << std::endl;
    std::ifstream in_file(destPath_, std::ios::binary);
    if (in_file) {
        int num;
        int count = 0;
        while (in_file.read(reinterpret_cast<char*>(&num), sizeof(num))) {
            std::cout << "  " << num;
            if (++count % 10 == 0) std::cout << std::endl;
            else std::cout << " ";
        }
        if (count % 10 != 0) std::cout << std::endl;
        if (count == 0) {
            std::cout << "  Файл пуст" << std::endl;
        } else {
            std::cout << "  Всего элементов: " << count << std::endl;
        }
        in_file.close();
    } else {
        std::cout << "  Файл не найден" << std::endl;
    }
}

} // namespace file_processor