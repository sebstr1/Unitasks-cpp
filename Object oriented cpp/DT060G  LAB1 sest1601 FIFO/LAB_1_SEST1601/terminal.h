/*
 * Autor       : Mikael Nilsson
 * Filename    : terminal.h
 * Description : Color and cursor manipulation support for terminal/console window (Windows, Linux, OSX)
 * Version     : 0.3
 *
*/

#ifndef CONSOLE_COLOR_H
#define CONSOLE_COLOR_H

#include <functional>
#include <string>
#include <ostream>
#include <stack>

#ifdef _WIN32
#include <windows.h>
#else
#include <iostream>
#include <sstream>
#endif

enum class COLOR {BLACK = 0, RED = 1, GREEN = 2, YELLOW = 3, BLUE = 4, MAGENTA = 5, CYAN = 6, WHITE = 7};

std::ostream& operator<<(std::ostream& os, std::function<std::ostream&(std::ostream&)> function);

class TerminalColor
{
public:
    TerminalColor(COLOR fg = COLOR::WHITE, COLOR bg = COLOR::BLACK)
        : m_fg(fg), m_bg(bg)
    {}
    COLOR fg() const
    {
        return m_fg;
    }
    COLOR bg() const
    {
        return m_bg;
    }
private:
    COLOR m_fg, m_bg;
};

class Terminal
{
public:
#ifdef WIN32
    Terminal();
#else
    Terminal() = default;
#endif
    ~Terminal();
    void pushColor(const TerminalColor& color);
    void popColor();
    std::function<std::function<std::ostream&(std::ostream&)>(const std::string& str)> strColor(const TerminalColor& color);
    std::function<std::ostream&(std::ostream&)> color(const TerminalColor &color);
    void clearColors();
    void clear();
    void resetCursor();
    void setCursor(unsigned int x, unsigned int y);
    std::function<std::function<std::ostream&(std::ostream&)>(unsigned int x, unsigned int y)>  position();
    void showCursor(bool show);
private:
    void setColor(const TerminalColor& color);
    int cti(COLOR c);
    std::stack<TerminalColor> m_colors;
#ifdef WIN32
    HANDLE m_hConsole;
    WORD m_savedAttributes;
#endif
};

#endif // CONSOLE_COLOR_H
