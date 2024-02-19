#ifndef _SOL_BUFFER_HPP__
#define _SOL_BUFFER_HPP__

#include <cstdint>
#include <string>
#include <vector>

#include <math/vec2.hpp>
#include <math/vec3.hpp>
#include <math/mat4.hpp>

#include <glad/gl.h>

namespace sol::graphics
{
	class Buffer
	{
      public:
        Buffer();

		[[nodiscard]] inline uint32_t get_size() const
        {
            return _size;
        }

	  protected:
        uint32_t _id;
        uint32_t _size;
	};

    class VertexBuffer : public Buffer
    {
      public:
        friend class VertexArray;

        VertexBuffer(const uint32_t size);
        VertexBuffer(void* data, const uint32_t size);

        void set_data(void* data, const uint32_t size);
    };

    class IndexBuffer : public Buffer
    {
      public:
        friend class VertexArray;

        IndexBuffer(const uint32_t count);
        IndexBuffer(uint32_t* data, const uint32_t count);

        void set_data(uint32_t* data, const uint32_t count);
    };

    class BufferLayout
    {
      public:
        struct BufferElement
        {
            std::string name;
            uint32_t type;
            std::size_t size;
            uint32_t count;
            std::size_t offset;
            bool normalized;
        };

        template<typename Type>
        void push(const std::string& name, const uint32_t count = 1, const bool normalized = false)
        {
            throw new std::exception("Unknown type");
        }

        const inline std::vector<BufferElement>& get_layout() const 
        {
            return _layout;
        }

        inline std::size_t get_stride() const
        {
            return _size;
        }

      private:
        std::size_t _size = 0;
        std::vector<BufferElement> _layout;

        void _push(const std::string& name, const uint32_t type, const std::size_t size, const uint32_t count, const bool normalized)
        {
            _layout.push_back({name, type, size, count, _size, normalized});
            _size += size * count;
        }
    };

    template<>
    inline void BufferLayout::push<math::fvec2>(const std::string& name, const uint32_t count, const bool normalized)
    {
        _push(name, GL_FLOAT, sizeof(float), 2 * count, normalized);
    }

    template <>
    inline void BufferLayout::push<math::fvec3>(const std::string& name, const uint32_t count, const bool normalized)
    {
        _push(name, GL_FLOAT, sizeof(float), 3 * count, normalized);
    }

    template <>
    inline void BufferLayout::push<math::fmat4>(const std::string& name, const uint32_t count, const bool normalized)
    {
        _push(name, GL_FLOAT, sizeof(float), 16 * count, normalized);
    }
} // namespace sol::graphics

#endif // _SOL_BUFFER_HPP__