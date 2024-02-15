#ifndef _SOL_MAT4_HPP__
#define _SOL_MAT4_HPP__

#include <algorithm>

#include <math/vec4.hpp>

namespace sol::math
{
    template <typename Type>
    class mat4
    {
      public:
        constexpr mat4() noexcept
        {
            identity();
        }

        constexpr mat4(Type m00, Type m01, Type m02, Type m03, 
                        Type m10, Type m11, Type m12, Type m13, 
                        Type m20, Type m21, Type m22, Type m23, 
                        Type m30, Type m31, Type m32, Type m33) noexcept
        {
            this->m00 = m00;
            this->m10 = m10;
            this->m20 = m20;
            this->m30 = m30;

            this->m01 = m01;
            this->m11 = m11;
            this->m21 = m21;
            this->m31 = m31;

            this->m02 = m02;
            this->m12 = m12;
            this->m22 = m22;
            this->m32 = m32;

            this->m03 = m03;
            this->m13 = m13;
            this->m23 = m23;
            this->m33 = m33;
        }

        constexpr explicit mat4(Type diagonal) noexcept
        {
            m00 = diagonal;
            m10 = static_cast<Type>(0);
            m20 = static_cast<Type>(0);
            m30 = static_cast<Type>(0);
            m01 = static_cast<Type>(0);
            m11 = diagonal;
            m21 = static_cast<Type>(0);
            m31 = static_cast<Type>(0);
            m02 = static_cast<Type>(0);
            m12 = static_cast<Type>(0);
            m22 = diagonal;
            m32 = static_cast<Type>(0);
            m03 = static_cast<Type>(0);
            m13 = static_cast<Type>(0);
            m23 = static_cast<Type>(0);
            m33 = diagonal;
        }

        constexpr explicit mat4(Type* data) noexcept
        {
            set(data);
        }

        constexpr mat4(Type col1[4], Type col2[4], Type col3[4], Type col4[4]) noexcept
        {
            m00 = col1[0];
            m01 = col1[1];
            m02 = col1[2];
            m03 = col1[3];

            m10 = col2[0];
            m11 = col2[1];
            m12 = col2[2];
            m13 = col2[3];

            m20 = col3[0];
            m21 = col3[1];
            m22 = col3[2];
            m23 = col3[3];

            m30 = col4[0];
            m31 = col4[1];
            m32 = col4[2];
            m33 = col4[3];
        }

        constexpr mat4(const mat4& other) noexcept
        {
            m00 = other.m00;
            m10 = other.m10;
            m20 = other.m20;
            m30 = other.m30;

            m01 = other.m01;
            m11 = other.m11;
            m21 = other.m21;
            m31 = other.m31;

            m02 = other.m02;
            m12 = other.m12;
            m22 = other.m22;
            m32 = other.m32;

            m03 = other.m03;
            m13 = other.m13;
            m23 = other.m23;
            m33 = other.m33;
        }

        constexpr mat4(mat4&& other) noexcept
        {
            m00 = std::move(other.m00);
            m10 = std::move(other.m10);
            m20 = std::move(other.m20);
            m30 = std::move(other.m30);

            m01 = std::move(other.m01);
            m11 = std::move(other.m11);
            m21 = std::move(other.m21);
            m31 = std::move(other.m31);

            m02 = std::move(other.m02);
            m12 = std::move(other.m12);
            m22 = std::move(other.m22);
            m32 = std::move(other.m32);

            m03 = std::move(other.m03);
            m13 = std::move(other.m13);
            m23 = std::move(other.m23);
            m33 = std::move(other.m33);
        }

