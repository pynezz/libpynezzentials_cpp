#ifndef LIBPYNEZZENTIALS_CPP_LIBRARY_H
#define LIBPYNEZZENTIALS_CPP_LIBRARY_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cstdio>
#include <cstdarg>


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

std::string SPrintRoundedBottom(int width);
std::string SPrintRoundedTop(int width);

std::string AddPadding(const std::string& content, int width);
std::string FormatRoundedBox(const std::string& content);

void SetCursorPos(int x, int y);
void PrintRoundedBottom(int width);
void PrintRoundedTop(int width);
int GetWidth(const std::string& content);


#endif //LIBPYNEZZENTIALS_CPP_LIBRARY_H
