#pragma once
#include "kat/utils/color.hpp"
#include "kat/engine.hpp"

namespace kat {

    class Renderer : public std::enable_shared_from_this<Renderer> {
      public:

        static std::shared_ptr<Renderer> create(const std::shared_ptr<Engine>& engine);

        virtual ~Renderer() = default;

        [[nodiscard]] const color &get_background_color() const { return m_background_color; }

        void set_background_color(const color &background_color) { m_background_color = background_color; }

        [[nodiscard]] bool is_does_clear() const { return m_does_clear; }

        void set_does_clear(const bool does_clear) { m_does_clear = does_clear; }

        void begin();

        void end();

      private:

        explicit Renderer(const std::shared_ptr<Engine> &engine);

        std::shared_ptr<Engine> m_engine;

        bool m_does_clear = true;
        color m_background_color = colors::BLACK;
    };

} // namespace kat