        constexpr void set(Type m00, Type m01, Type m02, Type m03, 
                            Type m10, Type m11, Type m12, Type m13, 
                            Type m20, Type m21, Type m22, Type m23, 
                            Type m30, Type m31, Type m32, Type m33) noexcept
        {
            this->m00 = m00;
            this->m10 = m10;
            this->m20 = m20;
            this->m30 = m30;

            this->m01 = m01;
            this->m11 = m11;
            this->m21 = m21;
            this->m31 = m31;

            this->m02 = m02;
            this->m12 = m12;
            this->m22 = m22;
            this->m32 = m32;

            this->m03 = m03;
            this->m13 = m13;
            this->m23 = m23;
            this->m33 = m33;
        }

        constexpr void set(Type* v) noexcept
        {
            for (int i = 0; i < 16; i++)
            {
                this->v[i] = v[i];
            }
        }

        constexpr mat4& operator=(const mat4& other) noexcept
        {
            for (std::size_t i = 0; i < 16; i++)
            {
                data[i] = other.data[i];
            }
            
            return *this;
        }

        constexpr mat4& operator=(mat4&& other) noexcept
        {
            for (std::size_t i = 0; i < 16; i++)
            {
                data[i] = std::move(other.data[i]);
            }
            
            return *this;
        }

        inline constexpr bool operator==(const mat4& other) const noexcept
        {
            return m00 == other.m00 && m10 == other.m10 && m20 == other.m20 && m30 == other.m30 && m01 == other.m01 &&
                   m11 == other.m11 && m21 == other.m21 && m31 == other.m31 && m02 == other.m02 && m12 == other.m12 &&
                   m22 == other.m22 && m32 == other.m32 && m03 == other.m03 && m13 == other.m13 && m23 == other.m23 &&
                   m33 == other.m33;
        }

        inline constexpr bool operator!=(const mat4& other) const noexcept
        {
            return m00 != other.m00 || m10 != other.m10 || m20 != other.m20 || m30 != other.m30 || m01 != other.m01 ||
                   m11 != other.m11 || m21 != other.m21 || m31 != other.m31 || m02 != other.m02 || m12 != other.m12 ||
                   m22 != other.m22 || m32 != other.m32 || m03 != other.m03 || m13 != other.m13 || m23 != other.m23 ||
                   m33 != other.m33;
        }

        inline constexpr mat4 operator*=(const mat4& other) noexcept
        {
            mat4 result;
            for (std::size_t col = 0; col < 4; ++col)
            {
                for (std::size_t row = 0; row < 4; ++row)
                {
                    Type sum = default(Type);
                    for (std::size_t k = 0; k < 4; ++k)
                    {
                        sum += data[k * 4 + row] * other.data[col * 4 + k];
                    }
                    result.data[col * 4 + row] = sum;
                }
            }

            return *this;
        }

        inline constexpr mat4 operator*=(const Type other) noexcept
        {
            for (std::size_t i = 0; i < 16; i++)
            {
                data[i] *= other;
            }

            return *this;
        }

        inline constexpr void transpose() noexcept
        {
            std::swap(m01, m10);
            std::swap(m02, m20);
            std::swap(m03, m30);
            std::swap(m12, m21);
            std::swap(m13, m31);
            std::swap(m23, m32);
        }

        static inline constexpr void transpose(const mat4& m) noexcept
        {
            m.transpose();
        }

        [[nodiscard]] inline constexpr mat4 transposed() noexcept
        {
            mat4 copy(data);

            copy.transpose();

            return copy;
        }

        [[nodiscard]] static inline constexpr void transposed(const mat4& m) noexcept
        {
            return m.transposed();
        }

        inline constexpr void set_identity() noexcept
        {
            m00 = static_cast<Type>(1);
            m10 = static_cast<Type>(0);
            m20 = static_cast<Type>(0);
            m30 = static_cast<Type>(0);
            m01 = static_cast<Type>(0);
            m11 = static_cast<Type>(1);
            m21 = static_cast<Type>(0);
            m31 = static_cast<Type>(0);
            m02 = static_cast<Type>(0);
            m12 = static_cast<Type>(0);
            m22 = static_cast<Type>(1);
            m32 = static_cast<Type>(0);
            m03 = static_cast<Type>(0);
            m13 = static_cast<Type>(0);
            m23 = static_cast<Type>(0);
            m33 = static_cast<Type>(1);
        }

