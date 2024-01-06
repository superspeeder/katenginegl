#include "window.hpp"

#include <glad/gl.h>
#include <glad/wgl.h>
#include <iostream>


#include "input_manager.hpp"

#include <windowsx.h>
#include <winuser.h>

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
    Window::Window(const std::shared_ptr<Engine> &engine) : m_engine(engine) {
        m_update_signal  = engine->get_window_update_signal().connect([this] { this->update(); });
        m_is_open_signal = engine->get_is_open_signal().connect([this](bool &is_open) {
            if (!this->is_closed()) {
                is_open = true;
            }
        });
        m_request_redraw_signal =
            engine->get_window_redraw_request_signal().connect([this] { this->request_redraw(); });

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
            m_redraw_signal.emit();
            swap();
            break;
        case WM_KEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP: {

            WORD vk_code = LOWORD(wparam);

            WORD key_flags = HIWORD(lparam);

            WORD scancode        = LOBYTE(key_flags);
            BOOL is_extended_key = (key_flags & KF_EXTENDED) == KF_EXTENDED;

            if (is_extended_key) {
                scancode = MAKEWORD(scancode, 0xE0);
            }

            BOOL was_key_down = (key_flags & KF_REPEAT) == KF_REPEAT;
            WORD repeat_count = LOWORD(lparam);

            BOOL is_key_released = (key_flags & KF_UP) == KF_UP;

            switch (vk_code) {
            case VK_SHIFT:   // converts to VK_LSHIFT or VK_RSHIFT
            case VK_CONTROL: // converts to VK_LCONTROL or VK_RCONTROL
            case VK_MENU:    // converts to VK_LMENU or VK_RMENU
                vk_code = LOWORD(MapVirtualKeyW(scancode, MAPVK_VSC_TO_VK_EX));
                break;
            default:
                break;
            }

            KeyMods key_mods{ .control = GetKeyState(VK_CONTROL) < 0,
                              .shift   = GetKeyState(VK_SHIFT) < 0,
                              .alt     = GetKeyState(VK_MENU) < 0 };


            KeyFlags key_flags_{ .repeat = was_key_down == TRUE, .repeat_count = repeat_count };


            if (is_key_released) {
                m_engine->get_input_manager()->get_key_released_signal().emit(static_cast<Key>(vk_code), scancode,
                                                                            key_mods, key_flags_);
            }
            else {
                m_engine->get_input_manager()->get_key_pressed_signal().emit(static_cast<Key>(vk_code), scancode,
                                                                           key_mods, key_flags_);
            }

        } break;

        case WM_LBUTTONDOWN: {
            KeyMods mods{
                .control = (wparam & MK_CONTROL) != 0,
                .shift   = (wparam & MK_SHIFT) != 0,
                .alt     = GetKeyState(VK_MENU) < 0,
            };

            glm::ivec2 pos = { GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) };

            m_engine->get_input_manager()->get_mouse_button_pressed_signal().emit(MouseButton::Left, pos, mods);
        } break;

        case WM_RBUTTONDOWN: {
            KeyMods mods{
                .control = (wparam & MK_CONTROL) != 0,
                .shift   = (wparam & MK_SHIFT) != 0,
                .alt     = GetKeyState(VK_MENU) < 0,
            };

            glm::ivec2 pos = { GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) };

            m_engine->get_input_manager()->get_mouse_button_pressed_signal().emit(MouseButton::Right, pos, mods);
        } break;


        case WM_MBUTTONDOWN: {
            KeyMods mods{
                .control = (wparam & MK_CONTROL) != 0,
                .shift   = (wparam & MK_SHIFT) != 0,
                .alt     = GetKeyState(VK_MENU) < 0,
            };

            glm::ivec2 pos = { GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) };

            m_engine->get_input_manager()->get_mouse_button_pressed_signal().emit(MouseButton::Middle, pos, mods);
        } break;

        case WM_XBUTTONDOWN: {
            WORD ks = GET_KEYSTATE_WPARAM(wparam);
            WORD b  = GET_XBUTTON_WPARAM(wparam);

            KeyMods mods{
                .control = (ks & MK_CONTROL) != 0,
                .shift   = (ks & MK_SHIFT) != 0,
                .alt     = GetKeyState(VK_MENU) < 0,
            };

            glm::ivec2 pos = { GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) };

            m_engine->get_input_manager()->get_mouse_button_pressed_signal().emit(
                b == XBUTTON1 ? MouseButton::X1 : MouseButton::X2, pos, mods);
        } break;

        case WM_LBUTTONUP: {
            KeyMods mods{
                .control = (wparam & MK_CONTROL) != 0,
                .shift   = (wparam & MK_SHIFT) != 0,
                .alt     = GetKeyState(VK_MENU) < 0,
            };

            glm::ivec2 pos = { GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) };

            m_engine->get_input_manager()->get_mouse_button_released_signal().emit(MouseButton::Left, pos, mods);
        } break;

        case WM_RBUTTONUP: {
            KeyMods mods{
                .control = (wparam & MK_CONTROL) != 0,
                .shift   = (wparam & MK_SHIFT) != 0,
                .alt     = GetKeyState(VK_MENU) < 0,
            };

            glm::ivec2 pos = { GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) };

            m_engine->get_input_manager()->get_mouse_button_released_signal().emit(MouseButton::Right, pos, mods);
        } break;


        case WM_MBUTTONUP: {
            KeyMods mods{
                .control = (wparam & MK_CONTROL) != 0,
                .shift   = (wparam & MK_SHIFT) != 0,
                .alt     = GetKeyState(VK_MENU) < 0,
            };

            glm::ivec2 pos = { GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) };

            m_engine->get_input_manager()->get_mouse_button_released_signal().emit(MouseButton::Middle, pos, mods);
        } break;

        case WM_XBUTTONUP: {
            WORD ks = GET_KEYSTATE_WPARAM(wparam);
            WORD b  = GET_XBUTTON_WPARAM(wparam);

            KeyMods mods{
                .control = (ks & MK_CONTROL) != 0,
                .shift   = (ks & MK_SHIFT) != 0,
                .alt     = GetKeyState(VK_MENU) < 0,
            };

            glm::ivec2 pos = { GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) };

            m_engine->get_input_manager()->get_mouse_button_released_signal().emit(
                b == XBUTTON1 ? MouseButton::X1 : MouseButton::X2, pos, mods);
        } break;


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

    glm::ivec2 Window::translate_screen_coordinates(const glm::ivec2 &sc) const {
        POINT pt{ sc.x, sc.y };
        ScreenToClient(m_hwnd, &pt);
        return { pt.x, pt.y };
    }
} // namespace kat
