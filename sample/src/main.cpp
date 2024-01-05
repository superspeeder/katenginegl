//
// Created by andy on 1/1/24.
//

#include <iostream>
#include <kat/engine.hpp>
#include <kat/window.hpp>


#include "kat/renderer/renderer.hpp"
#include <random>

int main() {
    auto engine = kat::Engine::create();
    auto window = std::make_shared<kat::Window>(engine);

    window->set_resizable(true);

    engine->set_primary_window(window);

    auto renderer = kat::Renderer::create(engine);

    std::random_device random_device;
    std::mt19937 rng(random_device());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(0, 255);

    auto signal_conn = engine->get_viewport_changed_slot().connect_signal([&] (const kat::Viewport& viewport) {
        renderer->set_background_color(kat::color::from_unorm(distribution(rng), distribution(rng), distribution(rng), 255));
    });

    renderer->set_background_color(kat::colors::CYAN);
    renderer->set_does_clear(true);

    auto redraw_signal = window->get_redraw_slot().connect_signal([&] {
        engine->set_viewport_to_window(window);

        renderer->begin();
        renderer->end();
    });

    engine->set_primary_window(window);
    engine->mainloop();
}