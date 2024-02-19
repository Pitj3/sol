#include <sol/graphics/shader_module.hpp>

#include <glad/gl.h>
#include <sol/log/logger.hpp>

namespace sol::graphics
{
    namespace detail
    {
        static GLenum GetShaderType(EShaderType type)
        {
            switch (type)
            {
            case EShaderType::VertexShader:
                return GL_VERTEX_SHADER;
            case EShaderType::FragmentShader:
                return GL_FRAGMENT_SHADER;
            case EShaderType::GeometryShader:
                return GL_GEOMETRY_SHADER;
            case EShaderType::TessEvaluationShader:
                return GL_TESS_EVALUATION_SHADER;
            case EShaderType::TessControlShader:
                return GL_TESS_CONTROL_SHADER;
            case EShaderType::ComputeShader:
                return GL_COMPUTE_SHADER;
            }

            throw new std::exception("Unrecognised shader type");

            return 0;
        }
    }

    ShaderModule::ShaderModule(EShaderType type, const std::string& source)
    {
        auto log = log::ilogger::get("ShaderModule");
        _type = type;

        _id = glCreateShader(detail::GetShaderType(type));

        const char* s = source.c_str();
        glShaderSource(_id, 1, &s, nullptr);
        glCompileShader(_id);

        int32_t compiled;
        glGetShaderiv(_id, GL_COMPILE_STATUS, &compiled);
        if (!compiled)
        {
            char infoLog[512];
            glGetShaderInfoLog(_id, 512, nullptr, infoLog);
            log->error("Error during shader compilation: {}", infoLog);
            
            glDeleteShader(_id);
        }
    }
}