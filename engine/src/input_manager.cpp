#include "input_manager.hpp"

namespace kat {
    InputManager::InputManager(const std::shared_ptr<Window> &window) : m_window(window) {}

    bool InputManager::get_key(Key key) {
        return GetAsyncKeyState(static_cast<int>(key)) != 0;
    }

    bool InputManager::get_mouse_button(MouseButton mouse_button) {
        return GetAsyncKeyState(static_cast<int>(mouse_button)) != 0;
    }

    glm::ivec2 InputManager::get_mouse_position() {
        POINT point{};
        GetCursorPos(&point);

        if (m_window) {
            return m_window->translate_screen_coordinates({point.x, point.y});
        }

        return { point.x, point.y };
    }

    const std::shared_ptr<Window> &InputManager::get_window() const {
        return m_window;
    }

    void InputManager::set_window(const std::shared_ptr<Window> &window) {
        m_window = window;
    }

    signal<void(Key, int, KeyMods, KeyFlags)> &InputManager::get_key_pressed_signal() {
        return m_key_pressed_signal;
    }

    signal<void(Key, int, KeyMods, KeyFlags)> &InputManager::get_key_released_signal() {
        return m_key_released_signal;
    }

    signal<void(MouseButton, glm::ivec2, KeyMods)> &InputManager::get_mouse_button_pressed_signal() {
        return m_mouse_button_pressed_signal;
    }

    signal<void(MouseButton, glm::ivec2, KeyMods)> &InputManager::get_mouse_button_released_signal() {
        return m_mouse_button_released_signal;
    }
} // namespace kat
