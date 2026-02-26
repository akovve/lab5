#ifndef TASK6_H
#define TASK6_H

#include "task.h"
#include <string>
#include <vector>

namespace file_processor {

// Задание 6: Переписать в другой файл строки, в которых нет русских букв
class Task6 : public Task {
private:
    std::string sourcePath_;
    std::string destPath_;
    std::vector<std::string> lines_;
    
    void loadLines();
    void saveLines(const std::vector<std::string>& lines, const std::string& path) const;
    bool containsRussianLetters(const std::string& text) const;
    void generateRandomText(int lineCount);
    void filterLinesWithoutRussian() const;
    
public:
    Task6(const std::string& source = "text6.txt", 
          const std::string& dest = "filtered6.txt");
    
    void execute() override;
    std::string getName() const override { 
        return "Фильтрация строк без русских букв"; 
    }
    int getNumber() const override { return 6; }
    
    void setParameters(const std::string& source, const std::string& dest) {
        sourcePath_ = source;
        destPath_ = dest;
    }
};

} // namespace file_processor

#endif // TASK6_H