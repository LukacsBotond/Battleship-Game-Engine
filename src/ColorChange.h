#ifndef COLORCHANGE_H
#define COLORCHANGE_H

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#endif // _WIN32

#include <iostream>
using namespace std;

#define color_black 0
#define color_dark_blue 1
#define color_dark_green 2
#define color_light_blue 3
#define color_dark_red 4
#define color_magenta 5
#define color_orange 6
#define color_light_gray 7
#define color_gray 8
#define color_blue 9
#define color_green 10
#define color_cyan 11
#define color_red 12
#define color_pink 13
#define color_yellow 14
#define color_white 15

inline void printcolor(const string s, const int textcolor)
{
#if defined(_WIN32)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    WORD default_colors = 0;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        default_colors = csbi.wAttributes;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 << 4 | textcolor);
#elif defined(__linux__)
    string t, b = "40";
    switch (textcolor)
    {
    case 0:
        t = "30";
        break; // color_black      0
    case 1:
        t = "34";
        break; // color_dark_blue  1
    case 2:
        t = "32";
        break; // color_dark_green 2
    case 3:
        t = "36";
        break; // color_light_blue 3
    case 4:
        t = "31";
        break; // color_dark_red   4
    case 5:
        t = "35";
        break; // color_magenta    5
    case 6:
        t = "33";
        break; // color_orange     6
    case 7:
        t = "37";
        break; // color_light_gray 7
    case 8:
        t = "90";
        break; // color_gray       8
    case 9:
        t = "94";
        break; // color_blue       9
    case 10:
        t = "92";
        break; // color_green     10
    case 11:
        t = "96";
        break; // color_cyan      11
    case 12:
        t = "91";
        break; // color_red       12
    case 13:
        t = "95";
        break; // color_pink      13
    case 14:
        t = "93";
        break; // color_yellow    14
    case 15:
        t = "97";
        break; // color_white     15
    default:
        t = "97";
    }
    cout << "\033[" + t + ";" + b + "m";
#endif // Windows/Linux
    cout << s;

//reset to default
#if defined(_WIN32)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), default_colors);
    cout << endl;
#elif defined(__linux__)
    cout << "\033[0m\n"; // reset color
#endif // Windows/Linux
}
//piros karakterekkel kiirja a megadott uzenetet
inline void printError(string error)
{
    printcolor(error, color_red);
}

#endif