#pragma once
#include <memory>
#include <vector>

#include "buffer.hpp"
#include "renderer.hpp"
#include "vertex_array.hpp"

namespace kat {

    struct StandardVertex {
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 uv;
    };

    class Mesh {
      public:
        Mesh(const std::vector<StandardVertex>& vertices);

        virtual ~Mesh() = default;

        void render(const std::shared_ptr<Renderer> &renderer);

      private:
        std::unique_ptr<Buffer>      m_vertex_buffer;
        std::unique_ptr<Buffer>      m_index_buffer;
        std::unique_ptr<VertexArray> m_vertex_array;
    };

} // namespace kat
