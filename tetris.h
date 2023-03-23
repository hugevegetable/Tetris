#pragma once
#include "interface.h"

#include <stdio.h>
#include <conio.h>


#define BLOCK_COUNT 5
#define BLOCK_WIDTH 5
#define BLOCK_HEIGHT 5

#define KEY_UP 72		//�û�����
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

//��ӡ����
void PrintTetris(struct Tetris*);

//�������켣
void CleanTetris(struct Tetris*);

//��ʼ��ǽ
void initwall();

//���̿��Ʒ����ƶ�
Tetris* KeyBored(struct Tetris*);

//�ж��Ƿ��ƶ�
int ifMove(struct Tetris*);

//��������
void Del_FullLine(struct Tetris* tetris);

//
void Fixed_Tetris(struct Tetris*);

//��ת
void Rotate(struct Tetris*);

//�Ƿ�ʧ��
bool isLose(struct Tetris*);

//�Ѷ�
void changeLevel(int grade);

int getScore();

void printScore();

void intoFile();

