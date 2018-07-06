/*
 * Autor       : Mikael Nilsson
 * Filename    : terminal.cpp
 * Description : Color and cursor manipulation support for terminal/console window (Windows, Linux, OSX)
 * Version     : 0.3
 *
*/

#include "terminal.h"

std::ostream &operator<<(std::ostream &os, std::function<std::ostream &(std::ostream &)> function)
{
    return function(os);
}

void Terminal::pushColor(const TerminalColor &color)
{
    setColor(color);
    m_colors.push(color);
}

std::function<std::function<std::ostream &(std::ostream &)> (const std::string &str)> Terminal::strColor(const TerminalColor &color)
{
    return [this, color](const std::string& str)->std::function<std::ostream &(std::ostream &)>
    {
        return [this, color, str](std::ostream& os)->std::ostream&
        {
            this->pushColor(color);
            os << str.c_str();
            this->popColor();
            return os;
        };
    };
}

std::function<std::ostream &(std::ostream &)> Terminal::color(const TerminalColor &color)
{
    return [this, color](std::ostream& os)->std::ostream&
    {
        this->pushColor(color);
        return os;
    };
}

std::function<std::function<std::ostream&(std::ostream&)>(unsigned int x, unsigned int y)> Terminal::position()
{
    return [this](unsigned int x, unsigned int y)->std::function<std::ostream&(std::ostream&)>
    {
        return [this, x, y](std::ostream& os)->std::ostream&
        {
            this->setCursor(x,y);
            return os;
        };
    };
}

Terminal::~Terminal()
{
    clearColors();
    showCursor(true);
}

#ifdef WIN32

Terminal::Terminal()
    : m_savedAttributes(0)
{
    m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(m_hConsole, &consoleInfo);
    m_savedAttributes = consoleInfo.wAttributes;
    DWORD mode;
    GetConsoleMode(m_hConsole, &mode);
    mode &= ~ENABLE_WRAP_AT_EOL_OUTPUT;
    SetConsoleMode(m_hConsole, mode);
}

void Terminal::popColor()
{
    m_colors.pop();
    if(m_colors.size() > 0)
    {
        setColor(m_colors.top());
    }
    else
    {
        clearColors();
    }
}

void Terminal::clearColors()
{
    while(m_colors.size() > 0)
    {
        m_colors.pop();
    }
    SetConsoleTextAttribute(m_hConsole, m_savedAttributes);
}

void Terminal::resetCursor()
{
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    SetConsoleCursorPosition(m_hConsole, coord);
}

void Terminal::setCursor(unsigned int x, unsigned int y)
{
    COORD coord;
    coord.X = x - 1;
    coord.Y = y - 1;
    SetConsoleCursorPosition(m_hConsole, coord);
}

void Terminal::showCursor(bool show)
{
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(m_hConsole, &info);
    info.bVisible = show;
    SetConsoleCursorInfo(m_hConsole, &info);
}

void Terminal::setColor(const TerminalColor &color)
{
    int fg = cti(color.fg());
    int bg = cti(color.bg());

    if(fg > 0 && fg < 6) fg+=8;
    if(bg > 0 && bg < 6) bg+=8;

    SetConsoleTextAttribute(m_hConsole,((bg & 0x0F) << 4) + (fg & 0x0F));
}

void Terminal::clear()
{
    clearColors();
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;
    COORD begining;
    begining.X = 0;
    begining.Y = 0;
    GetConsoleScreenBufferInfo(m_hConsole, &screen);
    FillConsoleOutputCharacterA(m_hConsole, ' ', screen.dwSize.X * screen.dwSize.Y, begining, &written);
    FillConsoleOutputAttribute(m_hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,screen.dwSize.X * screen.dwSize.Y, begining, &written);
    resetCursor();
}

int Terminal::cti(COLOR c)
{
    switch(c)
    {
    case COLOR::BLACK:
        return 0;
    case COLOR::RED:
        return 4;
    case COLOR::GREEN:
        return 2;
    case COLOR::YELLOW:
        return 14;
    case COLOR::BLUE:
        return 1;
    case COLOR::MAGENTA:
        return 5;
    case COLOR::CYAN:
        return 3;
    case COLOR::WHITE:
        return 15;
    default: //COLOR::NONE:
        return 100;

    }
}

#else

void Terminal::popColor()
{
    if(!m_colors.empty())
    {
        m_colors.pop();
    }
    if(!m_colors.empty())
    {
        setColor(m_colors.top());
    }
    else
    {
        std::cout << "\x1B[0m";
    }
}

void Terminal::clearColors()
{
    while(m_colors.size() > 1)
    {
        m_colors.pop();
    }
    popColor();
}

void Terminal::clear()
{
    clearColors();
    std::cout << "\033[2J\033[1;1H";
    resetCursor();
}

void Terminal::resetCursor()
{
    std::cout << "\033[1;1H";
}

void Terminal::setCursor(unsigned int x, unsigned int y)
{
    std::stringstream ss;
    ss << "\033[" << y << ";" << x << "H";
    std::cout << ss.str();
}

void Terminal::showCursor(bool show)
{
    if(show)
    {
        std::cout << "\e[?25h";
    }
    else
    {
        std::cout << "\e[?25l";
    }
}

void Terminal::setColor(const TerminalColor &color)
{
    std::stringstream ss;
    ss << "\x1B[" << (color.fg() == COLOR::BLACK ? '0' : '1') << ";" << cti(color.fg())+30 << ";" << cti(color.bg())+40 << "m";
    std::cout << ss.str();
}

int Terminal::cti(COLOR c)
{
    switch(c)
    {
    case COLOR::BLACK:
        return 0;
    case COLOR::RED:
        return 1;
    case COLOR::GREEN:
        return 2;
    case COLOR::YELLOW:
        return 3;
    case COLOR::BLUE:
        return 4;
    case COLOR::MAGENTA:
        return 5;
    case COLOR::CYAN:
        return 6;
    case COLOR::WHITE:
        return 7;
    default: //COLOR::NONE:
        return 100;
    }
}

#endif
