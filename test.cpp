
#include <windows.h>
#include <wingdi.h>
#include "Structures.h"

void LoadandBuildBitmap(LPCSTR Filename, HDC WDC, HINSTANCE hInst);



LRESULT CALLBACK Main_window_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

HWND Main_window_handle;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX Main_window_class;
    MSG Msg;


    Main_window_class.cbSize = sizeof(WNDCLASSEX);
    Main_window_class.style         = 0;
    Main_window_class.lpfnWndProc   = Main_window_proc;
    Main_window_class.cbClsExtra    = 0;
    Main_window_class.cbWndExtra    = 0;
    Main_window_class.hInstance     = hInstance;
    Main_window_class.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    Main_window_class.hCursor       = LoadCursor(NULL, IDC_ARROW);
    Main_window_class.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    Main_window_class.lpszMenuName  = NULL;
    Main_window_class.lpszClassName = "Main window class";
    Main_window_class.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);


    RegisterClassEx(&Main_window_class);


    Main_window_handle= CreateWindowEx(
    0,                              // Optional window styles.
    "Main window class",            // Window class
    "Dungeon crawler",              // Window text
    WS_OVERLAPPEDWINDOW,            // Window style

    // Size and position
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

    GetDesktopWindow(),       // Parent window    
    NULL,       // Menu
    hInstance,  // Instance handle
    NULL        // Additional application data
    );


    if(Main_window_handle == NULL)
    {
        MessageBox(NULL,"Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    LoadandBuildBitmap("Bitmap.bmp",GetDC(Main_window_handle),hInstance);

    ShowWindow(Main_window_handle, nCmdShow);
    UpdateWindow(Main_window_handle);

    // Step 3: The Message Loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}


void LoadandBuildBitmap(LPCSTR Filename, HDC WDC, HINSTANCE hInst)
{
    /*
    HBITMAP hBitmap;
    hBitmap = (HBITMAP)LoadBitmap(NULL, Filename);

    if (hBitmap==NULL)
    {
        MessageBox(NULL,"Load image failed","Error",MB_OK);
        exit(0);
    }

    HDC LocalDC;
    LocalDC=CreateCompatibleDC(WDC);
    
    if (LocalDC==NULL)
    {
        MessageBox(NULL,"Creating DC failed","Error",MB_OK);
        exit(0);
    }

    BITMAP Bitmap;

    if(!GetObject(hBitmap,sizeof(BITMAP),(LPVOID)&Bitmap))
    {
        MessageBox(NULL,"Getting bitmap info failed","Error",MB_OK);
        exit(0);
    }

    HBITMAP holdBitmap=(HBITMAP)SelectObject(LocalDC,hBitmap);

    if (holdBitmap==NULL)
    {
        MessageBox(NULL,"Holdbitmap failed","Error",MB_OK);
        exit(0);
    }

    if(!BitBlt(WDC,0,0,Bitmap.bmWidth,Bitmap.bmHeight,LocalDC,0,0,SRCCOPY))
    {
        MessageBox(NULL,"BitBlt","Error",MB_OK);
        exit(0);
    }

    SelectObject(WDC,holdBitmap);
    DeleteDC(LocalDC);
    DeleteObject(hBitmap);
}*/
    HBITMAP hBitmap = LoadBitmapA(hInst, "Bitmap.bmp");
    if (hBitmap==NULL)
    {
        MessageBox(NULL,"Load image failed","Error",MB_OK);
        exit(0);
    }

    // Create a memory device compatible with the above DC variable
    HDC LocalDC = CreateCompatibleDC(WDC);
     if (LocalDC==NULL)
    {
        MessageBox(NULL,"Creating DC failed","Error",MB_OK);
        exit(0);
    }

    // Select the new bitmap
    HBITMAP holdBmp = (HBITMAP)SelectObject(LocalDC, hBitmap);

    BITMAP Bitmap;

    if(!GetObject(hBitmap,sizeof(BITMAP),(LPVOID)&Bitmap))
    {
        MessageBox(NULL,"Getting bitmap info failed","Error",MB_OK);
        exit(0);
    }

    if(!BitBlt(WDC,0,0,Bitmap.bmWidth,Bitmap.bmHeight,LocalDC,0,0,SRCCOPY))
    {
        MessageBox(NULL,"BitBlt","Error",MB_OK);
        exit(0);
    }

    // Restore the old bitmap
    SelectObject(LocalDC, holdBmp);
    DeleteObject(hBitmap);
    DeleteDC(LocalDC);
}