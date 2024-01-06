#include "buffer.hpp"

namespace kat {

    Buffer::Buffer() {
        glCreateBuffers(1, &m_buffer);
    }

    Buffer::Buffer(const void *data, size_t size, BufferUsage usage) {
        glCreateBuffers(1, &m_buffer);
        set(data, size, usage);
    }

    Buffer::~Buffer() {
        glDeleteBuffers(1, &m_buffer);
    }

    void Buffer::bind(BufferTarget target) const {
        glBindBuffer(static_cast<GLenum>(target), m_buffer);
    }

    void Buffer::clear() {
        set(nullptr, 0, BufferUsage::StaticDraw);
    }

    void Buffer::set(const void *data, size_t size, BufferUsage usage) {
        if (usage == BufferUsage::UseCurrent) {
            usage = m_current_usage;
        }

        if (usage == BufferUsage::Undefined) {
            usage = BufferUsage::DynamicDraw;
        }

        if (!data) {
            // used to resize and not set. important to not try and use subdata.
            glNamedBufferData(m_buffer, size, nullptr, static_cast<GLenum>(usage));
        } else {
            if (m_current_usage != usage || m_current_size != size) {
                glNamedBufferData(m_buffer, size, data, static_cast<GLenum>(usage));
            } else {
                glNamedBufferSubData(m_buffer, 0, size, data);
            }
        }

        m_current_size = size;
        m_current_usage = usage;
    }
} // kat