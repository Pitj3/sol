#ifndef _SOL_VEC3_HPP__
#define _SOL_VEC3_HPP__

#include <cmath>
#include <limits>
#include <string>
#include <string_view>
#include <utility>

namespace sol::math
{
    template <typename Type>
    class vec3
    {
      public:
        constexpr vec3() noexcept
        {
            x = y = z = 0;
        }

        constexpr vec3(Type x, Type y, Type z) noexcept
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        constexpr explicit vec3(Type v) noexcept
        {
            this->x = this->y = this->z = v;
        }

        constexpr explicit vec3(Type* data) noexcept
        {
            this->data = data;
        }

        constexpr vec3(const vec3& other) noexcept
        {
            this->data = const_cast<Type*>(other.data);
        }

        constexpr vec3(vec3&& other) noexcept
        {
            this->data[0] = std::move(other.data[0]);
            this->data[1] = std::move(other.data[1]);
            this->data[2] = std::move(other.data[2]);
        }

        static constexpr vec3 zero() noexcept
        {
            return vec3(0, 0, 0);
        }

        constexpr void set(Type x, Type y, Type z) noexcept
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        void set(Type* data) noexcept
        {
            this->data[0] = data[0];
            this->data[1] = data[1];
            this->data[2] = data[2];
        }

        inline constexpr bool operator==(const vec3& other) const noexcept
        {
            return x == other.x && y == other.y && z == other.z;
        }

        inline constexpr bool operator!=(const vec3& other) const noexcept
        {
            return x != other.x || y != other.y || z != other.z;
        }

        constexpr vec3& operator=(const vec3& other) noexcept
        {
            set(const_cast<Type*>(other.data));

            return *this;
        }

        constexpr vec3& operator=(vec3&& other) noexcept
        {
            data[0] = std::move(other.data[0]);
            data[1] = std::move(other.data[1]);
            data[2] = std::move(other.data[2]);

            return *this;
        }

        vec3& operator+=(const vec3& other) noexcept
        {
            x += other.x;
            y += other.y;
            z += other.z;

            return *this;
        }

        vec3& operator-=(const vec3& other) noexcept
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;

            return *this;
        }

        vec3& operator*=(const vec3& other) noexcept
        {
            x *= other.x;
            y *= other.y;
            z *= other.z;

            return *this;
        }

        vec3& operator/=(const vec3& other) noexcept
        {
            x /= other.x;
            y /= other.y;
            z /= other.z;

            return *this;
        }

        vec3& operator/=(const Type other) noexcept
        {
            x /= other;
            y /= other;
            z /= other;

            return *this;
        }

        [[nodiscard]] inline constexpr Type dot(const vec3& other) const noexcept
        {
            return (x * other.x) + (y * other.y) + (z * other.z);
        }

        [[nodiscard]] static inline constexpr Type dot(const vec3& lhs, const vec3& rhs) noexcept
        {
            return lhs.dot(rhs);
        }

        [[nodiscard]] inline constexpr Type length() const noexcept
        {
            return const_cast<Type>(std::sqrt(const_cast<double>((x * x) + (y * y) + (z + z))));
        }

        [[nodiscard]] static inline constexpr Type length(const vec3& v) noexcept
        {
            return v.length();
        }

        [[nodiscard]] inline constexpr Type lengthsquared() const noexcept
        {
            return (x * x) + (y * y) + (z + z);
        }

        [[nodiscard]] static inline constexpr Type lengthsquared(const vec3& v) noexcept
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

        static inline constexpr void normalize(const vec3& v) noexcept
        {
            v.normalize();
        }

        [[nodiscard]] inline constexpr vec3 normalized() const noexcept
        {
            vec3 copy(data);
            copy.normalize();

            return copy;
        }

        [[nodiscard]] static inline constexpr vec3 normalized(const vec3& v) noexcept
        {
            return v.normalized();
        }

        [[nodiscard]] inline std::string_view to_string() const noexcept
        {
            return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z);
        }

        [[nodiscard]] static inline std::string_view to_string(const vec3& d) noexcept
        {
            return d.to_string();
        }

        [[nodiscard]] static inline constexpr Type distance(const vec3& lhs, const vec3& rhs) noexcept
        {
            vec3 delta = rhs - lhs;
            return delta.length();
        }

        [[nodiscard]] static inline constexpr vec3 min(const vec3& a, const vec3& b) noexcept
        {
            return {std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z)};
        }

        [[nodiscard]] static inline constexpr vec3 max(const vec3& a, const vec3& b) noexcept
        {
            return {std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z)};
        }

        inline constexpr void clamp(const vec3& minValue, const vec3& maxValue) noexcept
        {
            *this = max(minValue, min(v, maxValue));
        }

        [[nodiscard]] static inline constexpr vec3 clamp(const vec3& v, const vec3& minValue, const vec3& maxValue) noexcept
        {
            return max(minValue, min(v, maxValue));
        }

        [[nodiscard]] static inline constexpr vec3 lerp(const vec3& a, const vec3& b, Type t) noexcept
        {
            return a + (b - a) * t;
        }

        [[nodiscard]] static inline constexpr vec3 cross(const vec3& lhs, const vec3& rhs) noexcept
        {
            return {lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x};
        }

        [[nodiscard]] static inline constexpr vec3 project(const vec3& a, const vec3& b) noexcept
        {
            return b * (dot(a, b) / dot(b, b));
        }

        union {
            struct
            {
                Type x, y, z;
            };

            struct
            {
                Type r, g, b;
            };

            struct
            {
                Type u, v, w;
            };

            Type data[3];
        };
    };

    template <typename Type>
    [[nodiscard]] constexpr vec3<Type> operator+(const vec3<Type>& lhs, const vec3<Type>& rhs) noexcept
    {
        vec3<Type> temp = lhs;
        temp += rhs;

        return temp;
    }

    template <typename Type>
    [[nodiscard]] constexpr vec3<Type> operator-(const vec3<Type>& lhs, const vec3<Type>& rhs) noexcept
    {
        vec3<Type> temp = lhs;
        temp -= rhs;

        return temp;
    }

    template <typename Type>
    [[nodiscard]] constexpr vec3<Type> operator*(const vec3<Type>& lhs, const vec3<Type>& rhs) noexcept
    {
        vec3<Type> temp = lhs;
        temp *= rhs;

        return temp;
    }

    template <typename Type>
    [[nodiscard]] constexpr vec3<Type> operator/(const vec3<Type>& lhs, const vec3<Type>& rhs) noexcept
    {
        vec3<Type> temp = lhs;
        temp /= rhs;

        return temp;
    }

    template <typename Type>
    [[nodiscard]] constexpr vec3<Type> operator/(const vec3<Type>& lhs, Type rhs) noexcept
    {
        vec3<Type> temp = lhs;
        temp /= rhs;

        return temp;
    }

    template <typename Type>
    [[nodiscard]] constexpr vec3<Type> operator-(const vec3<Type>& lhs) noexcept
    {
        vec3<Type> temp = lhs;
        temp *= -1;

        return temp;
    }

    // Predefined types
    typedef vec3<bool> bvec3;
    typedef vec3<uint32_t> uvec3;
    typedef vec3<int32_t> ivec3;
    typedef vec3<float> fvec3;
    typedef vec3<double> dvec3;
} // namespace sol::math

#endif // _SOL_VEC3_HPP__