        static inline constexpr mat4 identity() noexcept
        {
            mat4 mat;
            mat.set_identity();

            return mat;
        }

        inline constexpr void invert() noexcept
        {
            Type c00 = data[2 * 4 + 2] * data[3 * 4 + 3] - data[3 * 4 + 2] * data[2 * 4 + 3];
            Type c02 = data[1 * 4 + 2] * data[3 * 4 + 3] - data[3 * 4 + 2] * data[1 * 4 + 3];
            Type c03 = data[1 * 4 + 2] * data[2 * 4 + 3] - data[2 * 4 + 2] * data[1 * 4 + 3];

            Type c04 = data[2 * 4 + 1] * data[3 * 4 + 3] - data[3 * 4 + 1] * data[2 * 4 + 3];
            Type c06 = data[1 * 4 + 1] * data[3 * 4 + 3] - data[3 * 4 + 1] * data[1 * 4 + 3];
            Type c07 = data[1 * 4 + 1] * data[2 * 4 + 3] - data[2 * 4 + 1] * data[1 * 4 + 3];

            Type c08 = data[2 * 4 + 1] * data[3 * 4 + 2] - data[3 * 4 + 1] * data[2 * 4 + 2];
            Type c10 = data[1 * 4 + 1] * data[3 * 4 + 2] - data[3 * 4 + 1] * data[1 * 4 + 2];
            Type c11 = data[1 * 4 + 1] * data[2 * 4 + 2] - data[2 * 4 + 1] * data[1 * 4 + 2];

            Type c12 = data[2 * 4 + 0] * data[3 * 4 + 3] - data[3 * 4 + 0] * data[2 * 4 + 3];
            Type c14 = data[1 * 4 + 0] * data[3 * 4 + 3] - data[3 * 4 + 0] * data[1 * 4 + 3];
            Type c15 = data[1 * 4 + 0] * data[2 * 4 + 3] - data[2 * 4 + 0] * data[1 * 4 + 3];

            Type c16 = data[2 * 4 + 0] * data[3 * 4 + 2] - data[3 * 4 + 0] * data[2 * 4 + 2];
            Type c18 = data[1 * 4 + 0] * data[3 * 4 + 2] - data[3 * 4 + 0] * data[1 * 4 + 2];
            Type c19 = data[1 * 4 + 0] * data[2 * 4 + 2] - data[2 * 4 + 0] * data[1 * 4 + 2];

            Type c20 = data[2 * 4 + 0] * data[3 * 4 + 1] - data[3 * 4 + 0] * data[2 * 4 + 1];
            Type c22 = data[1 * 4 + 0] * data[3 * 4 + 1] - data[3 * 4 + 0] * data[1 * 4 + 1];
            Type c23 = data[1 * 4 + 0] * data[2 * 4 + 1] - data[2 * 4 + 0] * data[1 * 4 + 1];

            vec4<Type> fac0(c00, c00, c02, c03);
            vec4<Type> fac1(c04, c04, c06, c07);
            vec4<Type> fac2(c08, c08, c10, c11);
            vec4<Type> fac3(c12, c12, c14, c15);
            vec4<Type> fac4(c16, c16, c18, c19);
            vec4<Type> fac5(c20, c20, c22, c23);

            vec4<Type> vec0(data[1 * 4 + 0], data[0 * 4 + 0], data[0 * 4 + 0], data[0 * 4 + 0]);
            vec4<Type> vec1(data[1 * 4 + 1], data[0 * 4 + 1], data[0 * 4 + 1], data[0 * 4 + 1]);
            vec4<Type> vec2(data[1 * 4 + 2], data[0 * 4 + 2], data[0 * 4 + 2], data[0 * 4 + 2]);
            vec4<Type> vec3(data[1 * 4 + 3], data[0 * 4 + 3], data[0 * 4 + 3], data[0 * 4 + 3]);

            vec4<Type> inv0(vec1 * fac0 - vec2 * fac1 + vec3 * fac2);
            vec4<Type> inv1(vec0 * fac0 - vec2 * fac3 + vec3 * fac4);
            vec4<Type> inv2(vec0 * fac1 - vec1 * fac3 + vec3 * fac5);
            vec4<Type> inv3(vec0 * fac2 - vec1 * fac4 + vec2 * fac5);

            vec4<Type> sign1(static_cast<Type>(1), static_cast<Type>(-1), static_cast<Type>(1), static_cast<Type>(-1));
            vec4<Type> sign2(static_cast<Type>(-1), static_cast<Type>(1), static_cast<Type>(-1), static_cast<Type>(1));

            mat4<Type> inver((inv0 * sign1).v, (inv1 * sign2).v, (inv2 * sign1).v, (inv3 * sign2).v);
            vec4<Type> row0 = {inver.data[0], inver.data[4], inver.data[8], inver.data[12]};
            vec4<Type> dot0 = col0 * row0;
            Type dot1 = dot0.x + dot0.y + dot0.z + dot0.w;
            Type inv = static_cast<Type>(1) / dot1;
            inver *= inv;

            set(inver.v);
        }

