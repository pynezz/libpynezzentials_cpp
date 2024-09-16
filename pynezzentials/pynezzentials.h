#ifndef LIBPYNEZZENTIALS_CPP_LIBRARY_H
#define LIBPYNEZZENTIALS_CPP_LIBRARY_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cstdio>
#include <cstdarg>

namespace pynezzentials {
    // Ansi colors
    const std::string Reset = "\033[0m"; // Reset the escape sequence
    const std::string Red = "\033[31m";
    const std::string Green = "\033[32m";
    const std::string Yellow = "\033[33m";
    const std::string Blue = "\033[34m";
    const std::string Purple = "\033[35m";
    const std::string Cyan = "\033[36m";
    const std::string Gray = "\033[37m";
    const std::string White = "\033[97m";

    // Ansi styles
    const std::string Bold = "\033[1m";
    const std::string Underline = "\033[4m";
    const std::string Inverse = "\033[7m";

    // Ansi 256 light colors
    const std::string LightRed = "\033[91m";
    const std::string LightGreen = "\033[92m";
    const std::string LightYellow = "\033[93m";
    const std::string LightBlue = "\033[94m";
    const std::string LightPurple = "\033[95m";
    const std::string LightCyan = "\033[96m";

    // Ansi 256 dark colors
    const std::string DarkRed = "\033[31m";
    const std::string DarkGreen = "\033[32m";
    const std::string DarkYellow = "\033[33m";
    const std::string DarkBlue = "\033[34m";
    const std::string DarkPurple = "\033[35m";
    const std::string DarkCyan = "\033[36m";

    // Background colors
    const std::string BgRed = "\033[41m";
    const std::string BgGreen = "\033[42m";
    const std::string BgYellow = "\033[43m";
    const std::string BgBlue = "\033[44m";
    const std::string BgPurple = "\033[45m";
    const std::string BgCyan = "\033[46m";
    const std::string BgGray = "\033[47m";

    // Cursor movement
    const std::string CursorUp = "\033[A"; // Move the cursor up
    const std::string CursorDown = "\033[B"; // Move the cursor down
    const std::string CursorRight = "\033[C"; // Move the cursor right
    const std::string CursorLeft = "\033[D"; // Move the cursor left

    // Terminal control
    const std::string ClearScreen = "\033[2J"; // Clear the screen
    const std::string ClearLine = "\033[K";    // Clear the current line
    const std::string Backspace = "\b";        // Backspace key
    const std::string Delete = "\033[3~";      // Delete key
    const std::string Enter = "\r";            // Return carriage
    const std::string Tab = "\t";              // Tab

    // Cursor positioning
    const std::string Home = "\033[H";
    const std::string SaveCursor = "\033[s";
    const std::string RestoreCursor = "\033[u";
    const std::string HideCursor = "\033[?25l";
    const std::string ShowCursor = "\033[?25h";

    // Rounded box characters
    const std::string RoundedTopLeft = "╭";
    const std::string RoundedTopRight = "╮";
    const std::string RoundedBottomLeft = "╰";
    const std::string RoundedBottomRight = "╯";
    const std::string RoundedHoriz = "─";
    const std::string RoundedVert = "│";

    // std::string SPrintRoundedBottom(int width);
    // std::string SPrintRoundedTop(int width);
    //
    // std::string AddPadding(const std::string& content, int width);
    // std::string FormatRoundedBox(const std::string& content);

    // Helper functions
    inline void SetCursorPos(int x, int y) {
        std::printf("\033[%d;%dH", x, y);
    }

    inline std::string SPrintRoundedTop(int width) {
        std::string rtop;
        for (int i = 0; i < width - 2; ++i) {
            rtop += RoundedHoriz;
        }
        return RoundedTopLeft + rtop + RoundedTopRight;
    }

    inline std::string SPrintRoundedBottom(int width) {
        std::string rbottom;
        for (int i = 0; i < width - 2; ++i) {
            rbottom += RoundedHoriz;
        }
        return RoundedBottomLeft + rbottom + RoundedBottomRight;
    }

    inline void PrintRoundedTop(int width) {
        std::cout << RoundedTopLeft;
        for (int i = 0; i < width - 2; ++i) {
            std::cout << RoundedHoriz;
        }
        std::cout << RoundedTopRight;
    }

    inline void PrintRoundedBottom(int width) {
        std::cout << RoundedBottomLeft;
        for (int i = 0; i < width - 2; ++i) {
            std::cout << RoundedHoriz;
        }
        std::cout << RoundedBottomRight;
    }

    inline std::string AddPadding(const std::string& content, const int width) {
        const int padding = width - content.length();
        std::string padded = content;
        for (int i = 0; i < padding + 1; ++i) {
            padded += " ";
        }
        return padded;
    }

    inline int GetWidth(const std::string& content) {
        int width = 0;
        int tmpW = 0;
        for (char c : content) {
            if (c == '\n') {
                if (width < tmpW) {
                    width = tmpW;
                }
                tmpW = 0;
            } else {
                ++tmpW;
            }
        }
        return std::max(width, tmpW);
    }

