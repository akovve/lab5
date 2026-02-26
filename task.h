#ifndef TASK_H
#define TASK_H

#include <string>

namespace file_processor {

class Task {
public:
    virtual ~Task() = default;
    virtual void execute() = 0;
    virtual std::string getName() const = 0;
    virtual int getNumber() const = 0; 
};

} // namespace file_processor

#endif // TASK_H