        static inline constexpr void invert(const mat4& m) noexcept
        {
            m.invert();
        }

        [[nodiscard]] inline constexpr mat4 inverted() noexcept
        {
            mat4 copy(data);
            copy.invert();

            return copy;
        }

        [[nodiscard]] static inline constexpr mat4 inverted(const mat4& m) noexcept
        {
            return m.inverted();
        }

        inline constexpr void negate() noexcept
        {
            for (std::size_t i = 0; i < 16; i++)
            {
                data[i] = -data[i];
            }
        }

        static inline constexpr void negate(const mat4& m) noexcept
        {
            m.negate();
        }

        [[nodiscard]] inline constexpr mat4 negated() noexcept
        {
            mat4 copy(data);
            copy.negate();

            return copy;
        }

        [[nodiscard]] static inline constexpr mat4 negated(const mat4& m) noexcept
        {
            return m.negated();
        }

        [[nodiscard]] inline constexpr Type determinant() const noexcept
        {
            Type f = m00 * ((m11 * m22 * m33 + m12 * m23 * m31 + m13 * m21 * m32) - m13 * m22 * m31 - m11 * m23 * m32 -
                         m12 * m21 * m33);
            f -= m01 * ((m10 * m22 * m33 + m12 * m23 * m30 + m13 * m20 * m32) - m13 * m22 * m30 - m10 * m23 * m32 -
                        m12 * m20 * m33);
            f += m02 * ((m10 * m21 * m33 + m11 * m23 * m30 + m13 * m20 * m31) - m13 * m21 * m30 - m10 * m23 * m31 -
                        m11 * m20 * m33);
            f -= m03 * ((m10 * m21 * m32 + m11 * m22 * m30 + m12 * m20 * m31) - m12 * m21 * m30 - m10 * m22 * m31 -
                        m11 * m20 * m32);

            return f;
        }

        [[nodiscard]] inline std::string to_string() const noexcept
        {
            return std::to_string(m00) + ", " + std::to_string(m10) + ", " + std::to_string(m20) + std::to_string(m30) +
                   "\n" + std::to_string(m01) + ", " + std::to_string(m11) + ", " + std::to_string(m21) +
                   std::to_string(m31) + "\n" + std::to_string(m02) + ", " + std::to_string(m12) + ", " +
                   std::to_string(m22) + std::to_string(m32) + "\n" + std::to_string(m03) + ", " + std::to_string(m13) +
                   ", " + std::to_string(m23) + std::to_string(m33);
        }

