#ifndef _SOL_SHADER_PROGRAM_HPP__
#define _SOL_SHADER_PROGRAM_HPP__

#include <vector>
#include <unordered_map>

#include <sol/graphics/shader_module.hpp>

namespace sol::graphics
{
	class ShaderProgram
	{
      public:
        ShaderProgram(const std::vector<ShaderModule*>& modules);

		void bind();
        void unbind();

		static ShaderProgram* current;

	  private:
        int32_t get_uniform_location(const std::string& uniform);

		std::unordered_map<std::string, int32_t> _uniformLocations;
        uint32_t _id;
	};
}

#endif // _SOL_SHADER_PROGRAM_HPP__