#ifndef _SOL_HPP__
#define _SOL_HPP__

#include <exception>

#if defined(_DEBUG)
#define SOL_DEFINE_MAIN(function)          \
    int main()                             \
    {                                      \
        return function;                   \
    }
#else
#define ATOMIC_DEFINE_MAIN(function)       \
    int main()                             \
    {                                      \
        int exitCode;                      \
        __try                              \
        {                                  \
            exitCode = function;           \
        }                                  \
        __except (std::exception e)        \
        {                                  \
        }                                  \
        return exitCode;                   \
    }
#endif

namespace sol
{
    class Sol
    {

    };
} // namespace sol

#endif // _SOL_HPP__