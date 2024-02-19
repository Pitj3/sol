#include <sol/graphics/shader_program.hpp>

#include <glad/gl.h>

#include <sol/log/logger.hpp>

namespace sol::graphics
{
    ShaderProgram* ShaderProgram::current;

    ShaderProgram::ShaderProgram(const std::vector<ShaderModule*>& modules)
    {
        auto log = log::ilogger::get("ShaderProgram");
        _id = glCreateProgram();

        for (auto mod : modules)
        {
            glAttachShader(_id, mod->_id);
        }

        glLinkProgram(_id);

        int32_t linked;
        glGetProgramiv(_id, GL_LINK_STATUS, &linked);
        if (!linked)
        {
            char infoLog[512];
            glGetProgramInfoLog(_id, 512, nullptr, infoLog);
            log->error("Error during program linking: {}", infoLog);

            glDeleteProgram(_id);

            for (auto mod : modules)
            {
                glDeleteShader(mod->_id);
            }
        }

        for (auto mod : modules)
        {
            glDetachShader(_id, mod->_id);
        }
    }

    void ShaderProgram::bind()
    {
        glUseProgram(_id);
        current = this;
    }
    
    void ShaderProgram::unbind()
    {
        glUseProgram(0);
        current = nullptr;
    }

    int32_t ShaderProgram::get_uniform_location(const std::string& uniform)
    {
        if (_uniformLocations.contains(uniform))
        {
            return _uniformLocations[uniform];
        }

        int32_t location = glGetUniformLocation(_id, uniform.c_str());
        _uniformLocations[uniform] = location;
        return location;
    }
}