#include"Header.h"

int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevlnstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);


	Position Yellow, Green, YellowShot[4][N], GreenShot[4][N]; //�΂Ɖ��F�ƒe�̍��W
	Position TmpY, TmpG;
	Size Y, G, YS, GS; //���ꂼ��̉摜�T�C�Y
	int i, j;
	int YellowGraph, YellowShotGraph, GreenGraph, GreenShotGraph, ArrowGraph;	//�n���h���ϐ�
	int YellowDamageGraph, GreenDamageGraph;	//�_���[�W�n���h���ϐ�
	int YellowDamageFlag, GreenDamageFlag;
	int YellowDirection = 0, GreenDirection = 2;	//����0(��),1(��),2(��),3(�E)
	int ShotRCFlag = 0, ShotRSFlag = 0, ShotLSFlag = 0, ShotLCFlag = 0;	//1�t���[����1��̃{�^������
	int ShotYFlag[4][N], ShotGFlag[4][N];	//�e����ʏ�ɕ\������Ă��邩�̏���
	int ShotYCounter = 30, ShotGCounter = 30;	//���̕\���t���[����
	int CharCounter = 0;	//�摜�d������


	/*
	int GreenMuki;
	int GreenDamageFlag, GreenDamageCounter, GreenDamgeGraph;
	int ETamaX, ETamaY, ETamaFlag = 0, ETamaCounter = 0;
	int ShotBFlag = 0;
	*/


	//��ʃ��[�h�̐ݒ�
	SetGraphMode(MAXw, MAXh, 16);

	//DX���C�u�����̏���������
	if (DxLib_Init() == -1) return -1;
	
	//�O���t�B�b�N�̕`���𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	//�O���t�B�b�N�Z�b�g
	YellowGraph = LoadGraph("image/Ball.png");	//���F�̃n���h��
	YellowShotGraph = LoadGraph("image/Shot.png");	//���F�̒e�̃n���h��
	YellowDamageGraph = LoadGraph("image/BallDam.png");	//���F�̃_���[�W�n���h��
	GreenGraph = LoadGraph("image/Sikaku.png");	//�ΐF�̃n���h��
	GreenShotGraph = LoadGraph("image/EShot.png");	//�ΐF�̒e�̃n���h��
	GreenDamageGraph = LoadGraph("image/SikakuDam.png");	//�ΐF�̃_���[�W�n���h��
	ArrowGraph = LoadGraph("image/Arrow.png");	//���̃n���h��

	//�T�C�Y�擾
	GetGraphSize(YellowGraph, &Y.w, &Y.h);
	GetGraphSize(YellowShotGraph, &YS.w, &YS.h);
	GetGraphSize(GreenGraph, &G.w, &G.h);
	GetGraphSize(GreenShotGraph, &GS.w, &GS.h);

	//���F�̍��W�����Z�b�g
	Yellow.x = MAXw - Y.w;
	Yellow.y = MAXh - Y.h;

	//�΂̍��W�����Z�b�g
	Green.x = 0;
	Green.y = 0;


	//���F�e�ƗΒe�̃V���b�g�t���O�̏�����
	for (i = 0; i < 4; i++) {
		for (j = 0; j < N; j++) {
			ShotYFlag[i][j] = 0;
			ShotGFlag[i][j] = 0;
		}
	}
	


	//�ړ����[�`��
	while (1) {
		ClearDrawScreen();

		TmpY = Yellow;
		TmpG = Green;

		//���F�̈ړ����[�`��
		YellowMove(&Yellow);
		//�ΐF�̈ړ����[�`��
		GreenMove(&Green);

		if (HitBox(Yellow, Y, Green, G) == 1) {
			Yellow = TmpY;
			Green = TmpG;
		}

		//���F�̋��̕�������
		if (CheckHitKey(KEY_INPUT_RSHIFT) == 1) {
			if (ShotRSFlag == 0) {
				YellowDirection++;
				if (YellowDirection == 4) YellowDirection = 0;
			}
			ShotRSFlag = 1;
		}
		else ShotRSFlag = 0;

		//�ΐF�̒e�̕�������
		if (CheckHitKey(KEY_INPUT_LSHIFT) == 1) {
			if (ShotLSFlag == 0) {
				GreenDirection++;
				if (GreenDirection == 4) GreenDirection = 0;
			}
			ShotLSFlag = 1;
		}
		else ShotLSFlag = 0;


		//**�����m�F�p�R�}���h
		if (CheckHitKey(KEY_INPUT_F7) == 1) {

			DrawFormatString(0, 0, GetColor(255, 255, 255), "������%d", YellowDirection);

		}

		//�͈͊O�ɏo���Ƃ��̏���
		RangeSet(&Yellow, Y);
		RangeSet(&Green, G);


		//���F�̓��͂ɂ���Ēe���o��
		if (CheckHitKey(KEY_INPUT_RCONTROL) == 1) {
			if (ShotRCFlag == 0) {
				ShotDirection(YellowDirection, ShotYFlag, YellowShot, Yellow, Y, YS);
			}
			//1�t���[���ŋ���ł�������
			ShotRCFlag = 1;
		}
		else ShotRCFlag = 0;

		//�ΐF�̓��͂ɂ���Ēe���o��
		if (CheckHitKey(KEY_INPUT_LCONTROL) == 1) {
			if (ShotLCFlag == 0) {
				ShotDirection(GreenDirection, ShotGFlag, GreenShot, Green, G, GS);
			}
			ShotLCFlag = 1;
		}
		else ShotLCFlag = 0;

		//���F�ƗΐF��\��	
		DrawGraph(Yellow.x, Yellow.y, YellowGraph, FALSE);
		DrawGraph(Green.x, Green.y, GreenGraph, FALSE);
		
		//���F�̑ł������\��
		if (ShotRSFlag == 1) {
			if (ShotYCounter < 0) ShotYCounter = 30;
			else {
				ShotYCounter--;
				if (YellowDirection == 0)
					DrawGraph(Yellow.x + Y.w / 2 - YS.w / 2, Yellow.y - YS.h, ArrowGraph, FALSE);
				else if (YellowDirection == 1)
					DrawRotaGraph(Yellow.x - YS.w / 2, Yellow.y + Y.h / 2, 1.0, -M_PI/ 2, ArrowGraph, FALSE, FALSE, FALSE);
				else if(YellowDirection == 2)
					DrawRotaGraph(Yellow.x + Y.w/2, Yellow.y + Y.h + YS.h / 2, 1.0, M_PI, ArrowGraph, FALSE, FALSE, FALSE);
				else 
					DrawRotaGraph(Yellow.x + Y.w + YS.w / 2, Yellow.y + Y.h / 2, 1.0, M_PI / 2, ArrowGraph, FALSE, FALSE, FALSE);
			}
		}

		//�΂̑ł������\��
		if (ShotLSFlag == 1) {
			if (ShotGCounter < 0) ShotGCounter = 30;
			else {
				ShotGCounter--;
				if (GreenDirection == 0)
					DrawGraph(Green.x + G.w / 2 - GS.w / 2, Green.y - GS.h, ArrowGraph, FALSE);
				else if (GreenDirection == 1)
					DrawRotaGraph(Green.x - GS.w / 2, Green.y + G.h / 2, 1.0, -M_PI / 2, ArrowGraph, FALSE, FALSE, FALSE);
				else if (GreenDirection == 2)
					DrawRotaGraph(Green.x + G.w / 2, Green.y + G.h + GS.h / 2, 1.0, M_PI, ArrowGraph, FALSE, FALSE, FALSE);
				else
					DrawRotaGraph(Green.x + G.w + GS.w / 2, Green.y + G.h / 2, 1.0, M_PI / 2, ArrowGraph, FALSE, FALSE, FALSE);
			}
		}
		

		//�e����ʏ�ɂ���ꍇ�̏���
		for (i = 0; i < 4; i++) {
			for (j = 0; j < N; j++) {
				if (ShotYFlag[i][j] == 1) {
					ShotMove(i, j, YellowShot);

					//��ʊO�ɏo���ꍇ�̏���
					if (RangeJudge(i, j, YellowShot) == 1) ShotYFlag[i][j] = 0;
					DrawGraph(YellowShot[i][j].x, YellowShot[i][j].y, YellowShotGraph, FALSE);
				}

				if (ShotGFlag[i][j] == 1) {
					ShotMove(i, j, GreenShot);

					if (RangeJudge(i, j, GreenShot) == 1) ShotGFlag[i][j] = 0;
					DrawGraph(GreenShot[i][j].x, GreenShot[i][j].y, GreenShotGraph, FALSE);

				}


			}
		}

		for (i = 0; i < 4; i++) {
			for (j = 0; j < N; j++) {
				if (HitBox(Green, G, YellowShot[i][j], YS) == 1) {
					ShotYFlag[i][j] = 0;
				}
				if (HitBox(Yellow, Y, GreenShot[i][j], GS) == 1) {
					ShotGFlag[i][j] = 0;
				}
			}
		}


		
		/*
		//�e���΂ɓ�����������
		for (i = 0; i < N; i++) {
			if (GreenDamageCounter != 5) {
				if (((ShotX[i] > Green.x && ShotX[i] < Green.x + Siw) || (Green.x > ShotX[i] && Green.x < ShotX[i] + Sw)) &&
					((ShotY[i] > Green.y && ShotY[i] < Green.y + Sih) || (Green.y > ShotY[i] && Green.y < ShotY[i] + Sh))) {
					ShotFlag[i] = 0;
					GreenDamageFlag = 1;
				}
			}
		
		}
		*/
		

		ScreenFlip();

		if (ProcessMessage() < 0) break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}



	DxLib_End();

	return 0;
	
}

