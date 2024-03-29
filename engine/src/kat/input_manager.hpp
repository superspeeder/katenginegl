#pragma once

#include "engine.hpp"
#include "window.hpp"

namespace kat {

    enum class Key {
        Backspace          = VK_BACK,
        Tab                = VK_TAB,
        Clear              = VK_CLEAR,
        Enter              = VK_RETURN,
        Shift              = VK_SHIFT,
        Control            = VK_CONTROL,
        Alt                = VK_MENU,
        Pause              = VK_PAUSE,
        CapsLock           = VK_CAPITAL,
        Escape             = VK_ESCAPE,
        Space              = VK_SPACE,
        PageUp             = VK_PRIOR,
        PageDown           = VK_NEXT,
        End                = VK_END,
        Home               = VK_HOME,
        Left               = VK_LEFT,
        Up                 = VK_UP,
        Right              = VK_RIGHT,
        Down               = VK_DOWN,
        Select             = VK_SELECT,
        Print              = VK_PRINT,
        Execute            = VK_EXECUTE,
        PrintScreen        = VK_SNAPSHOT,
        Insert             = VK_INSERT,
        Delete             = VK_DELETE,
        Help               = VK_HELP,
        Num0               = 0x30,
        Num1               = 0x31,
        Num2               = 0x32,
        Num3               = 0x33,
        Num4               = 0x34,
        Num5               = 0x35,
        Num6               = 0x36,
        Num7               = 0x37,
        Num8               = 0x38,
        Num9               = 0x39,
        A                  = 0x41,
        B                  = 0x42,
        C                  = 0x43,
        D                  = 0x44,
        E                  = 0x45,
        F                  = 0x46,
        G                  = 0x47,
        H                  = 0x48,
        I                  = 0x49,
        J                  = 0x4A,
        K                  = 0x4B,
        L                  = 0x4C,
        M                  = 0x4D,
        N                  = 0x4E,
        O                  = 0x4F,
        P                  = 0x50,
        Q                  = 0x51,
        R                  = 0x52,
        S                  = 0x53,
        T                  = 0x54,
        U                  = 0x55,
        V                  = 0x56,
        W                  = 0x57,
        X                  = 0x58,
        Y                  = 0x59,
        Z                  = 0x5A,
        LeftWindows        = VK_LWIN,
        RightWindows       = VK_RWIN,
        Apps               = VK_APPS,
        Sleep              = VK_SLEEP,
        Numpad0            = VK_NUMPAD0,
        Numpad1            = VK_NUMPAD1,
        Numpad2            = VK_NUMPAD2,
        Numpad3            = VK_NUMPAD3,
        Numpad4            = VK_NUMPAD4,
        Numpad5            = VK_NUMPAD5,
        Numpad6            = VK_NUMPAD6,
        Numpad7            = VK_NUMPAD7,
        Numpad8            = VK_NUMPAD8,
        Numpad9            = VK_NUMPAD9,
        Multiply           = VK_MULTIPLY,
        Add                = VK_ADD,
        Separator          = VK_SEPARATOR,
        Subtract           = VK_SUBTRACT,
        Decimal            = VK_DECIMAL,
        Divide             = VK_DIVIDE,
        F1                 = VK_F1,
        F2                 = VK_F2,
        F3                 = VK_F3,
        F4                 = VK_F4,
        F5                 = VK_F5,
        F6                 = VK_F6,
        F7                 = VK_F7,
        F8                 = VK_F8,
        F9                 = VK_F9,
        F10                = VK_F10,
        F11                = VK_F11,
        F12                = VK_F12,
        F13                = VK_F13,
        F14                = VK_F14,
        F15                = VK_F15,
        F16                = VK_F16,
        F17                = VK_F17,
        F18                = VK_F18,
        F19                = VK_F19,
        F20                = VK_F20,
        F21                = VK_F21,
        F22                = VK_F22,
        F23                = VK_F23,
        F24                = VK_F24,
        NumLock            = VK_NUMLOCK,
        LeftShift          = VK_LSHIFT,
        RightShift         = VK_RSHIFT,
        LeftControl        = VK_LCONTROL,
        RightControl       = VK_RCONTROL,
        LeftAlt            = VK_LMENU,
        RightAlt           = VK_RMENU,
        BrowserBack        = VK_BROWSER_BACK,
        BrowserForward     = VK_BROWSER_FORWARD,
        BrowserRefresh     = VK_BROWSER_REFRESH,
        BrowserStop        = VK_BROWSER_STOP,
        BrowserSearch      = VK_BROWSER_SEARCH,
        BrowserFavorites   = VK_BROWSER_FAVORITES,
        BrowserHome        = VK_BROWSER_HOME,
        VolumeMute         = VK_VOLUME_MUTE,
        VolumeUp           = VK_VOLUME_UP,
        VolumeDown         = VK_VOLUME_DOWN,
        MediaNextTrack     = VK_MEDIA_NEXT_TRACK,
        MediaPreviousTrack = VK_MEDIA_PREV_TRACK,
        MediaStop          = VK_MEDIA_STOP,
        MediaPlayPause     = VK_MEDIA_PLAY_PAUSE,
        LaunchMail         = VK_LAUNCH_MAIL,
        LaunchMediaSelect  = VK_LAUNCH_MEDIA_SELECT,
        LaunchApp1         = VK_LAUNCH_APP1,
        LaunchApp2         = VK_LAUNCH_APP2,
        Semicolon          = VK_OEM_1,
        Plus               = VK_OEM_PLUS,
        Comma              = VK_OEM_COMMA,
        Minus              = VK_OEM_MINUS,
        Period             = VK_OEM_PERIOD,
        ForwardSlash       = VK_OEM_2,
        Grave              = VK_OEM_3,
        LeftBracket        = VK_OEM_4,
        Backslash          = VK_OEM_5,
        RightBracket       = VK_OEM_6,
        Apostrophe         = VK_OEM_7,
        Play               = VK_PLAY,
        Zoom               = VK_ZOOM,

