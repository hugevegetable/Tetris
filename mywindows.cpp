#include "mywindows.h"

HANDLE handle;

void gotoXY(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void initHandle()
{
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    hideCursor();
}
void hideCursor() // 用于隐藏光标

{

    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };  // 第二个值为0表示隐藏光标

    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);

}
void showCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = { 1, 1 };  // 第二个值为0表示隐藏光标

    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);

}
void  setColor(int color)
{
    SetConsoleTextAttribute(handle, color);
}