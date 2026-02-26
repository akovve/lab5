#ifndef TASK3_H
#define TASK3_H

#include "task.h"
#include <string>
#include <vector>

namespace file_processor {

class Toy {
private:
    std::string name_;
    double price_;
    int minAge_;
    int maxAge_;
    
public:
    Toy(const std::string& name = "", double price = 0.0, int minAge = 0, int maxAge = 0);
    
    const std::string& getName() const { return name_; }
    double getPrice() const { return price_; }
    int getMinAge() const { return minAge_; }
    int getMaxAge() const { return maxAge_; }
    
    bool isSuitableForAge(int age) const;
    std::string toString() const;
};

class Task3 : public Task {
private:
    std::string filePath_;
    std::vector<Toy> toys_;
    
    void loadToys();
    void saveToys() const;
    void generateRandomToys(int count);
    
public:
    Task3(const std::string& filePath = "toys.bin");
    
    void execute() override;
    std::string getName() const override { 
        return "Поиск игрушек для 3-летнего ребенка (кроме мяча)"; 
    }
    int getNumber() const override { return 3; }
    
    void addToy(const Toy& toy);
    bool findToyForThreeYearOld() const;
    
    void setFilePath(const std::string& filePath) { filePath_ = filePath; }
};

} // namespace file_processor

#endif // TASK3_H