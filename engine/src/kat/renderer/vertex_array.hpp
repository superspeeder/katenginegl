#pragma once
#include <memory>


#include "buffer.hpp"

namespace kat {

    struct VertexAttribute {
        size_t size;
        size_t offset;
    };

    class VertexArray {
      public:
        VertexArray();

        ~VertexArray();

        void bind() const;

        void vertex_buffer(const std::shared_ptr<Buffer>& buffer, const std::vector<size_t>& sizes);
        void vertex_buffer(const std::shared_ptr<Buffer>& buffer, const std::vector<VertexAttribute>& attributes, size_t stride, size_t offset = 0);

        void element_buffer(const std::shared_ptr<Buffer>& buffer);
      private:

        unsigned int m_vertex_array;

        unsigned int m_next_binding = 0;
        unsigned int m_next_attribute = 0;
    };

} // namespace kat
