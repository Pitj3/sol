#ifndef _SOL_VEC4_HPP__
#define _SOL_VEC4_HPP__

#include <cmath>
#include <limits>
#include <string>
#include <string_view>
#include <utility>

namespace sol::math
{
    template <typename Type>
    class vec4
    {
      public:
        constexpr vec4() noexcept
        {
            x = y = z = w = 0;
        }

        constexpr vec4(Type x, Type y, Type z, Type w) noexcept
        {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }

        constexpr explicit vec4(Type v) noexcept
        {
            this->x = this->y = this->z = this->w = v;
        }

        constexpr explicit vec4(Type* data) noexcept
        {
            this->data = data;
        }

        constexpr vec4(const vec4& other) noexcept
        {
            this->data = const_cast<Type*>(other.data);
        }

        constexpr vec4(vec4&& other) noexcept
        {
            this->data[0] = std::move(other.data[0]);
            this->data[1] = std::move(other.data[1]);
            this->data[2] = std::move(other.data[2]);
            this->data[3] = std::move(other.data[3]);
        }

        static constexpr vec4 zero() noexcept
        {
            return vec4(0);
        }

        constexpr void set(Type x, Type y, Type z, Type w) noexcept
        {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }

        void set(Type* data) noexcept
        {
            this->data[0] = data[0];
            this->data[1] = data[1];
            this->data[2] = data[2];
            this->data[3] = data[3];
        }

        inline constexpr bool operator==(const vec4& other) const noexcept
        {
            return x == other.x && y == other.y && z == other.z && w == other.w;
        }

        inline constexpr bool operator!=(const vec4& other) const noexcept
        {
            return x != other.x || y != other.y || z != other.z || w != other.w;
        }

        constexpr vec4& operator=(const vec4& other) noexcept
        {
            set(const_cast<Type*>(other.data));

            return *this;
        }

        constexpr vec4& operator=(vec4&& other) noexcept
        {
            data[0] = std::move(other.data[0]);
            data[1] = std::move(other.data[1]);
            data[2] = std::move(other.data[2]);
            data[3] = std::move(other.data[3]);

            return *this;
        }

        vec4& operator+=(const vec4& other) noexcept
        {
            x += other.x;
            y += other.y;
            z += other.z;
            w += other.w;

            return *this;
        }

        vec4& operator-=(const vec4& other) noexcept
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            w -= other.w;

            return *this;
        }

        vec4& operator*=(const vec4& other) noexcept
        {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            w *= other.w;

            return *this;
        }

        vec4& operator/=(const vec4& other) noexcept
        {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            w /= other.w;

            return *this;
        }

        vec4& operator/=(const Type other) noexcept
        {
            x /= other;
            y /= other;
            z /= other;
            w /= other;

            return *this;
        }

        [[nodiscard]] inline constexpr Type dot(const vec4& other) const noexcept
        {
            return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w);
        }

        [[nodiscard]] static inline constexpr Type dot(const vec4& lhs, const vec4& rhs) noexcept
        {
            return lhs.dot(rhs);
        }

        [[nodiscard]] inline constexpr Type length() const noexcept
        {
            return const_cast<Type>(std::sqrt(const_cast<double>((x * x) + (y * y) + (z * z) + (w * w))));
        }

        [[nodiscard]] static inline constexpr Type length(const vec4& v) noexcept
        {
            return v.length();
        }

        [[nodiscard]] inline constexpr Type lengthsquared() const noexcept
        {
            return (x * x) + (y * y) + (z * z) + (w * w);
        }

        [[nodiscard]] static inline constexpr Type lengthsquared(const vec4& v) noexcept
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

        static inline constexpr void normalize(const vec4& v) noexcept
        {
            v.normalize();
        }

        [[nodiscard]] inline constexpr vec4 normalized() const noexcept
        {
            vec4 copy(data);
            copy.normalize();

            return copy;
        }

        [[nodiscard]] static inline constexpr vec4 normalized(const vec4& v) noexcept
        {
            return v.normalized();
        }

        [[nodiscard]] inline std::string_view to_string() const noexcept
        {
            return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w);
        }

        [[nodiscard]] static inline std::string_view to_string(const vec4& d) noexcept
        {
            return d.to_string();
        }

        [[nodiscard]] static inline constexpr Type distance(const vec4& lhs, const vec4& rhs) noexcept
        {
            vec4 delta = rhs - lhs;
            return delta.length();
        }

        [[nodiscard]] static inline constexpr vec4 min(const vec4& a, const vec4& b) noexcept
        {
            return {std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z), std::min(a.w, b.w)};
        }

        [[nodiscard]] static inline constexpr vec4 max(const vec4& a, const vec4& b) noexcept
        {
            return {std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z), std::max(a.w, b.w)};
        }

        inline constexpr void clamp(const vec4& minValue, const vec4& maxValue) noexcept
        {
            *this = max(minValue, min(v, maxValue));
        }

        [[nodiscard]] static inline constexpr vec4 clamp(const vec4& v, const vec4& minValue,
                                                         const vec4& maxValue) noexcept
        {
            return max(minValue, min(v, maxValue));
        }

        [[nodiscard]] static inline constexpr vec4 lerp(const vec4& a, const vec4& b, Type t) noexcept
        {
            return a + (b - a) * t;
        }

        union {
            struct
            {
                Type x, y, z, w;
            };

            struct
            {
                Type r, g, b, a;
            };

            struct
            {
                Type u, v, w, t;
            };

            Type data[4];
        };
    };

    template <typename Type>
    [[nodiscard]] constexpr vec4<Type> operator+(const vec4<Type>& lhs, const vec4<Type>& rhs) noexcept
    {
        vec4<Type> temp = lhs;
        temp += rhs;

        return temp;
    }

    template <typename Type>
    [[nodiscard]] constexpr vec4<Type> operator-(const vec4<Type>& lhs, const vec4<Type>& rhs) noexcept
    {
        vec4<Type> temp = lhs;
        temp -= rhs;

        return temp;
    }

    template <typename Type>
    [[nodiscard]] constexpr vec4<Type> operator*(const vec4<Type>& lhs, const vec4<Type>& rhs) noexcept
    {
        vec4<Type> temp = lhs;
        temp *= rhs;

        return temp;
    }

    template <typename Type>
    [[nodiscard]] constexpr vec4<Type> operator/(const vec4<Type>& lhs, const vec4<Type>& rhs) noexcept
    {
        vec4<Type> temp = lhs;
        temp /= rhs;

        return temp;
    }

    template <typename Type>
    [[nodiscard]] constexpr vec4<Type> operator/(const vec4<Type>& lhs, Type rhs) noexcept
    {
        vec4<Type> temp = lhs;
        temp /= rhs;

        return temp;
    }

    template <typename Type>
    [[nodiscard]] constexpr vec4<Type> operator-(const vec4<Type>& lhs) noexcept
    {
        vec4<Type> temp = lhs;
        temp *= -1;

        return temp;
    }

    // Predefined types
    typedef vec4<bool> bvec4;
    typedef vec4<uint32_t> uvec4;
    typedef vec4<int32_t> ivec4;
    typedef vec4<float> fvec4;
    typedef vec4<double> dvec4;
} // namespace sol::math

#endif // _SOL_vec4_HPP__