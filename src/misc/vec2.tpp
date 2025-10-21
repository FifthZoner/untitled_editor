//
// Created by fifthzoner on 16/10/2025.
//

#ifndef UNTITLED_EDITOR_VEC_2
#define UNTITLED_EDITOR_VEC_2
#include <cstdint>
#include <iostream>

template <typename T>
struct Vec2 {
    T x{};
    T y{};

    Vec2() = default;
    Vec2(const T& x, const T& y) : x(x), y(y) {}
    Vec2(T&& x, const T& y) : x(x), y(y) {}
    Vec2(const T& x, T&& y) : x(x), y(y) {}
    Vec2(T&& x, T&& y) : x(x), y(y) {}
    Vec2(const Vec2& vec2) : x(vec2.x), y(vec2.y) {}
    Vec2(Vec2&& vec2)  noexcept : x(vec2.x), y(vec2.y) {}

    template <typename S>
    explicit Vec2(const Vec2<S>& vec2) noexcept : x(static_cast<S>(vec2.x)), y(static_cast<S>(vec2.y)) {}
    template <typename S>
    explicit Vec2(Vec2<S>&& vec2) noexcept : x(static_cast<S>(vec2.x)), y(static_cast<S>(vec2.y)) {}

    Vec2& operator=(const Vec2& other) = default;
    Vec2& operator=(Vec2&& other) = default;

    template <typename S>
    Vec2<S> to() {return Vec2(static_cast<S>(x), static_cast<S>(y));}

#define VEC2_DOUBLE_OPERATOR_OVERLOAD(OPERATOR) \
    Vec2 operator OPERATOR (const Vec2& other) {\
        this->x = x OPERATOR other.x;           \
        this->y = y OPERATOR other.y;           \
        return *this;                           \
    }                                           \
    Vec2 operator OPERATOR (Vec2&& other) {     \
        this->x = x OPERATOR other.x;           \
        this->y = y OPERATOR other.y;           \
        return *this;                           \
    }
    VEC2_DOUBLE_OPERATOR_OVERLOAD(+)
    VEC2_DOUBLE_OPERATOR_OVERLOAD(-)
    VEC2_DOUBLE_OPERATOR_OVERLOAD(/)
    VEC2_DOUBLE_OPERATOR_OVERLOAD(*)
#undef VEC2_DOUBLE_OPERATOR_OVERLOAD

#define VEC2_SINGLE_OPERATOR_OVERLOAD(OPERATOR) \
    Vec2 operator OPERATOR (const T& other) {   \
    this->x = x OPERATOR other;                 \
    this->y = y OPERATOR other;                 \
    return *this;                               \
    }                                           \
    Vec2 operator OPERATOR (T&& other) {        \
    this->x = x OPERATOR other;                 \
    this->y = y OPERATOR other;                 \
    return *this;                               \
    }
    VEC2_SINGLE_OPERATOR_OVERLOAD(/)
    VEC2_SINGLE_OPERATOR_OVERLOAD(*)
#undef VEC2_SINGLE_OPERATOR_OVERLOAD
};

template<typename T>
std::ostream& operator<<(std::ostream& out, Vec2<T> vec2) {
    return out << "(" << vec2.x << ", " << vec2.y << ")";
}

using Vec2f = Vec2<float>;
using Vec2d = Vec2<double>;
using Vec2u = Vec2<uint32_t>;
using Vec2i = Vec2<int32_t>;

#endif //UNTITLED_EDITOR_VEC_2