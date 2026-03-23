#ifndef APP_EXCEPTIONS_H
#define APP_EXCEPTIONS_H

#include <stdexcept>
#include <string>

using namespace std;


class ProjectException : public runtime_error {
public:
    explicit ProjectException(const string& message)
        : runtime_error(message) {}
};

class DataAccessException : public ProjectException {
public:
    explicit DataAccessException(const string& message)
        : ProjectException(message) {}
};

class ValidationException : public ProjectException {
public:
    explicit ValidationException(const string& message)
        : ProjectException(message) {}
};

#endif
