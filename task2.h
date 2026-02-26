#ifndef TASK2_H
#define TASK2_H

#include "task.h"
#include <string>
#include <vector>
#include <memory>

namespace file_processor {

// Задание 2: Указать столбец, где произведение элементов дальше всего от нуля
class Task2 : public Task {
private:
    class Matrix {
    private:
        std::vector<std::vector<int>> data_;
        size_t size_;
        
    public:
        Matrix(size_t n);
        void setValue(size_t i, size_t j, int value);
        int getValue(size_t i, size_t j) const;
        size_t getSize() const { return size_; }
        int findColumnFarthestFromZero() const;
        void print(const std::string& description) const;
    };
    
    std::string filePath_;
    size_t matrixSize_;
    
    std::unique_ptr<Matrix> createMatrixFromFile() const;
    void fillFileForMatrix(int count);
    
public:
    Task2(const std::string& filePath = "numbers2.bin", size_t matrixSize = 3);
    
    void execute() override;
    std::string getName() const override { 
        return "Матрица и поиск столбца с максимальным произведением"; 
    }
    int getNumber() const override { return 2; }
    
    void setParameters(const std::string& filePath, size_t matrixSize) {
        filePath_ = filePath;
        matrixSize_ = matrixSize;
    }
};

} // namespace file_processor

#endif // TASK2_H