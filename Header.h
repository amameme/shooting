#pragma once
#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define N 20 //�e�̐�
#define MAXw 1280 //��ʂ̉��ő�T�C�Y
#define MAXh 720 //��ʂ̏c�ő�T�C�Y

typedef struct Position {
	int x;
	int y;
} Position;

typedef struct Size {
	int w;
	int h;
} Size;

void YellowMove(Position* pos);	//���F�̈ړ����[�`��
void GreenMove(Position* pos);	//�ΐF�̈ړ����[�`��
void RangeSet(Position* pos, Size size);	//��ʃT�C�Y���Œ�
void ShotDirection(int Direction, int ShotFlag[4][N], Position Shot[4][N], Position pos, Size size1, Size size2);	//size1(�{��),size2(�e)�ł����̐���