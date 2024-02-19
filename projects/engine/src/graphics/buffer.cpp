#include <sol/graphics/buffer.hpp>

#include <glad/gl.h>

namespace sol::graphics
{
	Buffer::Buffer()
	{
        _size = 0;
        glCreateBuffers(1, &_id);
	}


    VertexBuffer::VertexBuffer(const uint32_t size) : Buffer()
    {
        _size = size;

        glNamedBufferStorage(_id, _size, nullptr, 0);
    }

    VertexBuffer::VertexBuffer(void* data, const uint32_t size) : Buffer()
    {
        set_data(data, size);
    }

    void VertexBuffer::set_data(void* data, const uint32_t size)
    {
        _size = size;

        glNamedBufferStorage(_id, _size, data, GL_DYNAMIC_STORAGE_BIT);
    }

    IndexBuffer::IndexBuffer(const uint32_t count) : Buffer()
    {
        _size = count * sizeof(uint32_t);

        glNamedBufferStorage(_id, _size, nullptr, 0);
    }

    IndexBuffer::IndexBuffer(uint32_t* data, const uint32_t count) : Buffer()
    {
        set_data(data, count);
    }

    void IndexBuffer::set_data(uint32_t* data, const uint32_t count)
    {
        _size = count * sizeof(uint32_t);

        glNamedBufferStorage(_id, _size, data, GL_DYNAMIC_STORAGE_BIT);
    }

} // namespace sol::graphics