#ifndef _SOL_VEC2_HPP__
#define _SOL_VEC2_HPP__

#include <cmath>
#include <limits>
#include <string>
#include <string_view>
#include <utility>

namespace sol::math
{
    template <typename Type>
    class vec2
    {
      public:
        constexpr vec2() noexcept
        {
            x = y = 0;
        }

        constexpr vec2(Type x, Type y) noexcept
        {
            this->x = x;
            this->y = y;
        }

        constexpr explicit vec2(Type v) noexcept
        {
            this->x = this->y = v;
        }

        constexpr explicit vec2(Type* data) noexcept
        {
            this->data = data;
        }

        constexpr vec2(const vec2& other) noexcept
        {
            this->data = const_cast<Type*>(other.data);
        }

        constexpr vec2(vec2&& other) noexcept
        {
            this->data[0] = std::move(other.data[0]);
            this->data[1] = std::move(other.data[1]);
        }

        static constexpr vec2 zero() noexcept
        {
            return vec2(0, 0);
        }

        constexpr void set(Type x, Type y) noexcept
        {
            this->x = x;
            this->y = y;
        }

        void set(Type* data) noexcept
        {
            this->data[0] = data[0];
            this->data[1] = data[1];
        }

        inline constexpr bool operator==(const vec2& other) const noexcept
        {
            return x == other.x && y == other.y;
        }

        inline constexpr bool operator!=(const vec2& other) const noexcept
        {
            return x != other.x || y != other.y;
        }

        constexpr vec2& operator=(const vec2& other) noexcept
        {
            set(const_cast<Type*>(other.data));

            return *this;
        }

        constexpr vec2& operator=(vec2&& other) noexcept
        {
            data[0] = std::move(other.data[0]);
            data[1] = std::move(other.data[1]);

            return *this;
        }

        vec2& operator+=(const vec2& other) noexcept
        {
            x += other.x;
            y += other.y;

            return *this;
        }

        vec2& operator-=(const vec2& other) noexcept
        {
            x -= other.x;
            y -= other.y;

            return *this;
        }

        vec2& operator*=(const vec2& other) noexcept
        {
            x *= other.x;
            y *= other.y;

            return *this;
        }

        vec2& operator/=(const vec2& other) noexcept
        {
            x /= other.x;
            y /= other.y;

            return *this;
        }

        vec2& operator/=(const Type other) noexcept
        {
            x /= other;
            y /= other;

            return *this;
        }

        [[nodiscard]] inline constexpr Type dot(const vec2& other) const noexcept
        {
            return (x * other.x) + (y * other.y);
        }

        [[nodiscard]] static inline constexpr Type dot(const vec2& lhs, const vec2& rhs) noexcept
        {
            return lhs.dot(rhs);
        }

        [[nodiscard]] inline constexpr Type length() const noexcept
        {
            return const_cast<Type>(std::sqrt(const_cast<double>((x * x) + (y * y))));
        }

        [[nodiscard]] static inline constexpr Type length(const vec2& v) noexcept
        {
            return v.length();
        }

        [[nodiscard]] inline constexpr Type lengthsquared() const noexcept
        {
            return (x * x) + (y * y);
        }

        [[nodiscard]] static inline constexpr Type lengthsquared(const vec2& v) noexcept
        {
            return v.lengthsquared();
        }

        inline constexpr void normalize() noexcept
        {
            Type mag = length();

            if (mag > std::numeric_limits<Type>::epsilon)
                *this /= mag;
            else
                set(0);
        }

        static inline constexpr void normalize(const vec2& v) noexcept
        {
            v.normalize();
        }

        [[nodiscard]] inline constexpr vec2 normalized() const noexcept
        {
            vec2 copy(data);
            copy.normalize();

            return copy;
        }

        [[nodiscard]] static inline constexpr vec2 normalized(const vec2& v) noexcept
        {
            return v.normalized();
        }

        [[nodiscard]] inline std::string_view to_string() const noexcept
        {
            return std::to_string(x) + ", " + std::to_string(y);
        }

        [[nodiscard]] static inline std::string_view to_string(const vec2& d) noexcept
        {
            return d.to_string();
        }

        [[nodiscard]] static inline constexpr Type distance(const vec2& lhs, const vec2& rhs) noexcept
        {
            vec2 delta = rhs - lhs;
            return delta.length();
        }

        union
        {
            struct
            {
                Type x, y;
            };

            struct
            {
                Type r, g;
            };

            struct
            {
                Type u, v;
            };

            Type data[2];
        };
    };

    template<typename Type>
    [[nodiscard]] constexpr vec2<Type> operator+(const vec2<Type>& lhs, const vec2<Type>& rhs) noexcept
    {
        vec2<Type> temp = lhs;
        temp += rhs;

        return temp;
    }

    template <typename Type>
    [[nodiscard]] constexpr vec2<Type> operator-(const vec2<Type>& lhs, const vec2<Type>& rhs) noexcept
    {
        vec2<Type> temp = lhs;
        temp -= rhs;

        return temp;
    }

    template <typename Type>
    [[nodiscard]] constexpr vec2<Type> operator*(const vec2<Type>& lhs, const vec2<Type>& rhs) noexcept
    {
        vec2<Type> temp = lhs;
        temp *= rhs;

        return temp;
    }

    template <typename Type>
    [[nodiscard]] constexpr vec2<Type> operator/(const vec2<Type>& lhs, const vec2<Type>& rhs) noexcept
    {
        vec2<Type> temp = lhs;
        temp /= rhs;

        return temp;
    }

    template <typename Type>
    [[nodiscard]] constexpr vec2<Type> operator/(const vec2<Type>& lhs, Type rhs) noexcept
    {
        vec2<Type> temp = lhs;
        temp /= rhs;

        return temp;
    }

    template<typename Type>
    [[nodiscard]] constexpr vec2<Type> operator-(const vec2<Type>& lhs) noexcept
    {
        vec2<Type> temp = lhs;
        temp *= -1;

        return temp;
    }

    // Predefined types
    typedef vec2<bool> bvec2;
    typedef vec2<uint32_t> uvec2;
    typedef vec2<int32_t> ivec2;
    typedef vec2<float> fvec2;
    typedef vec2<double> dvec2;
} // namespace sol::math

#endif // _SOL_VEC2_HPP__