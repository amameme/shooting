#include"Header.h"

int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevlnstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);


	Position Yellow, Green, YellowShot[4][N], GreenShot[4][N]; //緑と黄色と弾の座標
	Size Y, G, YS, GS; //それぞれの画像サイズ
	int i, j;
	int YellowGraph, YellowShotGraph, GreenGraph, GreenShotGraph, ArrowGraph;	//ハンドル変数
	int YellowDamageGraph, GreenDamageGraph;	//ダメージハンドル変数
	int YellowDirection = 0, GreenDirection = 2;	//方向0(上),1(左),2(下),3(右)
	int ShotRCFlag = 0, ShotRSFlag = 0, ShotLSFlag = 0, ShotLCFlag = 0;	//1フレームに1回のボタン処理
	int ShotYFlag[4][N], ShotGFlag[4][N];	//弾が画面上に表示されているかの処理
	int ShotYCounter = 20, ShotGCounter = 30;	//矢印の表示フレーム数


	int GreenMuki;
	int GreenDamageFlag, GreenDamageCounter, GreenDamgeGraph;
	int ETamaX, ETamaY, ETamaFlag = 0, ETamaCounter = 0;
	int ShotBFlag = 0;



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
		
		
		//黄色の移動ルーチン
		YellowMove(&Yellow);

		//緑色の移動ルーチン
		GreenMove(&Green);

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
		if (CheckHitKey(KEY_INPUT_RCONTROL) == 1 ) {
			if (ShotRCFlag == 0) {

				ShotDirection(YellowDirection, ShotYFlag, YellowShot, Yellow, Y, YS);
				/*
				for (i = 0; i < N; i++) {
					if (ShotYFlag[YellowDirection][i] == 0) {

						//弾の位置
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
			//1フレームで球を打った判定
			ShotRCFlag = 1;
		}
		else ShotRCFlag = 0;

		//黄色を表示	
		DrawGraph(Yellow.x, Yellow.y, YellowGraph, FALSE);
		
		//打つ方向矢印表示
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
		//緑の移動ルーチン
		if (GreenDamageFlag == 0) {
			if (GreenMuki == 1) Green.x += 20;
			if (GreenMuki == 0) Green.x -= 20;

			//壁に当たった場合反転
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

			//緑を表示
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

		//弾が画面上にある場合の処理
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

					//画面外に出た場合の処理
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
	if (CheckHitKey(KEY_INPUT_UP) == 1) pos->y -= 3;
	if (CheckHitKey(KEY_INPUT_DOWN) == 1) pos->y += 3;
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1) pos->x += 3;
	if (CheckHitKey(KEY_INPUT_LEFT) == 1) pos->x -= 3;
}

//緑色の移動ルーチン
void GreenMove(Position* pos)
{
	if (CheckHitKey(KEY_INPUT_W) == 1) pos->y -= 3;
	if (CheckHitKey(KEY_INPUT_S) == 1) pos->y += 3;
	if (CheckHitKey(KEY_INPUT_A) == 1) pos->x -= 3;
	if (CheckHitKey(KEY_INPUT_D) == 1) pos->x += 3;
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