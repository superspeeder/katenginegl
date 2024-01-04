#pragma once

#include <Windows.h>

#include <memory>

#include "kat/engine.hpp"

namespace kat {

    class Window {
      public:
        Window(const std::shared_ptr<Engine> &engine);

        ~Window();

        [[nodiscard]] bool is_closed() const;
        void set_closed(bool closed);

        void update();
        void request_redraw() const;
        void swap();

        [[nodiscard]] Viewport get_viewport() const;

        void set_resizable(bool resizable) const;

        std::tuple<LPARAM, bool> proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

        [[nodiscard]] RECT get_rect() const;
        [[nodiscard]] RECT get_client_rect() const;


        [[nodiscard]] slot<void()> &get_redraw_slot() { return m_redraw_slot; }

      private:
        HWND m_hwnd;
        bool m_should_close = false;

        std::shared_ptr<signal_connection<void()>> m_update_signal;
        std::shared_ptr<signal_connection<void(bool&)>> m_is_open_signal;

        slot<void()> m_redraw_slot;

    };

} // namespace kat
