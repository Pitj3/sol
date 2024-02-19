#include <sol/core/application.hpp>
#include <sol/sol.hpp>
#include <sol/core/window.hpp>

class GameApplication : public sol::core::Application
{
  public:
    GameApplication(const std::shared_ptr<sol::Sol>& context) : Application(context)
    {
    
    }

    void on_initialize() override
    {
        auto info = sol::core::WindowCreateInfo{
            .width = 1280, .height = 720, .title = "Sol Engine", .fullscreen = false, .vsync = true};

        open_window(info);
    }

    void on_close() override
    {
    }
};

SOL_DEFINE_APPLICATION_MAIN(GameApplication)