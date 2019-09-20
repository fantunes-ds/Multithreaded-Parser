#pragma once

namespace Utils
{
    /**
     * Class with static functions that allow to modify console text color.
     * @note Only for Windows Console. Requires to use <windows.h>
     */
    class ColorManagement
    {
    public:
        /**
         * Color Codes for Windows Console Colors.
         */
        enum Color
        {
            BLACK = 0,
            BLUE = 1,
            GREEN = 2,
            AQUA = 3,
            RED = 4,
            PURPLE = 5,
            YELLOW = 6,
            WHITE = 7,
            GRAY = 8,
            LIGHT_BLUE = 9,
            LIGHT_GREEN = 'a',
            LIGHT_AQUA = 'b',
            LIGHT_RED = 'c',
            LIGHT_PURPLE = 'd',
            LIGHT_YELLOW = 'e',
            BRIGHT_WHITE = 'f',
        };

        /**
         * Sets all text following this call to the wanted color.
         * @param
         * @n Overload 1:
         * @param p_textColor : Change color only
         * @n Overload 2:
         * @param p_textColor : Color you want the text in
         * @param p_backgroundColor : Color of the background behind the text
         */
        static void SetColorTo(const Color& p_textColor);
        static void SetColorTo(const Color& p_textColor, const Color& p_backgroundColor);
        static void ResetColor();
    };
}
