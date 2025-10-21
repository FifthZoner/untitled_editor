#include "errors.hpp"

#include <iostream>

Error::Error(std::string message) {
    _errorPtr = std::make_unique<const std::string>(message);
}

Error::Error(std::string* message) {
    if (message == nullptr)
        _errorPtr = nullptr;
    else
        _errorPtr = std::make_unique<const std::string>(*message);
}

Error::Error(const Error& message) {
    if (message._errorPtr != nullptr)
        _errorPtr = std::make_unique<const std::string>(*message._errorPtr);
    else _errorPtr = nullptr;
}

Error::Error(Error&& message) noexcept {
    if (message._errorPtr == nullptr)
        _errorPtr = nullptr;
    else
        _errorPtr = std::move(message._errorPtr);
}

Error& Error::operator=(const Error& other) {
    if (other._errorPtr == nullptr)
        this->_errorPtr = nullptr;
    else
        this->_errorPtr = std::make_unique<std::string>(*other._errorPtr);
    return *this;
}

std::string Error::message() const {
    if (_errorPtr == nullptr)
        return ERROR_OK;
    return *_errorPtr;
}

bool Error::ok() const {
    return _errorPtr == nullptr or *_errorPtr == ERROR_OK;
}

std::ostream& operator<<(std::ostream& out, const Error& error) {
    return out << error.message();
}

void Warning(std::string message) {
    std::cout << "Warning: " << message << "\n";
}

void Warning(const char* message) {
    std::cout << "Warning: " << message << "\n";
}

bool TrueOrWarning(bool condition, std::string message) {
    if (not condition)
        std::cout << "Warning: " << message << "\n";
    return condition;
}

bool TrueOrWarning(bool condition, const char* message) {
    if (not condition)
        std::cout << "Warning: " << message << "\n";
    return condition;
}