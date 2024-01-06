#include "window.hpp"

#include <glad/gl.h>
#include <glad/wgl.h>
#include <iostream>

std::string GetLastErrorAsString() {
    // Get the error message ID, if any.
    DWORD errorMessageID = ::GetLastError();
    if (errorMessageID == 0) {
        return std::string(); // No error message has been recorded
    }

    LPSTR messageBuffer = nullptr;

    // Ask Win32 to give us the string version of that message ID.
    // The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet
    // know how long the message string will be).
    size_t size =
        FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                       NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

    // Copy the error message into a std::string.
    std::string message(messageBuffer, size);

    // Free the Win32's string's buffer.
    LocalFree(messageBuffer);

    return message;
}

GLADapiproc GetAnyGLFuncAddress(const char *name) {
    void *p = (void *)wglGetProcAddress(name);
    if (p == 0 || (p == (void *)0x1) || (p == (void *)0x2) || (p == (void *)0x3) || (p == (void *)-1)) {
        HMODULE module = LoadLibraryA("opengl32.dll");
        p              = (void *)GetProcAddress(module, name);
    }

    return reinterpret_cast<GLADapiproc>(p);
}

namespace kat {
    struct window_data {
        Window *window;
        Engine *engine;
    };

    Window::Window(const std::shared_ptr<Engine> &engine) {
        m_update_signal  = engine->get_window_update_slot().connect_signal([this] { this->update(); });
        m_is_open_signal = engine->get_is_open_slot().connect_signal([this](bool &is_open) {
            if (!this->is_closed()) {
                is_open = true;
            }
        });
        m_request_redraw_signal =
            engine->get_window_redraw_request_slot().connect_signal([this] { this->request_redraw(); });

        // create window

        constexpr DWORD ex_style = WS_EX_OVERLAPPEDWINDOW;
        constexpr DWORD style    = WS_OVERLAPPEDWINDOW;

        constexpr glm::ivec2 pos  = { CW_USEDEFAULT, CW_USEDEFAULT };
        constexpr glm::ivec2 size = { 800, 800 };

        m_hwnd = CreateWindowExW(ex_style, WINDOW_CLASS_NAME, L"Window", style, pos.x, pos.y, size.x, size.y, nullptr,
                                 nullptr, engine->get_hinstance(), this);

        m_dc = GetDC(m_hwnd);

        {
            // clang-format off
            int attrib[] = {
                WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
                WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
                WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
                WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
                WGL_COLOR_BITS_ARB, 24,
                WGL_DEPTH_BITS_ARB, 24,
                WGL_STENCIL_BITS_ARB, 8,
                WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB, GL_TRUE,
                // WGL_SAMPLE_BUFFERS_ARB, 1,
                // WGL_SAMPLES_ARB,        4, // 4x MSAA

                0,
            };
            // clang-format on

            int  format;
            UINT formats;
            wglChoosePixelFormatARB(m_dc, attrib, NULL, 1, &format, &formats);

            PIXELFORMATDESCRIPTOR desc = { .nSize = sizeof(desc) };

            DescribePixelFormat(m_dc, format, sizeof(desc), &desc);

            SetPixelFormat(m_dc, format, &desc);
        }
        {
            int attrib[] = {
                WGL_CONTEXT_MAJOR_VERSION_ARB,
                4,
                WGL_CONTEXT_MINOR_VERSION_ARB,
                6,
                WGL_CONTEXT_PROFILE_MASK_ARB,
                WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
#ifndef NDEBUG
                // ask for debug context for non "Release" builds
                // this is so we can enable debug callback
                WGL_CONTEXT_FLAGS_ARB,
                WGL_CONTEXT_DEBUG_BIT_ARB,
#endif
                0,
            };

            m_hglrc = wglCreateContextAttribsARB(m_dc, NULL, attrib);

            make_current();

            gladLoadGL(GetAnyGLFuncAddress);
        }

        ShowWindow(m_hwnd, SW_NORMAL);
    }

    Window::~Window() {
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(m_hglrc);
        ReleaseDC(m_hwnd, m_dc);
        DestroyWindow(m_hwnd);
    }

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

    void Window::swap() const {
        SwapBuffers(m_dc);
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
            return { 0, true };
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

    void Window::make_current() const {
        wglMakeCurrent(m_dc, m_hglrc);
    }
} // namespace kat
