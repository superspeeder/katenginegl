#pragma once

#ifndef NDEBUG
#define KATDEBUG
#endif

#include <glad/gl.h>

#include <Windows.h>

#include "kat/utils/signals.hpp"

#include <glm/glm.hpp>

#include <exception>
#include <stdexcept>

namespace kat {
    class InputManager;


    constexpr wchar_t WINDOW_CLASS_NAME[] = L"KATWINDOWCLASS";

    class Renderer;

    class Window;

    struct Viewport {
        glm::ivec2 position;
        glm::uvec2 size;

        friend bool operator==(const Viewport &lhs, const Viewport &rhs) {
            return lhs.position == rhs.position && lhs.size == rhs.size;
        }

        friend bool operator!=(const Viewport &lhs, const Viewport &rhs) { return !(lhs == rhs); }
    };

    class Engine : public std::enable_shared_from_this<Engine> {
      public:
        static std::shared_ptr<Engine> create();

        ~Engine();

        void update();

        void set_vsync(bool vsync);

        [[nodiscard]] bool is_vsync() const;

        [[nodiscard]] signal<void()> &get_window_update_signal() { return m_window_update_signal; }

        [[nodiscard]] const Viewport &get_current_viewport() const { return m_current_viewport; }

        [[nodiscard]] signal<void(const Viewport &)> &get_viewport_changed_signal() { return m_viewport_changed_signal; }

        void set_viewport_to_window(const std::shared_ptr<Window> &window);
        void set_viewport(const Viewport &viewport);

        void set_primary_window(const std::shared_ptr<Window> &window);

        [[nodiscard]] const std::shared_ptr<Window> &get_primary_window() const { return m_primary_window; }

        [[nodiscard]] const std::shared_ptr<Renderer> &get_active_renderer() const { return m_active_renderer; }

        void set_active_renderer(const std::shared_ptr<Renderer> &active_renderer) {
#ifdef KATDEBUG
            if (m_active_renderer)
                throw std::runtime_error("Cannot make renderer active, there is already another active renderer.");
#endif
            m_active_renderer = active_renderer;
        }

        void deactivate_renderer(const std::shared_ptr<Renderer> &renderer) {
            if (renderer == m_active_renderer) {
                m_active_renderer = nullptr; // only deactivate if the active renderer is the one passed in.
            }
            else {
                // todo: log warning
            }
        }

        [[nodiscard]] HINSTANCE get_hinstance() const { return m_hinstance; }

        [[nodiscard]] signal<void(bool &)> &get_is_open_signal() { return m_is_open_signal; }

        [[nodiscard]] bool is_any_open();

        void mainloop();

        [[nodiscard]] signal<void()> get_window_redraw_request_signal() const;

        [[nodiscard]] std::shared_ptr<InputManager> get_input_manager() const;

      private:
        Engine();

        HINSTANCE                     m_hinstance;
        bool                          m_is_vsync = true;
        Viewport                      m_current_viewport;
        std::shared_ptr<Window>       m_primary_window;
        std::shared_ptr<Renderer>     m_active_renderer;
        std::shared_ptr<InputManager> m_input_manager;

        signal<void()>                 m_window_update_signal;
        signal<void()>                 m_window_redraw_request_signal;
        signal<void(const Viewport &)> m_viewport_changed_signal;
        signal<void(bool &)>           m_is_open_signal;
    };

    std::string read_file(const std::string& path);
} // namespace kat
