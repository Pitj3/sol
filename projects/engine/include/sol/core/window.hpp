#ifndef _SOL_WINDOW_HPP__
#define _SOL_WINDOW_HPP__

#include <cstdint>
#include <string>
#include <memory>

#include <sol/core/result.hpp>

namespace sol::core
{
    struct WindowCreateInfo
    {
        uint16_t width;
        uint16_t height;

        std::string title;

        bool fullscreen;
        bool vsync;
    };

    class Window
    {
      public:
          using WindowResult = Result<Window*, std::string>;

          static WindowResult create(const WindowCreateInfo& info);
          ~Window();

          Window(const Window&) = delete;
          Window& operator=(const Window&) = delete;

          Window(Window&&) noexcept = delete;
          Window& operator=(Window&&) noexcept = delete;

          void poll_events();
          void swap();

      private:
          Window() = default;
          std::string _error;

          void* _windowHandle = nullptr;
          void* _platformHandle = nullptr;

          bool initialize(const WindowCreateInfo& info);
    };
} // namespace sol::core

#endif // _SOL_WINDOW_HPP__