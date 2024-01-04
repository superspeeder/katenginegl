#pragma once

namespace kat {
    struct color {
        float r, g, b, a;

        static constexpr color from_unorm(unsigned r, unsigned g, unsigned b, unsigned a) {
            return { static_cast<float>(r) / 255.0f, static_cast<float>(g) / 255.0f, static_cast<float>(b) / 255.0f,
                     static_cast<float>(a) / 255.0f };
        }

        friend bool operator==(const color &lhs, const color &rhs) {
            return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a;
        }

        friend bool operator!=(const color &lhs, const color &rhs) { return !(lhs == rhs); }
    };

    namespace colors {
        constexpr color BLACK{ 0, 0, 0, 1 };
        constexpr color WHITE{ 1, 1, 1, 1 };
        constexpr color TRANSPARENT{ 0, 0, 0, 0 };
        constexpr color RED{ 1, 0, 0, 1 };
        constexpr color GREEN{ 0, 1, 0, 1 };
        constexpr color BLUE{ 0, 0, 1, 1 };
        constexpr color YELLOW{ 1, 1, 0, 1 };
        constexpr color CYAN{ 0, 1, 1, 1 };
        constexpr color MAGENTA{ 1, 0, 1, 1 };
    } // namespace colors
} // namespace kat
