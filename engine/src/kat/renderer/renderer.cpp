#include "renderer.hpp"

namespace kat {
    Renderer::Renderer(const std::shared_ptr<Engine> &engine) : m_engine(engine) {}

    std::shared_ptr<Renderer> Renderer::create(const std::shared_ptr<Engine> &engine) {
        return std::shared_ptr<Renderer>(new Renderer(engine));
    }

    void Renderer::begin() {
        m_engine->set_active_renderer(shared_from_this());

        if (m_does_clear) {
            glClearColor(m_background_color.r, m_background_color.g, m_background_color.b, m_background_color.a);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        }
    }

    void Renderer::end() {
        m_engine->deactivate_renderer(shared_from_this());
    }
} // kat