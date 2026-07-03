#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <cstdlib>

using namespace std;

class Utilities
{
public:
    static inline void printLine(char ch = '=', int length = 70)
    {
        for (int i = 0; i < length; i++)
            cout << ch;
        cout << endl;
    }

    static inline void printTitle(const string &title)
    {
        printLine();
        int width = 70;
        int padding = (width - (int)title.length()) / 2;
        for (int i = 0; i < padding; i++)
            cout << " ";
        cout << title << endl;
        printLine();
    }

    static inline void clearInput()
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    static inline void pause()
    {
        cout << "\nPress ENTER to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    static inline void clearScreen()
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    static inline bool isPositiveInteger(int value)
    {
        return value >= 0;
    }

    static inline bool isPositiveDouble(double value)
    {
        return value >= 0.0;
    }
};

#endif