        LeftButton   = VK_LBUTTON,
        RightButton  = VK_RBUTTON,
        MiddleButton = VK_MBUTTON,
        X1Button     = VK_XBUTTON1,
        X2Button     = VK_XBUTTON2,
    };

    enum class MouseButton : int { Left, Right, Middle, X1, X2 };

    struct KeyMods {
        bool control, shift, alt;
    };

    struct KeyFlags {
        bool repeat;
        int  repeat_count;
    };

    class InputManager {
      public:
        explicit InputManager(const std::shared_ptr<Window> &window);

        ~InputManager() = default;

        bool get_key(Key key);
        bool get_mouse_button(MouseButton mouse_button);

        glm::ivec2 get_mouse_position();

        [[nodiscard]] const std::shared_ptr<Window> &get_window() const;
        void                                         set_window(const std::shared_ptr<Window> &window);

        [[nodiscard]] signal<void(Key, int, KeyMods, KeyFlags)>      &get_key_pressed_signal();
        [[nodiscard]] signal<void(Key, int, KeyMods, KeyFlags)>      &get_key_released_signal();
        [[nodiscard]] signal<void(MouseButton, glm::ivec2, KeyMods)> &get_mouse_button_pressed_signal();
        [[nodiscard]] signal<void(MouseButton, glm::ivec2, KeyMods)> &get_mouse_button_released_signal();

      private:
        std::shared_ptr<Window> m_window;

        signal<void(Key, int, KeyMods, KeyFlags)>      m_key_pressed_signal;
        signal<void(Key, int, KeyMods, KeyFlags)>      m_key_released_signal;
        signal<void(MouseButton, glm::ivec2, KeyMods)> m_mouse_button_pressed_signal;
        signal<void(MouseButton, glm::ivec2, KeyMods)> m_mouse_button_released_signal;
    };

} // namespace kat
