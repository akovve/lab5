#ifndef TASK4_H
#define TASK4_H

#include "task.h"
#include <string>
#include <vector>

namespace file_processor {

// Задание 4: В текстовом файле найти сумму максимального и минимального элементов
class Task4 : public Task {
private:
    std::string filePath_;
    std::vector<int> numbers_;
    
    void loadNumbers();
    void saveNumbers() const;
    void generateRandomNumbers(int count);
    int findSumOfMinMax() const;
    
public:
    Task4(const std::string& filePath = "numbers4.txt");
    
    void execute() override;
    std::string getName() const override { 
        return "Сумма максимального и минимального в текстовом файле"; 
    }
    int getNumber() const override { return 4; }
    
    void setFilePath(const std::string& filePath) { filePath_ = filePath; }
};

} // namespace file_processor

#endif // TASK4_H