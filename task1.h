#ifndef TASK1_H
#define TASK1_H

#include "task.h"
#include <string>

namespace file_processor {

class Task1 : public Task {
private:
    std::string sourcePath_;
    std::string destPath_;
    int k_;
    
    void fillBinaryFileWithRandomNumbers(int count);
    void printBinaryFileContents(const std::string& description) const;
    void filterMultiples();
    
public:
    Task1(const std::string& source = "numbers1.bin", 
          const std::string& dest = "filtered1.bin", 
          int k = 3);
    
    void execute() override;
    std::string getName() const override { 
        return "Фильтрация кратных чисел в бинарном файле"; 
    }
    int getNumber() const override { return 1; }
    
    void setParameters(const std::string& source, const std::string& dest, int k) {
        sourcePath_ = source;
        destPath_ = dest;
        k_ = k;
    }
};

} // namespace file_processor

#endif // TASK1_H