#ifndef _SOL_MATH_COMMON_HPP__
#define _SOL_MATH_COMMON_HPP__

namespace math
{
    template<typename Type>
    class constants
    {
        static inline constexpr Type pi = (Type)3.14159265358979323846f;
        static inline constexpr Type two_pi = (Type)6.28318530717958647692f;
        static inline constexpr Type half_pi = (Type)1.57079632679489661923f;
        static inline constexpr Type degtorad = pi / (Type)180.0f;
        static inline constexpr Type radtodeg = (Type)1.0f / degtorad;
    };
}

#endif // _SOL_MATH_COMMON_HPP__