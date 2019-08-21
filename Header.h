#pragma once
#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define N 20 //�e�̐�
#define MAXw 1280 //��ʂ̉��ő�T�C�Y
#define MAXh 720 //��ʂ̏c�ő�T�C�Y
/*
	1920*1080(ChangWindowMode��FALSE�ɂ���΂悵)
	1280*720
	640*480
*/
#define speed 5.5	//�L�����̃X�s�[�h�����ݒ�

typedef struct Position {
	double x;
	double y;
} Position;

typedef struct Size {
	int w;
	int h;
} Size;

void YellowMove(Position* pos);	//���F�̈ړ����[�`��
void GreenMove(Position* pos);	//�ΐF�̈ړ����[�`��
void RangeSet(Position* pos, Size size);	//��ʃT�C�Y���Œ�
void ShotDirection(int Direction, int ShotFlag[4][N], Position Shot[4][N], Position pos, Size size1, Size size2);	//size1(�{��),size2(�e)�ł����̐���
void ShotMove(int i, int j, Position shot[4][N]);	//�e�̈ړ����[�`��
int RangeJudge(int i, int j, Position Shot[4][N]);	//��ʊO����
int HitBox(Position pos1, Size size1, Position pos2, Size size2); //2�̕��̂̓����蔻��
