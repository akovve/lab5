#include "task2.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>

namespace file_processor {


Task2::Matrix::Matrix(size_t n) : size_(n) {
    data_.resize(n, std::vector<int>(n, 0));
}

void Task2::Matrix::setValue(size_t i, size_t j, int value) {
    if (i < size_ && j < size_) {
        data_[i][j] = value;
    }
}

int Task2::Matrix::getValue(size_t i, size_t j) const {
    return (i < size_ && j < size_) ? data_[i][j] : 0;
}

int Task2::Matrix::findColumnFarthestFromZero() const {
    int target_column = -1;
    double max_distance = -1.0;
    
    for (size_t j = 0; j < size_; ++j) {
        long long product = 1;
        bool has_non_zero = false;
        
        for (size_t i = 0; i < size_; ++i) {
            if (data_[i][j] != 0) {
                product *= data_[i][j];
                has_non_zero = true;
            }
        }
        
        if (has_non_zero) {
            double distance = std::abs(static_cast<double>(product));
            if (distance > max_distance) {
                max_distance = distance;
                target_column = static_cast<int>(j) + 1;  // Нумерация с 1
            }
        }
    }
    
    return target_column;
}

void Task2::Matrix::print(const std::string& description) const {
    std::cout << description << ":" << std::endl;
    for (size_t i = 0; i < size_; ++i) {
        std::cout << "  ";
        for (size_t j = 0; j < size_; ++j) {
            std::cout << data_[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}


Task2::Task2(const std::string& filePath, size_t matrixSize)
    : filePath_(filePath), matrixSize_(matrixSize) {}

void Task2::fillFileForMatrix(int count) {
    std::ofstream out_file(filePath_, std::ios::binary);
    if (!out_file) {
        std::cerr << "Ошибка открытия файла: " << filePath_ << std::endl;
        return;
    }
    
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = 0; i < count; ++i) {
        int num = std::rand() % 100 + 1;
        out_file.write(reinterpret_cast<const char*>(&num), sizeof(num));
    }
    
    out_file.close();
}

std::unique_ptr<Task2::Matrix> Task2::createMatrixFromFile() const {
    auto matrix = std::make_unique<Matrix>(matrixSize_);
    
    std::ifstream in_file(filePath_, std::ios::binary);
    if (!in_file) {
        std::cerr << "Ошибка открытия файла: " << filePath_ << std::endl;
        return matrix;
    }
    
    int value;
    for (size_t i = 0; i < matrixSize_; ++i) {
        for (size_t j = 0; j < matrixSize_; ++j) {
            if (in_file.read(reinterpret_cast<char*>(&value), sizeof(value))) {
                matrix->setValue(i, j, value);
            }
        }
    }
    
    in_file.close();
    return matrix;
}

void Task2::execute() {
    std::cout << "\nЗАДАНИЕ 2: Матрица из бинарного файла" << std::endl;
    std::cout << "Условие: Скопировать элементы файла в квадратную матрицу n×n\n"
              << "         и найти столбец, где произведение элементов дальше всего от нуля\n" << std::endl;
    
    int totalElements = matrixSize_ * matrixSize_;
    fillFileForMatrix(totalElements);

    std::cout << "Содержимое файла (" << filePath_ << "):" << std::endl;
    std::ifstream in_file(filePath_, std::ios::binary);
    if (in_file) {
        int num;
        int count = 0;
        while (in_file.read(reinterpret_cast<char*>(&num), sizeof(num))) {
            std::cout << "  " << num;
            if (++count % matrixSize_ == 0) {
                std::cout << std::endl;
            } else {
                std::cout << " ";
            }
        }
        in_file.close();
    }

    auto matrix = createMatrixFromFile();
    matrix->print("Матрица " + std::to_string(matrixSize_) + "x" + std::to_string(matrixSize_));

    int column = matrix->findColumnFarthestFromZero();
    if (column != -1) {
        std::cout << "\nСтолбец с произведением, дальше всего от нуля: " << column << std::endl;
    } else {
        std::cout << "\nНе удалось найти подходящий столбец" << std::endl;
    }
}

} // namespace file_processor