//���F�̈ړ����[�`��
void YellowMove(Position* pos)
{
	if (CheckHitKey(KEY_INPUT_UP) == 1) pos->y -= speed;
	if (CheckHitKey(KEY_INPUT_DOWN) == 1) pos->y += speed;
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1) pos->x += speed;
	if (CheckHitKey(KEY_INPUT_LEFT) == 1) pos->x -= speed;
}

//�ΐF�̈ړ����[�`��
void GreenMove(Position* pos)
{
	if (CheckHitKey(KEY_INPUT_W) == 1) pos->y -= speed;
	if (CheckHitKey(KEY_INPUT_S) == 1) pos->y += speed;
	if (CheckHitKey(KEY_INPUT_A) == 1) pos->x -= speed;
	if (CheckHitKey(KEY_INPUT_D) == 1) pos->x += speed;
}

//��ʊO����
void RangeSet(Position* pos, Size size)
{
	if (pos->y < 0) pos->y = 0;
	if (pos->y > MAXh - size.h) pos->y = MAXh - size.h;
	if (pos->x < 0) pos->x = 0;
	if (pos->x > MAXw - size.w) pos->x = MAXw - size.w;
}

//�e��ł����̐���
void ShotDirection(int Direction, int ShotFlag[4][N], Position Shot[4][N], Position pos, Size size1, Size size2)
{
	int i;

	for (i = 0; i < N; i++) {
		if (ShotFlag[Direction][i] == 0) {

			//�e�̈ʒu
			if (Direction == 0) {
				Shot[Direction][i].x = pos.x + size1.w / 2 - size2.w / 2;
				Shot[Direction][i].y = pos.y + size2.h;

				ShotFlag[Direction][i] = 1;
			}
			else if (Direction == 1) {
				Shot[Direction][i].x = pos.x - size2.w;
				Shot[Direction][i].y = pos.y + size1.h / 2 - size2.h / 2;

				ShotFlag[Direction][i] = 1;
			}
			else if (Direction == 2) {
				Shot[Direction][i].x = pos.x + size1.w / 2 - size2.w / 2;
				Shot[Direction][i].y = pos.y + size1.h;

				ShotFlag[Direction][i] = 1;
			}
			else {
				Shot[Direction][i].x = pos.x + size1.w;
				Shot[Direction][i].y = pos.y + size1.h / 2 - size2.h / 2;

				ShotFlag[Direction][i] = 1;
			}


			break;
		}
	}
}

//�e�̈ړ����[�`��
void ShotMove(int i, int j, Position Shot[4][N])
{
	switch (i) {
	case 0:
		Shot[i][j].y -= 8;
		break;
	case 1:
		Shot[i][j].x -= 8;
		break;
	case 2:
		Shot[i][j].y += 8;
		break;
	case 3:
		Shot[i][j].x += 8;
		break;
	}
}

//��ʊO����
int RangeJudge(int i, int j, Position Shot[4][N])
{
	if (Shot[i][j].x < 0 || Shot[i][j].y < 0 || Shot[i][j].x > MAXw || Shot[i][j].y > MAXh) return 1;
	else return -1;
}

//�����蔻��
int HitBox(Position pos1, Size size1, Position pos2, Size size2)
{
	//green pos2
	//Shot po1
	if (((pos1.x > pos2.x && pos1.x < pos2.x + size2.w) || (pos2.x > pos1.x && pos2.x < pos1.x + size1.w)) &&
		((pos1.y > pos2.y && pos1.y < pos2.y + size2.h) || (pos2.y > pos1.y && pos2.y < pos1.y + size1.h)))
		return 1;
	else return 0;
}