        [[nodiscard]] static inline constexpr mat4 view(const vec3<Type>& eye, const vec3<Type>& to, const vec3<Type>& up) noexcept
        {
            mat4 res = mat4::identity();

            vec3<Type> zAxis = vec3<Type>::normalize(eye - to);
            vec3<Type> xAxis = vec3<Type>::normalize(vec3<Type>::cross(up, zAxis));
            vec3<Type> yAxis = vec3<Type>::normalize(vec3<Type>::cross(zAxis, xAxis));

            res.m00 = xAxis.x;
            res.m10 = xAxis.y;
            res.m20 = xAxis.z;
            res.m30 = -vec3<Type>::dot(xAxis, eye);

            res.m01 = yAxis.x;
            res.m11 = yAxis.y;
            res.m21 = yAxis.z;
            res.m31 = -vec3<Type>::dot(yAxis, eye);

            res.m02 = zAxis.x;
            res.m12 = zAxis.y;
            res.m22 = zAxis.z;
            res.m32 = -vec3<Type>::dot(zAxis, eye);

            return res;
        }

        [[nodiscard]] static inline constexpr mat4 perspective(Type fov, Type aspect, Type near, Type far)
        {
            mat4 res = mat4::identity();

            Type width = static_cast<Type>(1) - static_cast<Type>(std::tan(static_cast<double>(fov) / 2.0)),
                 height = aspect / static_cast<Type>(std::tan(static_cast<double>(fov) / 2.0));

            res.m00 = width;
            res.m11 = height;
            res.m22 = far / (near - far);
            res.m32 = far * near / (near - far);
            res.m23 = static_cast<Type>(-1);

            return res;
        }

        [[nodiscard]] static inline constexpr mat4 ortho(Type width, Type height, Type near, Type far) noexcept
        {
            mat4 res = mat4::identity();

            res.m00 = static_cast<Type>(2) / width;
            res.m11 = static_cast<Type>(2) / height;
            res.m22 = static_cast<Type>(2) / (near - far);
            res.m32 = near / (near - far);
        }

        template<typename Type2>
        [[nodiscard]] static inline constexpr mat4 translate(const vec3<Type2>& translation) noexcept
        {
            mat4 res = mat4::identity();

            res.m30 = static_cast<Type>(translation.x);
            res.m31 = static_cast<Type>(translation.y);
            res.m32 = static_cast<Type>(translation.z);

            return res;
        }

        template <typename Type2>
        [[nodiscard]] static inline constexpr mat4 scale(const vec3<Type2>& scale) noexcept
        {
            mat4 res = mat4::identity();

            res.m00 = static_cast<Type>(scale.x);
            res.m11 = static_cast<Type>(scale.y);
            res.m22 = static_cast<Type>(scale.z);

            return res;
        }

        [[nodiscard]] static inline constexpr mat4 rotate_x(Type theta) noexcept
        {
            mat4 res = mat4::identity();

            Type cosT = static_cast<Type>(std::cos(static_cast<double>(theta)));
            Type sinT = static_cast<Type>(std::sin(static_cast<double>(theta)));

            res.m11 = cosT;
            res.m12 = sinT;
            res.m21 = -sinT;
            res.m22 = cosT;

            return res;
        }

        [[nodiscard]] static inline constexpr mat4 rotate_y(Type theta) noexcept
        {
            mat4 res = mat4::identity();

            Type cosT = static_cast<Type>(std::cos(static_cast<double>(theta)));
            Type sinT = static_cast<Type>(std::sin(static_cast<double>(theta)));

            res.m00 = cosT;
            res.m02 = sinT;
            res.m20 = -sinT;
            res.m22 = cosT;

            return res;
        }

