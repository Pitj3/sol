#ifndef _SOL_TIMER_HPP__
#define _SOL_TIMER_HPP__

#include <chrono>

namespace sol::core
{
	class Timer
	{
      public:
		Timer()
		{
            reset();
		}

		void reset()
		{
            _start = std::chrono::high_resolution_clock::now();
		}

		[[nodiscard]] float elapsed() const
		{ 
            return static_cast<float>(std::chrono::duration_cast<std::chrono::nanoseconds>(
                                          std::chrono::high_resolution_clock::now() - _start)
                                          .count()) *
                   0.001f * 0.001f * 0.001f;
		}

		[[nodiscard]] float elapsed_millis() const
		{
            return elapsed() * 1000.0f;
		}

	  private:
        std::chrono::time_point<std::chrono::high_resolution_clock> _start;
	};
}

#endif // _SOL_TIMER_HPP__