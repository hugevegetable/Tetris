#pragma once
#include "interface.h"

#include <stdio.h>
#include <conio.h>


#define BLOCK_COUNT 5
#define BLOCK_WIDTH 5
#define BLOCK_HEIGHT 5

#define KEY_UP 72		//用户操作
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DOWN 80
#define KEY_SPACE 32






struct Tetris {
	int x;
	int y;
	int shape;
	int shape_dir;
	bool flag = false;
	
};

void init();

void setTetris(struct Tetris*, int x, int y, int shape, int shape_dir);

Tetris* CreateTetris();

//打印方块
void PrintTetris(struct Tetris*);

//清除方块轨迹
void CleanTetris(struct Tetris*);

//初始化墙
void initwall();

//键盘控制方块移动
Tetris* KeyBored(struct Tetris*);

//判断是否移动
int ifMove(struct Tetris*);

//满行消除
void Del_FullLine(struct Tetris* tetris);

//
void Fixed_Tetris(struct Tetris*);

//旋转
void Rotate(struct Tetris*);

//是否失败
bool isLose(struct Tetris*);

//难度
void changeLevel(int grade);

int getScore();

void printScore();

void intoFile();

