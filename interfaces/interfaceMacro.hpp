//
// Created by fifthzoner on 19/10/2025.
//

#ifndef UNTITLED_EDITOR_INTERFACE_MACRO_HPP
#define UNTITLED_EDITOR_INTERFACE_MACRO_HPP

#define _INTERFACE_GET_BOTH_INTERNAL(type, name) type name
#define _INTERFACE_GET_TYPES_INTERNAL(type, name) type
#define _INTERFACE_GET_NAMES_INTERNAL(type, name) name
#define _INTERFACE_PLACE_CONTENT(name, content) _##content
#define _INTERFACE_PLACE_NULLPTR_CHECK(name, content) \
if (_##name == nullptr) \
    return Error(std::string("Interface function: \"") + #name + "\" cannot be a nullptr!");
#define _COMMA ,
#define _NEWLINE \

#define _FOREACH_2_INT_19(macro, separator, arg1, arg2, ...) _##macro(arg1, arg2) __VA_OPT__(<<E><R><R><O><R>>"Max defined loop length reached!"<<E><R><R><O><R>>)
#define _FOREACH_2_INT_18(macro, separator, arg1, arg2, ...) _##macro(arg1, arg2) __VA_OPT__(_##separator) __VA_OPT__(_FOREACH_2_INT_19(macro, separator, __VA_ARGS__))
#define _FOREACH_2_INT_17(macro, separator, arg1, arg2, ...) _##macro(arg1, arg2) __VA_OPT__(_##separator) __VA_OPT__(_FOREACH_2_INT_18(macro, separator, __VA_ARGS__))
#define _FOREACH_2_INT_16(macro, separator, arg1, arg2, ...) _##macro(arg1, arg2) __VA_OPT__(_##separator) __VA_OPT__(_FOREACH_2_INT_17(macro, separator, __VA_ARGS__))
#define _FOREACH_2_INT_15(macro, separator, arg1, arg2, ...) _##macro(arg1, arg2) __VA_OPT__(_##separator) __VA_OPT__(_FOREACH_2_INT_16(macro, separator, __VA_ARGS__))
#define _FOREACH_2_INT_14(macro, separator, arg1, arg2, ...) _##macro(arg1, arg2) __VA_OPT__(_##separator) __VA_OPT__(_FOREACH_2_INT_15(macro, separator, __VA_ARGS__))
#define _FOREACH_2_INT_13(macro, separator, arg1, arg2, ...) _##macro(arg1, arg2) __VA_OPT__(_##separator) __VA_OPT__(_FOREACH_2_INT_14(macro, separator, __VA_ARGS__))
#define _FOREACH_2_INT_12(macro, separator, arg1, arg2, ...) _##macro(arg1, arg2) __VA_OPT__(_##separator) __VA_OPT__(_FOREACH_2_INT_13(macro, separator, __VA_ARGS__))
#define _FOREACH_2_INT_11(macro, separator, arg1, arg2, ...) _##macro(arg1, arg2) __VA_OPT__(_##separator) __VA_OPT__(_FOREACH_2_INT_12(macro, separator, __VA_ARGS__))
#define _FOREACH_2_INT_10(macro, separator, arg1, arg2, ...) _##macro(arg1, arg2) __VA_OPT__(_##separator) __VA_OPT__(_FOREACH_2_INT_11(macro, separator, __VA_ARGS__))
#define  _FOREACH_2_INT_9(macro, separator, arg1, arg2, ...) _##macro(arg1, arg2) __VA_OPT__(_##separator) __VA_OPT__(_FOREACH_2_INT_10(macro, separator, __VA_ARGS__))
#define  _FOREACH_2_INT_8(macro, separator, arg1, arg2, ...) _##macro(arg1, arg2) __VA_OPT__(_##separator) __VA_OPT__(_FOREACH_2_INT_9(macro, separator, __VA_ARGS__))
#define  _FOREACH_2_INT_7(macro, separator, arg1, arg2, ...) _##macro(arg1, arg2) __VA_OPT__(_##separator) __VA_OPT__(_FOREACH_2_INT_8(macro, separator, __VA_ARGS__))
#define  _FOREACH_2_INT_6(macro, separator, arg1, arg2, ...) _##macro(arg1, arg2) __VA_OPT__(_##separator) __VA_OPT__(_FOREACH_2_INT_7(macro, separator, __VA_ARGS__))
#define  _FOREACH_2_INT_5(macro, separator, arg1, arg2, ...) _##macro(arg1, arg2) __VA_OPT__(_##separator) __VA_OPT__(_FOREACH_2_INT_6(macro, separator, __VA_ARGS__))
#define  _FOREACH_2_INT_4(macro, separator, arg1, arg2, ...) _##macro(arg1, arg2) __VA_OPT__(_##separator) __VA_OPT__(_FOREACH_2_INT_5(macro, separator, __VA_ARGS__))
#define  _FOREACH_2_INT_3(macro, separator, arg1, arg2, ...) _##macro(arg1, arg2) __VA_OPT__(_##separator) __VA_OPT__(_FOREACH_2_INT_4(macro, separator, __VA_ARGS__))
#define  _FOREACH_2_INT_2(macro, separator, arg1, arg2, ...) _##macro(arg1, arg2) __VA_OPT__(_##separator) __VA_OPT__(_FOREACH_2_INT_3(macro, separator, __VA_ARGS__))
#define  _FOREACH_2_INT_1(macro, separator, arg1, arg2, ...) _##macro(arg1, arg2) __VA_OPT__(_##separator) __VA_OPT__(_FOREACH_2_INT_2(macro, separator, __VA_ARGS__))
// starts a loop on variadic arguments, pass the macro and separator without the leading _, it will be added later
#define         FOREACH_2(macro, separator, arg1, arg2, ...) _##macro(arg1, arg2) __VA_OPT__(_##separator) __VA_OPT__(_FOREACH_2_INT_1(macro, separator, __VA_ARGS__))

// gets types of parameters separated by commas as in: type, type, ...
#define _INTERFACE_GET_TYPES(...) FOREACH_2(INTERFACE_GET_TYPES_INTERNAL, COMMA, __VA_ARGS__)
// gets names of parameters separated by commas as in: name, name, ...
#define _INTERFACE_GET_NAMES(...) FOREACH_2(INTERFACE_GET_NAMES_INTERNAL, COMMA, __VA_ARGS__)
// gets names and types of parameters separated by commas after as in: type name, type name, ...
#define _INTERFACE_GET_BOTH(...) FOREACH_2(INTERFACE_GET_BOTH_INTERNAL, COMMA, __VA_ARGS__)

// allows for commas to be used inside the macro in <..., ...> style
#define _COMMA_WRAPPER(...) __VA_ARGS__

// TODO: for arguments something like this will be needed so that commas in types get preserved
#define ARG(...) COMMA_WRAPPER(_NOT_LAST) _LAST

// defines an interface function, use ONLY as arguments for INTERFACE macro
// argument passing like: returnType, name, arg1Type, arg1Name, arg2Type, arg2Name, ...
#define INTERFACE_FUNCTION(returnType, name, ...) name, COMMA_WRAPPER(                                                   \
    private:                                                                                                             \
        std::function<returnType(_INTERFACE_GET_TYPES(__VA_ARGS__))> _##name = nullptr;                                  \
    public:                                                                                                              \
        void set##name(std::nullptr_t) = delete;                                                                         \
        constexpr inline void set##name(std::function<returnType(_INTERFACE_GET_TYPES(__VA_ARGS__))> func) {             \
            _##name = std::move(func);                                                                                   \
        }                                                                                                                \
        inline std::expected<returnType, Error> name(_INTERFACE_GET_BOTH(__VA_ARGS__)) const {                           \
            try {                                                                                                        \
                return _##name(_INTERFACE_GET_NAMES(__VA_ARGS__));                                                       \
            }                                                                                                            \
            catch (...) {                                                                                                \
                return Error(std::string("Interface function call of: ") + #returnType + " " + #name + "(...) failed!"); \
            }                                                                                                            \
        })

// defines a new interface of given type, named <name>Interface with given member functions
#define INTERFACE(name, ...)                                                                         \
    struct name##Interface {                                                                         \
        FOREACH_2(INTERFACE_PLACE_CONTENT, NEWLINE, __VA_ARGS__)                                     \
        inline std::optional<Error> isValid() {                                                      \
        FOREACH_2(INTERFACE_PLACE_NULLPTR_CHECK, NEWLINE, __VA_ARGS__)                               \
            return std::nullopt;                                                                     \
        }                                                                                            \
};

#endif //UNTITLED_EDITOR_INTERFACE_MACRO_HPP