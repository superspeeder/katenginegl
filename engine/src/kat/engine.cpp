#include "engine.hpp"


#include <fstream>
#include <glad/wgl.h>
#include <iostream>


#include "input_manager.hpp"
#include "window.hpp"

namespace kat {
    LRESULT CALLBACK winproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
        if (msg == WM_CREATE) {
            auto* cs = reinterpret_cast<CREATESTRUCTW *>(lparam);
            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(cs->lpCreateParams));
            return 0;
        }

        LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
        if (ptr != NULL) {

            auto *window = reinterpret_cast<Window *>(ptr);

            if (auto [output, success] = window->proc(hwnd, msg, wparam, lparam); success)
                return output;
        }

        return DefWindowProc(hwnd, msg, wparam, lparam);
    }

    Engine::Engine() : m_current_viewport({ 0, 0 }, { 0, 0 }) {
        m_hinstance = GetModuleHandle(nullptr);

        WNDCLASSEXW wc{};
        wc.cbSize        = sizeof(WNDCLASSEXW);
        wc.hInstance     = m_hinstance;
        wc.style         = CS_HREDRAW | CS_VREDRAW;
        wc.lpszClassName = WINDOW_CLASS_NAME;
        wc.lpfnWndProc   = winproc;
        wc.cbWndExtra    = sizeof(Engine *);

        RegisterClassExW(&wc);

        HWND dummy = CreateWindowExW(0, L"STATIC", L"DummyWindow", WS_OVERLAPPED, CW_USEDEFAULT, CW_USEDEFAULT,
                                     CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, NULL, NULL);

        HDC ddc = GetDC(dummy);

        PIXELFORMATDESCRIPTOR ddesc = {
            .nSize        = sizeof(ddesc),
            .nVersion     = 1,
            .dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
            .iPixelType   = PFD_TYPE_RGBA,
            .cColorBits   = 32,
            .cDepthBits   = 24,
            .cStencilBits = 8,
        };

        int dformat = ChoosePixelFormat(ddc, &ddesc);

        DescribePixelFormat(ddc, dformat, sizeof(ddesc), &ddesc);
        SetPixelFormat(ddc, dformat, &ddesc);

        HGLRC rc = wglCreateContext(ddc);
        wglMakeCurrent(ddc, rc);

        gladLoadWGL(
            ddc, +[](const char *p) -> GLADapiproc {
                // std::cout << "Load: " << p << std::endl;
                GLADapiproc proc = reinterpret_cast<GLADapiproc>(wglGetProcAddress(p));
                if (proc == nullptr) {
                    proc = reinterpret_cast<GLADapiproc>(GetProcAddress(GetModuleHandleA(nullptr), p));
                    if (proc == nullptr) {
                        std::cerr << "Failed to load: " << p << std::endl;
                    }
                    else {
                        std::cerr << "Fell back to opengl32.lib for " << p << std::endl;
                    }
                }

                return proc;
            });

        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(rc);
        ReleaseDC(dummy, ddc);
        DestroyWindow(dummy);

        m_input_manager = std::make_shared<kat::InputManager>(nullptr);
    }

    std::string read_file(const std::string &path) {
        std::ifstream f(path, std::ios::in | std::ios::ate);
        auto end = f.tellg();
        f.seekg(0);
        std::string data;
        data.resize(end);
        f.read(data.data(), end);
        f.close();
        return data;
    }

    std::shared_ptr<Engine> Engine::create() {
        return std::shared_ptr<Engine>(new Engine());
    }

    Engine::~Engine() {
        UnregisterClassW(WINDOW_CLASS_NAME, m_hinstance);
    }

    void Engine::update() {
        m_window_redraw_request_signal.emit();

        MSG msg{};
        while (PeekMessage(&msg, nullptr, NULL, NULL, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        m_window_update_signal.emit();
    }

    void Engine::set_vsync(bool vsync) {
        m_is_vsync = vsync;

    }

    bool Engine::is_vsync() const {
        return m_is_vsync;
    }

    void Engine::set_viewport_to_window(const std::shared_ptr<Window> &window) {
        set_viewport(window->get_viewport());
    }

    void Engine::set_viewport(const Viewport &viewport) {

        glViewport(viewport.position.x, viewport.position.y, static_cast<GLsizei>(viewport.size.x),
                   static_cast<GLsizei>(viewport.size.y));
        if (viewport != m_current_viewport) {
            m_viewport_changed_signal.emit(viewport);
        }

        m_current_viewport = viewport;
    }

    void Engine::set_primary_window(const std::shared_ptr<Window> &window) {
        m_primary_window = window;
        m_input_manager->set_window(m_primary_window);
    }

    bool Engine::is_any_open() {
        bool is_open = false;
        m_is_open_signal.emit(is_open);

        return is_open;
    }

    void Engine::mainloop() {
        while (is_any_open()) {
            update();
        }
    }

    signal<void()> Engine::get_window_redraw_request_signal() const {
        return m_window_redraw_request_signal;
    }

    std::shared_ptr<InputManager> Engine::get_input_manager() const {
        return m_input_manager;
    }
} // namespace kat
