#pragma once

#include <glad/gl.h>

#include <Windows.h>

#include <memory>

#include "kat/engine.hpp"

namespace kat {

    class Window {
      public:
        explicit Window(const std::shared_ptr<Engine> &engine);

        ~Window();

        [[nodiscard]] bool is_closed() const;
        void               set_closed(bool closed);

        void update();
        void request_redraw() const;
        void swap() const;

        [[nodiscard]] Viewport get_viewport() const;

        void set_resizable(bool resizable) const;

        std::tuple<LPARAM, bool> proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

        [[nodiscard]] RECT get_rect() const;
        [[nodiscard]] RECT get_client_rect() const;

        [[nodiscard]] signal<void()> &get_redraw_signal() { return m_redraw_signal; }

        void make_current() const;

        glm::ivec2 translate_screen_coordinates(const glm::ivec2& sc) const;

      private:
        HWND  m_hwnd;
        HGLRC m_hglrc;
        bool  m_should_close = false;
        HDC   m_dc;

        std::shared_ptr<Engine> m_engine;

        std::shared_ptr<signal_connection<void()>>       m_update_signal;
        std::shared_ptr<signal_connection<void(bool &)>> m_is_open_signal;
        std::shared_ptr<signal_connection<void()>>       m_request_redraw_signal;

        signal<void()> m_redraw_signal;
    };

} // namespace kat
