#pragma once
#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define N 20 //弾の数
#define MAXw 1280 //画面の横最大サイズ
#define MAXh 720 //画面の縦最大サイズ

typedef struct Position {
	int x;
	int y;
} Position;

typedef struct Size {
	int w;
	int h;
} Size;

void YellowMove(Position* pos);	//黄色の移動ルーチン
void GreenMove(Position* pos);	//緑色の移動ルーチン
void RangeSet(Position* pos, Size size);	//画面サイズ内固定
void ShotDirection(int Direction, int ShotFlag[4][N], Position Shot[4][N], Position pos, Size size1, Size size2);	//size1(本体),size2(弾)打つ方向の制御