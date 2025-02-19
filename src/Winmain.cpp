// Tetris.cpp : This file contains the 'WinMain' function. Program execution begins and ends there.
#define WIN32_LEAN_AND_MEAN
#if defined(_WIN32)
#define WIN32
#endif
#if defined(_WIN64)
#define WIN64
#define _AMD64_
#undef _X86_
#else
#undef _AMD64_
#define _X86_
#endif

// Forward declaration of the necessary Windows API function
extern "C" {
	__declspec(dllimport) int __stdcall GetSystemMetrics(int nIndex);
}

// Define necessary constants
#ifndef SM_CXSCREEN
#define SM_CXSCREEN 0
#endif

#ifndef SM_CYSCREEN
#define SM_CYSCREEN 1
#endif

#include <minwindef.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "Game.h"


int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR lpCmdLine,
    int CmdShow)
{
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int Height = screenHeight / 200;
    Height *= 200;  //mora biti večkratnik 200, da ne odstopajo pixli

    Game* game = new Game(Height*16/20, Height);
    if (game->Init("Tetris")) {
        game->Run();
    }
    delete game;  // This will call the destructor which handles cleanup
    exit(0);    //if i don't call this, the app runs in the background
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
