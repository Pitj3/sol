#ifndef _SOL_SHADER_MODULE_HPP__
#define _SOL_SHADER_MODULE_HPP__

#include <cstdint>
#include <string>

namespace sol::graphics
{
	enum class EShaderType : uint8_t
	{
		VertexShader = 0,
		FragmentShader,
		GeometryShader,
		TessEvaluationShader,
		TessControlShader,
		ComputeShader
	};

	class ShaderModule
	{
      public:
        ShaderModule(EShaderType type, const std::string& source);

		inline EShaderType get_type() const
		{
            return _type;
		}

	  private:
        friend class ShaderProgram;
        uint32_t _id;
        EShaderType _type;
	};
}

#endif // _SOL_SHADER_MODULE_HPP__