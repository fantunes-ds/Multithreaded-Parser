#include <Utils/ColorManagement.h>

#include <windows.h>

void Utils::ColorManagement::SetColorTo(const Color& p_textColor, const Color& p_backgroundColor)
{
    HANDLE hConsole;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, p_textColor + p_backgroundColor * 16);
}

void Utils::ColorManagement::SetColorTo(const Color& p_textColor)
{
    HANDLE hConsole;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, p_textColor);
}

void Utils::ColorManagement::ResetColor()
{
    HANDLE hConsole;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, WHITE);
}
