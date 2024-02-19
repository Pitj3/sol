#include <sol/core/window.hpp>

#include <glad/gl.h> 
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <sol/log/logger.hpp>

static bool sGLFWInitialized = false;

namespace sol::core
{
	Window::~Window()
	{
        glfwDestroyWindow(static_cast<GLFWwindow*>(_windowHandle));
        _platformHandle = nullptr;
	}

	Window::WindowResult Window::create(const WindowCreateInfo& info)
	{
        Window* w = new Window();
		if (!w->initialize(info))
		{
            return WindowResult::from_error(w->_error);
		}

		return WindowResult::from_success(w);
	}

	bool Window::initialize(const WindowCreateInfo& info)
	{
		if (!sGLFWInitialized)
		{
            const int32_t res = glfwInit();
			if (res != GLFW_TRUE)
			{
                _error = "Could not initialize GLFW";
                return false;
			}

			sGLFWInitialized = true;
		}

		if (info.fullscreen)
		{
            GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* vidmode = glfwGetVideoMode(primaryMonitor);
            _windowHandle =
                glfwCreateWindow(vidmode->width, vidmode->height, info.title.c_str(), primaryMonitor, nullptr);
		}
		else
		{
            _windowHandle = glfwCreateWindow(info.width, info.height, info.title.c_str(), nullptr, nullptr);
		}

		#if defined(SOL_PLATFORM_WINDOWS)
        _platformHandle = glfwGetWin32Window(static_cast<GLFWwindow*>(_windowHandle));
		#endif // SOL_PLATFORM_WINDOWS

		if (info.vsync)
		{
            glfwSwapInterval(1);
		}

		glfwShowWindow(static_cast<GLFWwindow*>(_windowHandle));
        glfwMakeContextCurrent(static_cast<GLFWwindow*>(_windowHandle));

		// Initialize GL functions
        const int32_t version = gladLoadGL(glfwGetProcAddress);
        if (version == 0)
        {
            _error = "Could not initialize OpenGL Functions";
            return false;
        }

		return true;
	}

	void Window::poll_events()
	{
        glfwPollEvents();
	}

	void Window::swap()
	{
        glfwSwapBuffers(static_cast<GLFWwindow*>(_windowHandle));
	}
}