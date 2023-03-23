#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "tetris.h"
#include "time.h"
#include <stdio.h>

#include <Windows.h>  //Unicode字符串需要用到
#include <conio.h> //_getch获取用户输入需要用到
#pragma comment (lib,"winmm.lib")//播放音乐函数需要用到



#define GameFrame_Width 20
#define GameFrame_Height 20

#define GameFrame_X 4
#define GameFrame_Y 3


void color(int c);
void welcome();
void DrawGameFrame();
void printEND();
void close();
void music();
void open_music();
void close_music();
void regulation();
void setting();
void gamePlay();


