#include <Windows.h>
#include <iostream>

#define BTN_OK 1000
#define BTN_CLEAR 1001

#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Win32 User Input";
    const wchar_t WINDOW_TITLE[] = L"Your input";

    WNDCLASSEX wcex = { };

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = CLASS_NAME;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            TEXT("Call to RegisterClassEx failed!"),
            TEXT("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    // Create the window.
    HWND hWnd = CreateWindowExW(
        0,
        CLASS_NAME,                                 // Window class
        WINDOW_TITLE,                               // Window text
        WS_SYSMENU,                                 // Window style
        CW_USEDEFAULT, CW_USEDEFAULT, 240, 110,     // Size and position
        NULL,                                       // Parent window    
        NULL,                                       // Menu
        hInstance,                                  // Instance handle
        NULL                                        // Additional application data
    );

    if (hWnd == NULL)
    {
        return 0;
    }

    // hWnd[0]
    HWND hEditBox = CreateWindow(
        TEXT("EDIT"),
        NULL,
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_LEFT | ES_AUTOVSCROLL,
        10, 10, 200, 20,
        hWnd, NULL, NULL, NULL);

    if (hEditBox == NULL)
    {
        return 0;
    }

    // hWnd[1]
    HWND hOkBtn = CreateWindowEx(
        0,
        TEXT("BUTTON"),
        TEXT("OK"),
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_FLAT,
        10, 40, 50, 20,
        hWnd,
        (HMENU)BTN_OK,
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

    if (hOkBtn == NULL)
    {
        return 0;
    }

    // hWnd[2]
    HWND hClearBtn = CreateWindowEx(
        0,
        TEXT("BUTTON"),
        TEXT("Clear"),
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_FLAT,
        70, 40, 50, 20,
        hWnd,
        (HMENU)BTN_CLEAR,
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

    if (hClearBtn == NULL)
    {
        return 0;
    }

    // Set fonts
    LOGFONT logfont;
    ZeroMemory(&logfont, sizeof(LOGFONT));
    logfont.lfCharSet = DEFAULT_CHARSET;
    logfont.lfHeight = 14;
    const CHAR FONTS[] = "Courier New";
    RtlCopyMemory(logfont.lfFaceName, FONTS, sizeof(FONTS));
    HFONT hFont = CreateFontIndirect(&logfont);
    SendMessage(hOkBtn, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hClearBtn, WM_SETFONT, (WPARAM)hFont, TRUE);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
    }
    break;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        wchar_t INPUT_BUFFER[256];
        switch (wmId)
        {
        case BTN_OK:
        {
            ZeroMemory(INPUT_BUFFER, 256);
            HWND hEditBox = GetWindow(hWnd, GW_CHILD);
            GetWindowText(hEditBox, INPUT_BUFFER, 256);
            std::wcout << "Input is " << INPUT_BUFFER << std::endl;
        }
        break;

        case BTN_CLEAR:
        {
            ZeroMemory(INPUT_BUFFER, 256);
            HWND hEditBox = GetWindow(hWnd, GW_CHILD);
            SetWindowText(hEditBox, INPUT_BUFFER);
        }
        break;

        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
    }
    break;

    case WM_INITDIALOG:
    case WM_SETFONT:
    {

    }
    break;

    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}

/* MIT License

Copyright (c) 2021 Jim00000

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software. 

*/