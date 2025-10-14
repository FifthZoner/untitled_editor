//
// Created by fifthzoner on 12/10/2025.
//

#ifndef UNTITLED_EDITOR_ERRORS_HPP
#define UNTITLED_EDITOR_ERRORS_HPP

#include <string>
#include <memory>

#include "../definitions.hpp"

/// <summary>
/// The standard class for error handling
/// And as to why it's done via a unique_ptr:
/// it's probably better to move around 8 bytes instead of something like 16-40 when rarely needed
/// </summary>
class Error {

    std::unique_ptr<const std::string> _errorPtr = nullptr;

public:

    Error() = default;
    explicit Error(std::string message);
    explicit Error(std::string* message);
    Error(const Error& message);
    Error(Error&& message) noexcept;

    Error& operator= (const Error& other);

    [[nodiscard]] std::string message() const;
    [[nodiscard]] bool ok() const;
};

void Warning(std::string message);
void Warning(const char* message);

/// \brief Asserts if condition is true, if it's not displays a warning
/// \param condition Condition to assert as true
/// \param message Message for warning
/// \return Result of condition
bool TrueOrWarning(bool condition, std::string message);

/// \brief Asserts if condition is true, if it's not displays a warning
/// \param condition Condition to assert as true
/// \param message Message for warning
/// \return Result of condition
bool TrueOrWarning(bool condition, const char* message);

#ifdef BUILD_DEBUG
// if the condition doesn't assert to true returns an error, enabled in debug
#define TrueOrUnexpectedExt(condition, message) if (not (condition)) return std::unexpected(Error(message))
// if the condition doesn't assert to true returns an error, enabled in debug
#define TrueOrOptionalExt(condition, message) if (not (condition)) return Error(message)
// if the condition doesn't assert to true displays a warning, returns result of condition, enabled in debug
#define TrueOrWarningExt(condition, message) AssertWarning(condition, message)
#else
// if the condition doesn't assert to true returns an error, disabled in release
#define TrueOrUnexpectedExt(condition, message)
// if the condition doesn't assert to true returns an error, disabled in release
#define TrueOrOptionalExt(condition, message)
// if the condition doesn't assert to true displays a warning, returns result of condition, disabled in release
#define TrueOrWarningExt(condition, message)
#endif

// if the condition doesn't assert to true returns an error
#define TrueOrUnexpected(condition, message) if (not (condition)) return std::unexpected(Error(message))
// if the condition doesn't assert to true returns an error
#define TrueOrOptional(condition, message) if (not (condition)) return Error(message)

#define ERROR_OK "Skip"

#endif //UNTITLED_EDITOR_ERRORS_HPP