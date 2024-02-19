#include <sol/graphics/vertex_array.hpp>

namespace sol::graphics
{
    VertexArray::VertexArray(const std::vector<VertexBuffer*> vBuffers, IndexBuffer* iBuffer,
                             const BufferLayout& layout)
    {
        _vertexBuffers = vBuffers;
        _indexBuffer = iBuffer;
        _bufferLayout = layout;

        create();

        set_layout(_bufferLayout);
    }

    void VertexArray::set_index_buffer(IndexBuffer* buffer)
    {
        _indexBuffer = buffer;

        glVertexArrayElementBuffer(_id, _indexBuffer->_id);
    }

    void VertexArray::set_layout(const BufferLayout& layout)
    {
        for (std::size_t i = 0; i < layout.get_layout().size(); i++)
        {
            BufferLayout::BufferElement element = layout.get_layout()[i];
            glEnableVertexArrayAttrib(_id, static_cast<GLuint>(i));
            glVertexArrayAttribFormat(_id, static_cast<GLuint>(i), element.count, element.type, element.normalized,
                                      static_cast<GLuint>(element.offset));
            glVertexArrayAttribBinding(_id, static_cast<GLuint>(i), 0);
        }
    }

    void VertexArray::bind() const
    {
        glBindVertexArray(_id);
    }

    void VertexArray::unbind() const
    {
        glBindVertexArray(0);
    }

    void VertexArray::create()
    {
        glCreateVertexArrays(1, &_id);

        uint32_t idx = 0;
        for (auto vbuf : _vertexBuffers)
        {
            glVertexArrayVertexBuffer(_id, idx++, vbuf->_id, 0, static_cast<GLsizei>(_bufferLayout.get_stride()));
        }

        if (_indexBuffer != nullptr)
        {
            glVertexArrayElementBuffer(_id, _indexBuffer->_id);
        }
    }
} // namespace sol::graphics