#include"Header.h"

int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevlnstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);


	Position Yellow, Green, YellowShot[4][N], GreenShot[4][N]; //�΂Ɖ��F�ƒe�̍��W
	Size Y, G, YS, GS; //���ꂼ��̉摜�T�C�Y
	int i, j;
	int YellowGraph, YellowShotGraph, GreenGraph, GreenShotGraph, ArrowGraph;	//�n���h���ϐ�
	int YellowDamageGraph, GreenDamageGraph;	//�_���[�W�n���h���ϐ�
	int YellowDirection = 0, GreenDirection = 2;	//����0(��),1(��),2(��),3(�E)
	int ShotRCFlag = 0, ShotRSFlag = 0, ShotLSFlag = 0, ShotLCFlag = 0;	//1�t���[����1��̃{�^������
	int ShotYFlag[4][N], ShotGFlag[4][N];	//�e����ʏ�ɕ\������Ă��邩�̏���
	int ShotYCounter = 20, ShotGCounter = 30;	//���̕\���t���[����


	int GreenMuki;
	int GreenDamageFlag, GreenDamageCounter, GreenDamgeGraph;
	int ETamaX, ETamaY, ETamaFlag = 0, ETamaCounter = 0;
	int ShotBFlag = 0;



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
		
		
		//���F�̈ړ����[�`��
		YellowMove(&Yellow);

		//�ΐF�̈ړ����[�`��
		GreenMove(&Green);

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
		if (CheckHitKey(KEY_INPUT_RCONTROL) == 1 ) {
			if (ShotRCFlag == 0) {

				ShotDirection(YellowDirection, ShotYFlag, YellowShot, Yellow, Y, YS);
				/*
				for (i = 0; i < N; i++) {
					if (ShotYFlag[YellowDirection][i] == 0) {

						//�e�̈ʒu
						if (YellowDirection == 0) {
							YellowShot[YellowDirection][i].x = Yellow.x + Y.w / 2 - YS.w / 2;
							YellowShot[YellowDirection][i].y = Yellow.y + YS.h;

							ShotYFlag[YellowDirection][i] = 1;
						}
						else if (YellowDirection == 1) {
							YellowShot[YellowDirection][i].x = Yellow.x - YS.w;
							YellowShot[YellowDirection][i].y = Yellow.y + Y.h / 2 - YS.h / 2;

							ShotYFlag[YellowDirection][i] = 1;
						}
						else if (YellowDirection == 2) {
							YellowShot[YellowDirection][i].x = Yellow.x + Y.w / 2 - YS.w / 2;
							YellowShot[YellowDirection][i].y = Yellow.y + Y.h;

							ShotYFlag[YellowDirection][i] = 1;
						}
						else {
							YellowShot[YellowDirection][i].x = Yellow.x + Y.w;
							YellowShot[YellowDirection][i].y = Yellow.y + Y.h / 2 - YS.h / 2;

							ShotYFlag[YellowDirection][i] = 1;
						}
						

						break;
					}
				}
				*/
				
			}
			//1�t���[���ŋ���ł�������
			ShotRCFlag = 1;
		}
		else ShotRCFlag = 0;

		//���F��\��	
		DrawGraph(Yellow.x, Yellow.y, YellowGraph, FALSE);
		
		//�ł������\��
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

		/*
		//�΂̈ړ����[�`��
		if (GreenDamageFlag == 0) {
			if (GreenMuki == 1) Green.x += 20;
			if (GreenMuki == 0) Green.x -= 20;

			//�ǂɓ��������ꍇ���]
			if (Green.x > 640 - 64) {
				Green.x = 640 - 64;
				GreenMuki = 0;
			}
			else if (Green.x < 0) {
				Green.x = 0;
				GreenMuki = 1;
			}

			ETamaCounter++;

			if (ETamaCounter == 30) {
				ETamaCounter = 0;
				ETamaX = Green.x + Siw / 2 - Sw / 2;
				ETamaY = Green.y + Sih;
				ETamaFlag = 1;
			}

			//�΂�\��
			DrawGraph(Green.x, Green.y, GreenGraph, FALSE);
		}
		else {
			GreenDamageCounter++;
			DrawGraph(Green.x, Green.y, GreenDamgeGraph, FALSE);
			if (GreenDamageCounter == 5) {
				GreenDamageFlag = 0;
				GreenDamageCounter = 0;
			}
		}
		*/

		//�e����ʏ�ɂ���ꍇ�̏���
		for (i = 0; i < 4; i++) {
			for (j = 0; j < N; j++) {
				if (ShotYFlag[i][j] == 1) {
					switch (i) {
					case 0:
						YellowShot[i][j].y -= 8;
						break;
					case 1:
						YellowShot[i][j].x -= 8;
						break;
					case 2:
						YellowShot[i][j].y += 8;
						break;
					case 3:
						YellowShot[i][j].x += 8;
						break;
					}

					//��ʊO�ɏo���ꍇ�̏���
					if (YellowShot[i][j].x < 0 || YellowShot[i][j].y < 0 || YellowShot[i][j].x > MAXw || YellowShot[i][j].y > MAXh) ShotYFlag[i][j] = 0;
					DrawGraph(YellowShot[i][j].x, YellowShot[i][j].y, YellowShotGraph, FALSE);
				}
			}
		}


		/*
		if (ETamaFlag == 1) {
			ETamaY += 16;

			if (ETamaY > 480) {
				ETamaFlag = 0;
			}

			DrawGraph(ETamaX, ETamaY, ETamaGraph, FALSE);
		}

		
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
	if (CheckHitKey(KEY_INPUT_UP) == 1) pos->y -= 3;
	if (CheckHitKey(KEY_INPUT_DOWN) == 1) pos->y += 3;
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1) pos->x += 3;
	if (CheckHitKey(KEY_INPUT_LEFT) == 1) pos->x -= 3;
}

//�ΐF�̈ړ����[�`��
void GreenMove(Position* pos)
{
	if (CheckHitKey(KEY_INPUT_W) == 1) pos->y -= 3;
	if (CheckHitKey(KEY_INPUT_S) == 1) pos->y += 3;
	if (CheckHitKey(KEY_INPUT_A) == 1) pos->x -= 3;
	if (CheckHitKey(KEY_INPUT_D) == 1) pos->x += 3;
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