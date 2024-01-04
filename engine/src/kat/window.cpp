#include "window.hpp"

namespace kat {
    Window::Window(const std::shared_ptr<Engine> &engine) {
        m_update_signal = engine->get_window_update_slot().connect_signal([this] { this->update(); });
        m_is_open_signal = engine->get_is_open_slot().connect_signal([this] (bool& is_open) {
            if (!this->is_closed()) {
                is_open = true;
            }
        });

        constexpr DWORD    ex_style = WS_EX_OVERLAPPEDWINDOW;
        constexpr DWORD    style    = WS_OVERLAPPEDWINDOW;
        const std::wstring title    = L"Window";

        constexpr glm::ivec2 pos  = { CW_USEDEFAULT, CW_USEDEFAULT };
        constexpr glm::ivec2 size = { 800, 800 };

        m_hwnd = CreateWindowExW(ex_style, WINDOW_CLASS_NAME, title.c_str(), style, pos.x, pos.y, size.x, size.y,
                                 nullptr, nullptr, engine->get_hinstance(), this);

        ShowWindow(m_hwnd, SW_NORMAL);
    }

    Window::~Window() {}

    bool Window::is_closed() const {
        return m_should_close;
    }

    void Window::set_closed(bool closed) {
        m_should_close = closed;
    }

    void Window::update() {
        // glfwSwapBuffers(m_window);
        //
        // int w, h, fw, fh;
        // glfwGetWindowSize(m_window, &w, &h);
        // glfwGetFramebufferSize(m_window, &fw, &fh);
        //
        // m_size             = { w, h };
        // m_framebuffer_size = { fw, fh };
    }

    void Window::request_redraw() const {
        RedrawWindow(m_hwnd, nullptr, nullptr, RDW_INTERNALPAINT);
    }

    Viewport Window::get_viewport() const {
        auto [left, top, right, bottom] = get_client_rect();
        return { { 0, 0 }, { right, bottom } }; // TODO
    }

    void Window::set_resizable(const bool resizable) const {}

    std::tuple<LPARAM, bool> Window::proc(HWND hwnd, const UINT msg, WPARAM wparam, LPARAM lparam) {
        switch (msg) {
        case WM_CLOSE:
            m_should_close = true;
            return {0, true};
        case WM_PAINT:
            m_redraw_slot.call();
            swap();
            break;
        default:
            break;
        }

        return { 0, false };
    }

    RECT Window::get_rect() const {
        RECT r{};
        GetWindowRect(m_hwnd, &r);
        return r;
    }

    RECT Window::get_client_rect() const {
        RECT r{};
        GetClientRect(m_hwnd, &r);
        return r;
    }
} // namespace kat
