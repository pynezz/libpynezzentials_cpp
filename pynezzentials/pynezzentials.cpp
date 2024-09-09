#include <pynezzentials/pynezzentials.h>

// Helper functions
void SetCursorPos(int x, int y) {
    std::printf("\033[%d;%dH", x, y);
}

std::string SPrintRoundedTop(int width) {
    std::string rtop;
    for (int i = 0; i < width - 2; ++i) {
        rtop += RoundedHoriz;
    }
    return RoundedTopLeft + rtop + RoundedTopRight;
}

std::string SPrintRoundedBottom(int width) {
    std::string rbottom;
    for (int i = 0; i < width - 2; ++i) {
        rbottom += RoundedHoriz;
    }
    return RoundedBottomLeft + rbottom + RoundedBottomRight;
}

void PrintRoundedTop(int width) {
    std::cout << RoundedTopLeft;
    for (int i = 0; i < width - 2; ++i) {
        std::cout << RoundedHoriz;
    }
    std::cout << RoundedTopRight;
}

void PrintRoundedBottom(int width) {
    std::cout << RoundedBottomLeft;
    for (int i = 0; i < width - 2; ++i) {
        std::cout << RoundedHoriz;
    }
    std::cout << RoundedBottomRight;
}

std::string AddPadding(const std::string& content, const int width) {
    const int padding = width - content.length();
    std::string padded = content;
    for (int i = 0; i < padding + 1; ++i) {
        padded += " ";
    }
    return padded;
}

int GetWidth(const std::string& content) {
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

std::string FormatRoundedBox(const std::string& content) {
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
void PrintSuccess(const std::string& msg) {
    std::cout << Green << "[+]" << Reset << " " << msg << std::endl;
}

void PrintError(const std::string& msg) {
    std::cout << Red << "[!]" << Reset << " " << msg << std::endl;
}

void PrintErrorf(const std::string& format, ...) {
    va_list args;
    va_start(args, format);
    std::cout << Red << "[!]" << Reset << " ";
    vprintf(format.c_str(), args);
    std::cout << std::endl;
    va_end(args);
}

std::string ColorF(const std::string& color, const std::string& format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), format.c_str(), args);
    va_end(args);
    return color + std::string(buffer) + Reset;
}

// Hex to RGB conversion utility
bool HexToRGB(const std::string& hex, int& r, int& g, int& b) {
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
int RGBToColor256(int r, int g, int b) {
    return 16 + 36 * (r / 51) + 6 * (g / 51) + (b / 51);
}

std::string HexColor256(int r, int g, int b, const std::string& msg) {
    int color = RGBToColor256(r, g, b);
    return "\033[38;5;" + std::to_string(color) + "m" + msg + Reset;
}

std::string SprintHexf(const std::string& hex, const std::string& msg) {
    int r, g, b;
    if (!HexToRGB(hex, r, g, b)) {
        return ""; // return empty string on failure
    }
    int color = RGBToColor256(r, g, b);
    return "\033[38;5;" + std::to_string(color) + "m" + msg + Reset;
}

std::string HexBgAndFg(const std::string& hexFg, const std::string& hexBg, const std::string& msg) {
    int rFg, gFg, bFg, rBg, gBg, bBg;
    if (!HexToRGB(hexFg, rFg, gFg, bFg) || !HexToRGB(hexBg, rBg, gBg, bBg)) {
        return ""; // return empty string on failure
    }
    int colorFg = RGBToColor256(rFg, gFg, bFg);
    int colorBg = RGBToColor256(rBg, gBg, bBg);
    return "\033[38;5;" + std::to_string(colorFg) + "m\033[48;5;" + std::to_string(colorBg) + "m" + msg + Reset;
}

void PrintColorAndBgBold(const std::string& color, const std::string& bg, const std::string& msg) {
    std::cout << color + bg + Bold << msg << Reset << std::endl;
}

std::string GetCursorPos() {
    std::cout << "\033[6n";
    // Handling input from terminal to get the position might require system-specific handling.
    // This part would depend on the terminal environment and may need raw input mode enabled.
    return ""; // Just a placeholder to indicate it sends the escape sequence.
}

void PrintBold(const std::string& msg) {
    std::cout << Bold << msg << Reset << std::endl;
}

void PrintItalic(const std::string& msg) {
    std::cout << "\033[3m" << msg << Reset << std::endl;
}

void PrintUnderline(const std::string& msg) {
    std::cout << Underline << msg << Reset << std::endl;
}

void PrintInverse(const std::string& msg) {
    std::cout << Inverse << msg << Reset << std::endl;
}
void PrintColor(const std::string& color, const std::string& msg) {
    std::cout << color << msg << Reset << std::endl;
}

void PrintColorf(const std::string& color, const std::string& format, ...) {
    va_list args;
    va_start(args, format);
    std::cout << color;
    vprintf(format.c_str(), args);
    std::cout << Reset << std::endl;
    va_end(args);
}

void PrintColorUnderline(const std::string& color, const std::string& msg) {
    std::cout << color + Underline << msg << Reset << std::endl;
}


