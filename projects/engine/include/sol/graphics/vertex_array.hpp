#ifndef _SOL_VERTEX_ARRAY_HPP__
#define _SOL_VERTEX_ARRAY_HPP__

#include <vector>
#include <cstdint>

#include <sol/graphics/buffer.hpp>

namespace sol::graphics
{
	class VertexArray
	{
      public:
        VertexArray(const std::vector<VertexBuffer*> vBuffers, IndexBuffer* iBuffer, const BufferLayout& layout);

		void set_index_buffer(IndexBuffer* buffer);
        void set_layout(const BufferLayout& layout);

		void bind() const;
        void unbind() const;

		void create();

	  private:
        uint32_t _id;

        std::vector<VertexBuffer*> _vertexBuffers;
        IndexBuffer* _indexBuffer;
        BufferLayout _bufferLayout;
	};
}

#endif // _SOL_VERTEX_ARRAY_HPP__