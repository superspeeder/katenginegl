#include "vertex_array.hpp"

namespace kat {

    VertexArray::VertexArray() {
        glCreateVertexArrays(1, &m_vertex_array);
    }

    VertexArray::~VertexArray() {
        glDeleteVertexArrays(1, &m_vertex_array);
    }

    void VertexArray::bind() const {
        glBindVertexArray(m_vertex_array);
    }

    void VertexArray::vertex_buffer(const std::shared_ptr<Buffer> &buffer, const std::vector<size_t> &sizes) {
        buffer->bind(BufferTarget::Vertex);
        size_t stride = 0;

        const unsigned int binding = m_next_binding++;

        for (const size_t &size : sizes) {
            const unsigned int attribute = m_next_attribute++;

            glVertexArrayAttribFormat(m_vertex_array, attribute, size, GL_FLOAT, false, stride);
            glVertexArrayAttribBinding(m_vertex_array, attribute, binding);
            glEnableVertexArrayAttrib(m_vertex_array, attribute);

            stride += size * sizeof(float);
        }

        glVertexArrayVertexBuffer(m_vertex_array, binding, buffer->get_handle(), 0, stride);
    }

    void VertexArray::vertex_buffer(const std::shared_ptr<Buffer>      &buffer,
                                    const std::vector<VertexAttribute> &attributes, size_t stride, size_t offset) {
        buffer->bind(BufferTarget::Vertex);

        const unsigned int binding = m_next_binding++;

        for (const auto& a : attributes) {
            const unsigned int attribute = m_next_attribute++;

            glVertexArrayAttribFormat(m_vertex_array, attribute, a.size, GL_FLOAT, false, a.offset);
            glVertexArrayAttribBinding(m_vertex_array, attribute, binding);
            glEnableVertexArrayAttrib(m_vertex_array, attribute);
        }

        glVertexArrayVertexBuffer(m_vertex_array, binding, buffer->get_handle(), offset, stride);

    }

    void VertexArray::element_buffer(const std::shared_ptr<Buffer> &buffer) {
        glVertexArrayElementBuffer(m_vertex_array, buffer->get_handle());
    }
} // kat