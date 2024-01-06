#include <iostream>
#include <kat/engine.hpp>
#include <kat/window.hpp>


#include <random>
#include "kat/renderer/renderer.hpp"


#include "../../engine/src/kat/input_manager.hpp"
#include "kat/renderer/buffer.hpp"
#include "kat/renderer/vertex_array.hpp"

int main() {
    auto engine = kat::Engine::create();
    auto window = std::make_shared<kat::Window>(engine);

    window->set_resizable(true);

    engine->set_vsync(false);

    engine->set_primary_window(window);

    auto renderer = kat::Renderer::create(engine);

    std::random_device random_device;
    std::mt19937 rng(random_device());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(0, 255);

    auto signal_conn = engine->get_viewport_changed_signal().connect([&] (const kat::Viewport& viewport) {
        renderer->set_background_color(kat::color::from_unorm(distribution(rng), distribution(rng), distribution(rng), 255));
    });

    auto signal_conn_2 = engine->get_input_manager()->get_key_pressed_signal().connect([&](kat::Key key, int scancode, kat::KeyMods mods, kat::KeyFlags flags) {
        if (!flags.repeat) {
            if (key == kat::Key::Space) {
                if (mods.control) {
                    renderer->set_background_color(kat::color::from_unorm(distribution(rng), distribution(rng), distribution(rng), 255));
                } else if (mods.shift) {
                    glm::ivec2 pos = engine->get_input_manager()->get_mouse_position();
                    std::cout << "Pos: " << pos.x << ", " << pos.y << std::endl;
                }
            }
            if (key == kat::Key::Escape) {
                window->set_closed(true);
            }
        }
    });

    auto signal_conn_3 = engine->get_input_manager()->get_mouse_button_pressed_signal().connect([&](kat::MouseButton button, glm::ivec2 pos, kat::KeyMods mods) {
        if (button == kat::MouseButton::Left && mods.alt) {
            std::cout << "MPos: " << pos.x << ", " << pos.y << std::endl;
        }
    });

    renderer->set_background_color(kat::colors::CYAN);
    renderer->set_does_clear(true);

    auto vbo = kat::Buffer::create_vec<float>({ 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f }, kat::BufferUsage::StaticDraw);
    auto ebo = kat::Buffer::create_vec<unsigned int>({ 0u, 1u, 2u }, kat::BufferUsage::StaticDraw);

    auto vao = std::make_shared<kat::VertexArray>();
    vao->vertex_buffer(vbo, {3});
    vao->element_buffer(ebo);

    auto redraw_signal = window->get_redraw_signal().connect([&] {
        engine->set_viewport_to_window(window);

        renderer->begin();
        vao->bind();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        renderer->end();
    });

    engine->set_primary_window(window);
    engine->mainloop();
}