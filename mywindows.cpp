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
void hideCursor() // �������ع��

{

    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };  // �ڶ���ֵΪ0��ʾ���ع��

    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);

}
void showCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = { 1, 1 };  // �ڶ���ֵΪ0��ʾ���ع��

    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);

}
void  setColor(int color)
{
    SetConsoleTextAttribute(handle, color);
}