    inline std::string FormatRoundedBox(const std::string& content) {
        int w = 0;
        std::string result;
        std::vector<std::string> lines;
        std::stringstream ss(content);

        std::string line;
        while (std::getline(ss, line, '\n')) {
            auto str = RoundedVert;
            str += " " + line;

            lines.push_back(str);
            if (w < line.length()) {
                w = line.length();
            }
        }

        w += 4; // Padding for rounded corners

        std::string finres;
        for (const auto& l : lines) {
            finres += AddPadding(l, w) + RoundedVert + "\n";
        }

        return SPrintRoundedTop(w) + "\n" + finres + SPrintRoundedBottom(w);
    }

    // Print functions
    inline void PrintSuccess(const std::string& msg) {
        std::cout << Green << "[+]" << Reset << " " << msg << std::endl;
    }

    inline void PrintError(const std::string& msg) {
        std::cout << Red << "[!]" << Reset << " " << msg << std::endl;
    }

    inline void PrintErrorf(const std::string& format, ...) {
        va_list args;
        va_start(args, format);
        std::cout << Red << "[!]" << Reset << " ";
        vprintf(format.c_str(), args);
        std::cout << std::endl;
        va_end(args);
    }

    inline std::string ColorF(const std::string& color, const std::string& format, ...) {
        va_list args;
        va_start(args, format);
        char buffer[256];
        vsnprintf(buffer, sizeof(buffer), format.c_str(), args);
        va_end(args);
        return color + std::string(buffer) + Reset;
    }

    // Hex to RGB conversion utility
    inline bool HexToRGB(const std::string& hex, int& r, int& g, int& b) {
        std::string cleanedHex = (hex[0] == '#') ? hex.substr(1) : hex;
        if (cleanedHex.length() != 6) return false;

        std::stringstream ss;
        ss << std::hex << cleanedHex.substr(0, 2);
        ss >> r;
        ss.clear();
        ss << std::hex << cleanedHex.substr(2, 2);
        ss >> g;
        ss.clear();
        ss << std::hex << cleanedHex.substr(4, 2);
        ss >> b;
        return true;
    }

    // RGB to xterm-256 color
    inline int RGBToColor256(int r, int g, int b) {
        return 16 + 36 * (r / 51) + 6 * (g / 51) + (b / 51);
    }

    inline std::string HexColor256(int r, int g, int b, const std::string& msg) {
        int color = RGBToColor256(r, g, b);
        return "\033[38;5;" + std::to_string(color) + "m" + msg + Reset;
    }

    inline std::string SprintHexf(const std::string& hex, const std::string& msg) {
        int r, g, b;
        if (!HexToRGB(hex, r, g, b)) {
            return ""; // return empty string on failure
        }
        int color = RGBToColor256(r, g, b);
        return "\033[38;5;" + std::to_string(color) + "m" + msg + Reset;
    }

    inline std::string HexBgAndFg(const std::string& hexFg, const std::string& hexBg, const std::string& msg) {
        int rFg, gFg, bFg, rBg, gBg, bBg;
        if (!HexToRGB(hexFg, rFg, gFg, bFg) || !HexToRGB(hexBg, rBg, gBg, bBg)) {
            return ""; // return empty string on failure
        }
        int colorFg = RGBToColor256(rFg, gFg, bFg);
        int colorBg = RGBToColor256(rBg, gBg, bBg);
        return "\033[38;5;" + std::to_string(colorFg) + "m\033[48;5;" + std::to_string(colorBg) + "m" + msg + Reset;
    }

    inline void PrintColorAndBgBold(const std::string& color, const std::string& bg, const std::string& msg) {
        std::cout << color + bg + Bold << msg << Reset << std::endl;
    }

    inline std::string GetCursorPos() {
        std::cout << "\033[6n";
        // Handling input from terminal to get the position might require system-specific handling.
        // This part would depend on the terminal environment and may need raw input mode enabled.
        return ""; // Placeholder
    }

    inline void PrintBold(const std::string& msg) {
        std::cout << Bold << msg << Reset << std::endl;
    }

    inline void PrintItalic(const std::string& msg) {
        std::cout << "\033[3m" << msg << Reset << std::endl;
    }

    inline void PrintUnderline(const std::string& msg) {
        std::cout << Underline << msg << Reset << std::endl;
    }

    inline void PrintInverse(const std::string& msg) {
        std::cout << Inverse << msg << Reset << std::endl;
    }

    inline void PrintColor(const std::string& color, const std::string& msg) {
        std::cout << color << msg << Reset << std::endl;
    }

    inline void PrintColorf(const std::string& color, const std::string& format, ...) {
        va_list args;
        va_start(args, format);
        std::cout << color;
        vprintf(format.c_str(), args);
        std::cout << Reset << std::endl;
        va_end(args);
    }

    inline void PrintColorUnderline(const std::string& color, const std::string& msg) {
        std::cout << color + Underline << msg << Reset << std::endl;
    }
}

#endif //LIBPYNEZZENTIALS_CPP_LIBRARY_H
