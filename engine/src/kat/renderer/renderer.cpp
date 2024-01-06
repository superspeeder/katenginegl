#include "renderer.hpp"


#include <iostream>

namespace kat {
    Renderer::Renderer(const std::shared_ptr<Engine> &engine) : m_engine(engine) {
        int gl_major, gl_minor;
        glGetIntegerv(GL_MAJOR_VERSION, &gl_major);
        glGetIntegerv(GL_MINOR_VERSION, &gl_minor);

        if (gl_major != 4 && gl_minor != 6) throw std::runtime_error("Bad OpenGL Version");
    }

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