#include "input_manager.hpp"

namespace kat {
    InputManager::InputManager(const std::shared_ptr<Window> &window) : m_window(window) {

    }

    bool InputManager::get_key(Key key) {
        return GetAsyncKeyState(static_cast<int>(key));
    }

    bool InputManager::get_mouse_button(MouseButton mouse_button) {
        return GetAsyncKeyState(static_cast<int>(mouse_button));
    }
} // kat