#pragma once

#include "kat/engine.hpp"

namespace kat {

    enum class BufferTarget : GLenum {
        Vertex = GL_ARRAY_BUFFER,
        Element = GL_ELEMENT_ARRAY_BUFFER,
        Uniform = GL_UNIFORM_BUFFER,
        ShaderStorage = GL_SHADER_STORAGE_BUFFER,
        Texture = GL_TEXTURE_BUFFER,
    };

    enum class BufferUsage : GLenum {
        StaticDraw = GL_STATIC_DRAW,
        StaticRead = GL_STATIC_READ,
        StaticCopy = GL_STATIC_COPY,

        DynamicDraw = GL_DYNAMIC_DRAW,
        DynamicRead = GL_DYNAMIC_READ,
        DynamicCopy = GL_DYNAMIC_COPY,

        StreamDraw = GL_STREAM_DRAW,
        StreamRead = GL_STREAM_READ,
        StreamCopy = GL_STREAM_COPY,

        UseCurrent,
        Undefined
    };

    class Buffer {
      public:
        Buffer();

        Buffer(const void* data, size_t size, BufferUsage usage = BufferUsage::DynamicDraw);

        template<std::ranges::contiguous_range T>
        explicit Buffer(const T& range, BufferUsage usage = BufferUsage::DynamicDraw) {
            glCreateBuffers(1, &m_buffer);
            set(range, usage);
        }

        static inline std::shared_ptr<Buffer> create() {
            return std::make_shared<Buffer>();
        }

        static inline std::shared_ptr<Buffer> create(const void* data, size_t size, BufferUsage usage = BufferUsage::DynamicDraw) {
            return std::make_shared<Buffer>(data, size, usage);
        }

        template<std::ranges::contiguous_range T>
        static inline std::shared_ptr<Buffer> create(const T& range, BufferUsage usage = BufferUsage::DynamicDraw) {
            return std::make_shared<Buffer>(range, usage);
        }

        template<typename T>
        static inline std::shared_ptr<Buffer> create_vec(const std::vector<T>& range, BufferUsage usage = BufferUsage::DynamicDraw) {
            return std::make_shared<Buffer>(range, usage);
        }


        ~Buffer();

        void bind(BufferTarget target) const;

        void clear();

        void set(const void* data, size_t size, BufferUsage usage = BufferUsage::UseCurrent);

        template<std::ranges::contiguous_range T>
        void set(const T& range, BufferUsage usage = BufferUsage::UseCurrent) {
            using U = std::ranges::range_value_t<T>;
            set(std::ranges::cdata(range), std::ranges::size(range) * sizeof(U), usage);
        }

        [[nodiscard]] unsigned int get_handle() const noexcept { return m_buffer; }

      private:
        unsigned int m_buffer;
        size_t m_current_size = 0;
        BufferUsage m_current_usage = BufferUsage::Undefined;
    };

} // namespace kat
