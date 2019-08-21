#include"Header.h"

int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevlnstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);


	Position Yellow, Green, YellowShot[4][N], GreenShot[4][N]; //緑と黄色と弾の座標
	Position TmpY, TmpG;
	Size Y, G, YS, GS; //それぞれの画像サイズ
	int i, j;
	int YellowGraph, YellowShotGraph, GreenGraph, GreenShotGraph, ArrowGraph;	//ハンドル変数
	int YellowDamageGraph, GreenDamageGraph;	//ダメージハンドル変数
	int YellowDamageFlag, GreenDamageFlag;
	int YellowDirection = 0, GreenDirection = 2;	//方向0(上),1(左),2(下),3(右)
	int ShotRCFlag = 0, ShotRSFlag = 0, ShotLSFlag = 0, ShotLCFlag = 0;	//1フレームに1回のボタン処理
	int ShotYFlag[4][N], ShotGFlag[4][N];	//弾が画面上に表示されているかの処理
	int ShotYCounter = 30, ShotGCounter = 30;	//矢印の表示フレーム数
	int CharCounter = 0;	//画像重複判定


	/*
	int GreenMuki;
	int GreenDamageFlag, GreenDamageCounter, GreenDamgeGraph;
	int ETamaX, ETamaY, ETamaFlag = 0, ETamaCounter = 0;
	int ShotBFlag = 0;
	*/


	//画面モードの設定
	SetGraphMode(MAXw, MAXh, 16);

	//DXライブラリの初期化処理
	if (DxLib_Init() == -1) return -1;
	
	//グラフィックの描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	//グラフィックセット
	YellowGraph = LoadGraph("image/Ball.png");	//黄色のハンドル
	YellowShotGraph = LoadGraph("image/Shot.png");	//黄色の弾のハンドル
	YellowDamageGraph = LoadGraph("image/BallDam.png");	//黄色のダメージハンドル
	GreenGraph = LoadGraph("image/Sikaku.png");	//緑色のハンドル
	GreenShotGraph = LoadGraph("image/EShot.png");	//緑色の弾のハンドル
	GreenDamageGraph = LoadGraph("image/SikakuDam.png");	//緑色のダメージハンドル
	ArrowGraph = LoadGraph("image/Arrow.png");	//矢印のハンドル

	//サイズ取得
	GetGraphSize(YellowGraph, &Y.w, &Y.h);
	GetGraphSize(YellowShotGraph, &YS.w, &YS.h);
	GetGraphSize(GreenGraph, &G.w, &G.h);
	GetGraphSize(GreenShotGraph, &GS.w, &GS.h);

	//黄色の座標軸をセット
	Yellow.x = MAXw - Y.w;
	Yellow.y = MAXh - Y.h;

	//緑の座標軸をセット
	Green.x = 0;
	Green.y = 0;


	//黄色弾と緑弾のショットフラグの初期化
	for (i = 0; i < 4; i++) {
		for (j = 0; j < N; j++) {
			ShotYFlag[i][j] = 0;
			ShotGFlag[i][j] = 0;
		}
	}
	


	//移動ルーチン
	while (1) {
		ClearDrawScreen();

		TmpY = Yellow;
		TmpG = Green;

		//黄色の移動ルーチン
		YellowMove(&Yellow);
		//緑色の移動ルーチン
		GreenMove(&Green);

		if (HitBox(Yellow, Y, Green, G) == 1) {
			Yellow = TmpY;
			Green = TmpG;
		}

		//黄色の球の方向制御
		if (CheckHitKey(KEY_INPUT_RSHIFT) == 1) {
			if (ShotRSFlag == 0) {
				YellowDirection++;
				if (YellowDirection == 4) YellowDirection = 0;
			}
			ShotRSFlag = 1;
		}
		else ShotRSFlag = 0;

		//緑色の弾の方向制御
		if (CheckHitKey(KEY_INPUT_LSHIFT) == 1) {
			if (ShotLSFlag == 0) {
				GreenDirection++;
				if (GreenDirection == 4) GreenDirection = 0;
			}
			ShotLSFlag = 1;
		}
		else ShotLSFlag = 0;


		//**方向確認用コマンド
		if (CheckHitKey(KEY_INPUT_F7) == 1) {

			DrawFormatString(0, 0, GetColor(255, 255, 255), "方向は%d", YellowDirection);

		}

		//範囲外に出たときの処理
		RangeSet(&Yellow, Y);
		RangeSet(&Green, G);


		//黄色の入力によって弾を出す
		if (CheckHitKey(KEY_INPUT_RCONTROL) == 1) {
			if (ShotRCFlag == 0) {
				ShotDirection(YellowDirection, ShotYFlag, YellowShot, Yellow, Y, YS);
			}
			//1フレームで球を打った判定
			ShotRCFlag = 1;
		}
		else ShotRCFlag = 0;

		//緑色の入力によって弾を出す
		if (CheckHitKey(KEY_INPUT_LCONTROL) == 1) {
			if (ShotLCFlag == 0) {
				ShotDirection(GreenDirection, ShotGFlag, GreenShot, Green, G, GS);
			}
			ShotLCFlag = 1;
		}
		else ShotLCFlag = 0;

		//黄色と緑色を表示	
		DrawGraph(Yellow.x, Yellow.y, YellowGraph, FALSE);
		DrawGraph(Green.x, Green.y, GreenGraph, FALSE);
		
		//黄色の打つ方向矢印表示
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

		//緑の打つ方向矢印表示
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
		

		//弾が画面上にある場合の処理
		for (i = 0; i < 4; i++) {
			for (j = 0; j < N; j++) {
				if (ShotYFlag[i][j] == 1) {
					ShotMove(i, j, YellowShot);

					//画面外に出た場合の処理
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
		//弾が緑に当たった判定
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

//黄色の移動ルーチン
void YellowMove(Position* pos)
{
	if (CheckHitKey(KEY_INPUT_UP) == 1) pos->y -= speed;
	if (CheckHitKey(KEY_INPUT_DOWN) == 1) pos->y += speed;
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1) pos->x += speed;
	if (CheckHitKey(KEY_INPUT_LEFT) == 1) pos->x -= speed;
}

//緑色の移動ルーチン
void GreenMove(Position* pos)
{
	if (CheckHitKey(KEY_INPUT_W) == 1) pos->y -= speed;
	if (CheckHitKey(KEY_INPUT_S) == 1) pos->y += speed;
	if (CheckHitKey(KEY_INPUT_A) == 1) pos->x -= speed;
	if (CheckHitKey(KEY_INPUT_D) == 1) pos->x += speed;
}

//画面外判定
void RangeSet(Position* pos, Size size)
{
	if (pos->y < 0) pos->y = 0;
	if (pos->y > MAXh - size.h) pos->y = MAXh - size.h;
	if (pos->x < 0) pos->x = 0;
	if (pos->x > MAXw - size.w) pos->x = MAXw - size.w;
}

//弾を打つ方向の制御
void ShotDirection(int Direction, int ShotFlag[4][N], Position Shot[4][N], Position pos, Size size1, Size size2)
{
	int i;

	for (i = 0; i < N; i++) {
		if (ShotFlag[Direction][i] == 0) {

			//弾の位置
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

//弾の移動ルーチン
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

//画面外判定
int RangeJudge(int i, int j, Position Shot[4][N])
{
	if (Shot[i][j].x < 0 || Shot[i][j].y < 0 || Shot[i][j].x > MAXw || Shot[i][j].y > MAXh) return 1;
	else return -1;
}

//当たり判定
int HitBox(Position pos1, Size size1, Position pos2, Size size2)
{
	//green pos2
	//Shot po1
	if (((pos1.x > pos2.x && pos1.x < pos2.x + size2.w) || (pos2.x > pos1.x && pos2.x < pos1.x + size1.w)) &&
		((pos1.y > pos2.y && pos1.y < pos2.y + size2.h) || (pos2.y > pos1.y && pos2.y < pos1.y + size1.h)))
		return 1;
	else return 0;
}

