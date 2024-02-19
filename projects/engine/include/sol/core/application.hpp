#ifndef _SOL_APPLICATION_HPP__
#define _SOL_APPLICATION_HPP__

#include <memory>

#include <sol/sol.hpp>
#include <sol/core/window.hpp>

namespace sol::core
{
    class Application
    {
      public:
        Application(const std::shared_ptr<Sol>& context);

        virtual void on_initialize() = 0;
        virtual void on_close() = 0;

        void open_window(const WindowCreateInfo& info);

        int run();
        void stop();

      protected:
        sol::core::Window* window;

    private:
        std::shared_ptr<Sol> _context;
      bool _running = false;
    };

    #define SOL_DEFINE_APPLICATION_MAIN(className)                         \
    int run_application()                                                   \
    {                                                                      \
        std::shared_ptr<sol::Sol> context(new sol::Sol());                 \
        std::shared_ptr<className> application(new className(context));    \
        return application->run();                                         \
    }                                                                      \
    SOL_DEFINE_MAIN(run_application());
} // namespace sol::core

#endif // _SOL_APPLICATION_HPP__