#include <sol/core/application.hpp>

#include <glad/gl.h>

#include <sol/log/logger.hpp>

#include <sol/graphics/shader_program.hpp>

#include <sol/graphics/vertex_array.hpp>

namespace sol::core
{
    Application::Application(const std::shared_ptr<Sol>& context)
    {
        window = nullptr;
        _context = context;
    }

    void Application::open_window(const WindowCreateInfo& info)
    {
        auto win = sol::core::Window::create(info);
        if (win.has_value())
        {
            window = win.value();
        }
        else
        {
            log::ilogger* log = log::ilogger::get("WINDOW");
            log->error(win.error());
        }
    }

    int Application::run()
    {
        _running = true;
        on_initialize();

        float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f}; 
        uint32_t indices[] = {0, 1, 2};

        log::ilogger* shaderlog = log::ilogger::get("SHADER");


        const char* vertexShaderSource = "#version 330 core\n"
                                         "layout (location = 0) in vec3 aPos;\n"
                                         "void main()\n"
                                         "{\n"
                                         "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                         "}\0";

        const char* fragmentShaderSource = "#version 330 core\n"
                                           "out vec4 FragColor;\n"
                                           "void main()\n"
                                           "{\n"
                                           "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                           "}\n\0";

        graphics::ShaderModule* vertexModule =
            new graphics::ShaderModule(graphics::EShaderType::VertexShader, vertexShaderSource);

        graphics::ShaderModule* fragmentModule =
            new graphics::ShaderModule(graphics::EShaderType::FragmentShader, fragmentShaderSource);

        graphics::ShaderProgram* shaderProgram = new graphics::ShaderProgram({vertexModule, fragmentModule});

        graphics::VertexBuffer* vBuf = new graphics::VertexBuffer(vertices, sizeof(float) * 9);
        graphics::IndexBuffer* iBuf = new graphics::IndexBuffer(indices, 3);

        graphics::BufferLayout layout;
        layout.push<math::fvec3>("iPosition");
        graphics::VertexArray* vbo = new graphics::VertexArray({vBuf}, iBuf, layout);

        glDisable(GL_CULL_FACE);

        while (_running)
        {
            // run frame
            window->poll_events();

            shaderProgram->bind();
            vbo->bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);

            window->swap();
        }

        on_close();

        delete vbo;
        delete iBuf;
        delete vBuf;
        delete shaderProgram;
        delete fragmentModule;
        delete vertexModule;
        delete window;

        return 0;
    }

    void Application::stop()
    {
        _running = false;
    }
}