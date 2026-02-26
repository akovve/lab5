#ifndef TASK5_H
#define TASK5_H

#include "task.h"
#include <string>
#include <vector>

namespace file_processor {

// Задание 5: Вычислить сумму четных элементов в файле
class Task5 : public Task {
private:
    struct NumberLine {
        std::vector<int> numbers;
        int sumEven() const;
    };
    
    std::string filePath_;
    std::vector<NumberLine> lines_;
    
    void loadLines();
    void saveLines() const;
    void generateRandomLines(int lineCount, int maxNumbersPerLine);
    int sumAllEvenNumbers() const;
    
public:
    Task5(const std::string& filePath = "numbers5.txt");
    
    void execute() override;
    std::string getName() const override { 
        return "Сумма четных элементов в текстовом файле"; 
    }
    int getNumber() const override { return 5; }
    
    void setFilePath(const std::string& filePath) { filePath_ = filePath; }
};

} // namespace file_processor

#endif // TASK5_H