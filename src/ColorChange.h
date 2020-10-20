#ifndef COLOR_H
#define COLOR_H

#include <string>
#include <iostream>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#endif // _WIN32

using namespace std;

void printred(const string s)
{
#if defined(_WIN32)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    WORD default_colors = 0;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        default_colors = csbi.wAttributes;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 << 4 | 12);
#elif defined(__linux__)
    string t, b;
    t = "91";
    b = "40";
    cout << "\033[" + t + ";" + b + "m";
#endif // Windows/Linux
    cout << s;
#if defined(_WIN32)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), default_colors);
    cout << endl;
#elif defined(__linux__)
    cout << "\033[0m" << endl; // reset color
#endif // Windows/Linux
}

//piros karakterekkel kiirja a megadott uzenetet
void printError(string error)
{
    printred(error);
}

#endif