        [[nodiscard]] static inline constexpr mat4 rotate_z(Type theta) noexcept
        {
            mat4 res = mat4::identity();

            Type cosT = static_cast<Type>(std::cos(static_cast<double>(theta)));
            Type sinT = static_cast<Type>(std::sin(static_cast<double>(theta)));

            res.m00 = cosT;
            res.m01 = sinT;
            res.m10 = -sinT;
            res.m11 = cosT;

            return res;
        }

        template<typename Type2>
        [[nodiscard]] static inline constexpr mat4 rotate(const vec3<Type2>& axis, Type angle) noexcept
        {
            mat4 res = mat4::identity();

            Type c = static_cast<Type>(std::cos(static_cast<double>(angle)));
            Type s = static_cast<Type>(std::sin(static_cast<double>(angle)));
            Type t = static_cast<Type>(1) - c;

            vec3<Type2> normalizedAxis = axis.normalized();
            Type x = static_cast<Type>(normalizedAxis.x);
            Type y = static_cast<Type>(normalizedAxis.y);
            Type z = static_cast<Type>(normalizedAxis.z);

            res.m00 = static_cast<Type>(1) + t * (x * x - static_cast<Type>(1));
            res.m01 = z * s + t * x * y;
            res.m02 = -y * s + t * x * z;

            res.m10 = -z * s + t * x * y;
            res.m11 = static_cast<Type>(1) + t * (y * y - static_cast<Type>(1));
            res.m12 = x * s + t * y * z;

            res.m20 = y * s + t * x * z;
            res.m21 = -x * s + t * y * z;
            res.m22 = static_cast<Type>(1) + t * (z * z - static_cast<Type>(1));

            return res;
        }

        [[nodiscard]] static inline constexpr mat4 rotate(Type yaw, Type pitch, Type roll) noexcept
        {
            return rotaty_y(yaw) * rotate_x(pitch) * rotate_z(roll);
        }

        template<typename Type2, typename Type3>
        [[nodiscard]] static inline constexpr mat4 rotate(const vec3<Type2>& axis, Type angle, const vec3<Type3>& center) noexcept
        {
            return translate(-center) * rotate(axis, angle) * translate(center);
        }

        union 
        {
            struct
            {
                union 
                {
                    vec4<Type> col0;
                    struct
                    {
                        Type m00, m01, m02, m03;
                    };
                };

                union 
                {
                    vec4<Type> col1;
                    struct
                    {
                        Type m10, m11, m12, m13;
                    };
                };

                union 
                {
                    vec4<Type> col2;
                    struct
                    {
                        Type m20, m21, m22, m23;
                    };
                };

                union 
                {
                    vec4<Type> col3;
                    struct
                    {
                        Type m30, m31, m32, m33;
                    };
                };
            };

            vec4<Type> col[4];
            Type data[16];
        };
    };

    template<typename Type>
    inline constexpr mat4<Type> operator*(mat4<Type> lhs, mat4<Type> rhs) noexcept
    {
        mat4<Type> temp = lhs;
        temp *= rhs;

        return temp;
    }

    template<typename Type>
    inline constexpr vec4<Type> operator*(const mat4<Type>& lhs, const vec4<Type>& rhs) noexcept
    {
        Type x = lhs.m00 * rhs.x + lhs.m10 * rhs.y + lhs.m20 * rhs.z + lhs.m30 * rhs.w;
        Type y = lhs.m01 * rhs.x + lhs.m11 * rhs.y + lhs.m21 * rhs.z + lhs.m31 * rhs.w;
        Type z = lhs.m02 * rhs.x + lhs.m12 * rhs.y + lhs.m22 * rhs.z + lhs.m32 * rhs.w;
        Type w = lhs.m03 * rhs.x + lhs.m13 * rhs.y + lhs.m23 * rhs.z + lhs.m33 * rhs.w;

        return {x, y, z, w};
    }

    // Predefined types
    typedef mat4<float> fmat4;
    typedef mat4<double> dmat4;
} // namespace sol::math

#endif // _SOL_MAT4_HPP__