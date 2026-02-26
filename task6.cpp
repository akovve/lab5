#include "task6.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

namespace file_processor {

Task6::Task6(const std::string& source, const std::string& dest)
    : sourcePath_(source), destPath_(dest) {
    loadLines();
}

void Task6::loadLines() {
    lines_.clear();
    std::ifstream in_file(sourcePath_);
    if (!in_file) {
        return;
    }
    
    std::string line;
    while (std::getline(in_file, line)) {
        lines_.push_back(line);
    }
    
    in_file.close();
}

void Task6::saveLines(const std::vector<std::string>& lines, const std::string& path) const {
    std::ofstream out_file(path);
    if (!out_file) {
        std::cerr << "Ошибка открытия файла: " << path << std::endl;
        return;
    }
    
    for (const auto& line : lines) {
        out_file << line << std::endl;
    }
    
    out_file.close();
}

bool Task6::containsRussianLetters(const std::string& text) const {
    for (size_t i = 0; i < text.length(); ++i) {
        unsigned char c = static_cast<unsigned char>(text[i]);

        if (c == 0xD0 || c == 0xD1) {
            return true;
        }
    }
    return false;
}

void Task6::generateRandomText(int lineCount) {
    std::vector<std::string> sample_lines = {
        "Hello world!",
        "Добрый день!",
        "This is a test.",
        "Добро дошли.",
        "12345",
        "No russian letters here",
        "А здесь есть русские буквы!!!!!!",
        "Только English",
        "Смешанный mixed текст",
        "C++",
        "Программирование на C++",
        "No cyrillic",
        "Кириллица Мефодица"
    };
    
    lines_.clear();
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    for (int i = 0; i < lineCount; ++i) {
        lines_.push_back(sample_lines[std::rand() % sample_lines.size()]);
    }
    
    saveLines(lines_, sourcePath_);
}

void Task6::filterLinesWithoutRussian() const {
    std::vector<std::string> filtered_lines;
    
    for (const auto& line : lines_) {
        if (!containsRussianLetters(line)) {
            filtered_lines.push_back(line);
        }
    }
    
    saveLines(filtered_lines, destPath_);
}

void Task6::execute() {
    std::cout << "\nЗАДАНИЕ 6: Фильтрация текстового файла" << std::endl;
    std::cout << "Условие: Переписать в другой файл строки, в которых нет русских букв\n" << std::endl;
    
    generateRandomText(15);
    
    std::cout << "Исходный файл (" << sourcePath_ << "):" << std::endl;
    for (const auto& line : lines_) {
        std::cout << line << std::endl;
    }

    std::cout << "\nФильтруем строки без русских букв..." << std::endl;
    filterLinesWithoutRussian();

    std::cout << "\nОтфильтрованный файл (" << destPath_ << "):" << std::endl;
    std::ifstream in_file(destPath_);
    if (in_file) {
        std::string line;
        int count = 0;
        while (std::getline(in_file, line)) {
            std::cout << line << std::endl;
            count++;
        }
        in_file.close();
        
        std::cout << "\nИтого:" << std::endl;
        std::cout << "  Всего строк в исходном файле: " << lines_.size() << std::endl;
        std::cout << "  Скопировано строк без русских букв: " << count << std::endl;
    } else {
        std::cout << "  Файл не найден" << std::endl;
    }
}

} // namespace file_processor