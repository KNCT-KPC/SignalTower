#include <DxLib.h>
#include <math.h>

int key[256];
int dntputtime = 0;
int gameend = 0;

int gpUpdateKey(void) {
	char tempKey[256];
	int doput = 0;
	GetHitKeyStateAll(tempKey);
	for (int i = 0; i < 256; i++) {
		if (tempKey[i] != 0) {
			key[i] += 1;
			doput = 1;
		}
		else {
			key[i] = 0;
		}
	}

	if (doput == 0) dntputtime++;
	return 0;
}

struct Rank{
	int score = 0;
	char name[10];
} Ranking[4][11];

struct {
	int back = 0;
	int heart = 0;
	int heart2 = 0;
	int fighter = 0;
	int fighter2 = 0;
	int fighter3 = 0;
	int ballEnemy = 0;
	int ballEnemy2 = 0;
	int bossEnemy = 0;
	int bossEnemy2 = 0;
	int enemyFighter = 0;
	int bullet = 0;
	int enemyBullet = 0;


	void SetImage() {
		back = LoadGraph("material/back/background.png");
		heart = LoadGraph("material/back/Heart.png");
		heart2 = LoadGraph("material/back/Heart2.png");
		fighter = LoadGraph("material/chara/Fighter.png");
		fighter2 = LoadGraph("material/chara/Fighter2.png");
		fighter3 = LoadGraph("material/chara/Fighter3.png");
		ballEnemy = LoadGraph("material/chara/BallEnemy.png");
		ballEnemy2 = LoadGraph("material/chara/BallEnemy2.png");
		bossEnemy = LoadGraph("material/chara/BossEnemy.png");
		bossEnemy2 = LoadGraph("material/chara/BossEnemy2.png");
		enemyFighter = LoadGraph("material/chara/EnemyFighter.png");
		bullet = LoadGraph("material/chara/bullet.png");
		enemyBullet = LoadGraph("material/chara/enemyBullet.png");

	}
}Image;

struct base {
private:
	double x = 0;
	double y = 0;
	int speed = 0;
	int graph = 0;
public:
	double X() { return x; }
	void X(double add) { x = x + add * speed; }
	void SetX(int set) { x = set; }

	double Y() { return y; }
	void Y(double add) { y = y + add * speed; }
	void SetY(int set) { y = set; }

	int Speed() { return speed; }
	void Speed(int move) { speed = move; }

	void Graph(int image) { graph = image; }
	int Graph() { return graph; }

	int isHit(int x2, int y2, int width, int height) {
		int SizeX, SizeY;
		GetGraphSize(graph, &SizeX, &SizeY);

		if ((x2 <= x && x < (x2 + width)) || (x2 < (x + SizeX) && (x + SizeX) <= (x2 + width))) {
			if ((y2 <= y && y < (y2 + height)) || (y2 < (y + SizeY) && (y + SizeY) <= (y2 + height))) {
				return 1;
			}
		}

		return 0;
	}
};

struct Bullet {
	base Base;
	int flag = 0;
	double addX = 0;
	double addY = 0;
};

void ResetBullet(Bullet *bullet, int num, int graph, int speed) {
	for (int i = 0; i < num; i++) {
		bullet[i].flag = 0;
		bullet[i].Base.Graph(graph);
		bullet[i].Base.Speed(speed);
	}
}

void background(base *back) {
	if (back->Y() < 480) {
		back->Y(1);
	}
	else if(back->Y() == 480){
		back->Y(-(480 * back->Speed()));
	}
	DrawGraph(back->X(), back->Y(), back->Graph(), TRUE);
	DrawGraph(back->X(), (back->Y() - 480), back->Graph(),TRUE);
}

void Control(int *putkey) {
	putkey[0] = 0;
	putkey[1] = 0;

	if (key[KEY_INPUT_W] > 0) {
		putkey[1]--;
	}

	if (key[KEY_INPUT_S] > 0) {
		putkey[1]++;
	}

	if (key[KEY_INPUT_A] > 0) {
		putkey[0]--;
	}

	if (key[KEY_INPUT_D] > 0) {
		putkey[0]++;
	}
}

void ShowRanking(int x, int y, int gamemode) {
	SetFontThickness(6);
	SetFontSize(30);
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);

	switch (gamemode) {
	case 0: DrawFormatString(x, y, GetColor(80, 250, 50), " ランキング(EASY)"); break;
	case 1: DrawFormatString(x, y, GetColor(80, 250, 50), " ランキング(NORMAL)"); break;
	case 2: DrawFormatString(x, y, GetColor(80, 250, 50), " ランキング(HARD)"); break;
	case 3: DrawFormatString(x, y, GetColor(80, 250, 50), " ランキング(EXPERT)"); break;
	}

	for (int i = 0; i < 10; i++) {
		if (Ranking[gamemode][i].score == 0) {
			DrawFormatString(x, y + (30 * (i + 1)), GetColor(80, 250, 50), "----------");
			DrawFormatString(x + 180, y + (30 * (i + 1)), GetColor(80, 250, 50), ": -----");
		}
		else {
			DrawFormatString(x, y + (30 * (i + 1)), GetColor(80, 250, 50), "%s", Ranking[gamemode][i].name);
			DrawFormatString(x + 180, y + (30 * (i + 1)), GetColor(80, 250, 50), ": %5d", Ranking[gamemode][i].score);
		}
	}
}

void Title(int *here, int *menu, int *cursor, int *gamemode, int *showmode) {
	SetFontThickness(6);
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);

	if (dntputtime == 120) {
		dntputtime = 0;
		*showmode = (*showmode + 1) % 4;
	}

	switch (*menu) {
	case 0:
		SetFontSize(60);
		DrawFormatString(50, 50, GetColor(200, 200, 200), "シューティングゲーム");

		SetFontSize(30);
		switch (*cursor) {
		case 0:
			DrawFormatString(100, 240, GetColor(255, 255, 255), "PLAY");
			DrawFormatString(100, 300, GetColor(100, 100, 100), "RANKING");
			DrawFormatString(100, 360, GetColor(100, 100, 100), "END");
			
			if (key[KEY_INPUT_SPACE] == 1) {
				*menu = 1;
				(*cursor) = 0;
			}
			else {
				if (key[KEY_INPUT_S] == 1) {
					*cursor = *cursor + 1;
				}
				else if (key[KEY_INPUT_W] == 1) {
					*cursor = 2;
				}
			}
			break;
		case 1:
			DrawFormatString(100, 240, GetColor(100, 100, 100), "PLAY");
			DrawFormatString(100, 300, GetColor(255, 255, 255), "RANKING");
			DrawFormatString(100, 360, GetColor(100, 100, 100), "END");
			
			if (key[KEY_INPUT_SPACE] == 1) {
				*menu = 2;
				(*cursor) = 0;
			}
			else {
				if (key[KEY_INPUT_S] == 1) {
					*cursor = *cursor + 1;
				}
				else if (key[KEY_INPUT_W] == 1) {
					*cursor = *cursor - 1;
				}
			}
			break;
		case 2:
			DrawFormatString(100, 240, GetColor(100, 100, 100), "PLAY");
			DrawFormatString(100, 300, GetColor(100, 100, 100), "RANKING");
			DrawFormatString(100, 360, GetColor(255, 255, 255), "END");

			if (key[KEY_INPUT_SPACE] == 1) {
				gameend = 1;
				(*cursor) = 0;
			}
			else {
				if (key[KEY_INPUT_S] == 1) {
					*cursor = 0;
				}
				else if (key[KEY_INPUT_W] == 1) {
					*cursor = *cursor - 1;
				}
			}
			break;
		}

		ShowRanking(400, 120, *showmode);
		break;
	case 1:
		SetFontSize(60);
		DrawFormatString(50, 50, GetColor(100, 100, 100), "シューティングゲーム");

		SetFontSize(30);
		switch (*cursor) {
		case 0:
			DrawFormatString(100, 120, GetColor(255, 255, 255), "EASY");
			DrawFormatString(50, 180, GetColor(255,255,255), "体力:10   連射数:20\n1番カンタン。ゲームが\n苦手な人用");
			DrawFormatString(100, 300, GetColor(100, 100, 100), "NORMAL");
			DrawFormatString(100, 360, GetColor(100, 100, 100), "HARD");

			ShowRanking(400, 120, 0);

			if (key[KEY_INPUT_ESCAPE] == 1) {
				*menu = 0;
				(*cursor) = 0;
			}
			else {
				if (key[KEY_INPUT_S] == 1) {
					if(*cursor < 2) *cursor = *cursor + 1;
				}
				else if (key[KEY_INPUT_W] == 1) {
					if (*cursor > 0) *cursor = *cursor - 1;
				}
			}
			break;
		case 1:
			DrawFormatString(100, 120, GetColor(100, 100, 100), "EASY");
			DrawFormatString(100, 180, GetColor(255, 255, 255), "NORMAL");
			DrawFormatString(50, 240, GetColor(255, 255, 255), "体力:5    連射数:10\n普通。初めてプレイする\n人にオススメ");
			DrawFormatString(100, 360, GetColor(100, 100, 100), "HARD");

			ShowRanking(400, 120, 1);

			if (key[KEY_INPUT_ESCAPE] == 1) {
				*menu = 0;
				(*cursor) = 0;
			}
			else {
				if (key[KEY_INPUT_S] == 1) {
					if (*cursor < 2) *cursor = *cursor + 1;
				}
				else if (key[KEY_INPUT_W] == 1) {
					if (*cursor > 0) *cursor = *cursor - 1;
				}
			}
			break;
		case 2:
			DrawFormatString(100, 120, GetColor(100, 100, 100), "EASY");
			DrawFormatString(100, 180, GetColor(100, 100, 100), "NORMAL");
			DrawFormatString(100, 240, GetColor(255, 255, 255), "HARD");
			DrawFormatString(50, 300, GetColor(255, 255, 255), "体力:3    連射数:5\n最初に選択できる中で\n一番むずかしい。クリア\nするとさらに・・");

			ShowRanking(400, 120, 2);

			if (key[KEY_INPUT_ESCAPE] == 1) {
				*menu = 0;
				(*cursor) = 0;
			}
			else {
				if (key[KEY_INPUT_S] == 1) {
					if (*cursor < 2) *cursor = *cursor + 1;
				}
				else if (key[KEY_INPUT_W] == 1) {
					if (*cursor > 0) *cursor = *cursor - 1;
				}
			}
			break;
		}

		if (key[KEY_INPUT_ESCAPE] == 1) {
			*menu = 0;
			*cursor = 0;
		}
		else if (key[KEY_INPUT_SPACE] == 1) {
			*menu = 0;
			*gamemode = *cursor;
			*cursor = 0;
			*here = 1;
		}
		break;

	case 2:
		SetFontSize(60);
		DrawFormatString(50, 50, GetColor(100, 100, 100), "シューティングゲーム");

		SetFontSize(30);
		switch (*cursor) {
		case 0:
			DrawFormatString(100, 240, GetColor(255, 255, 255), "EASY");
			DrawFormatString(100, 300, GetColor(100, 100, 100), "NORMAL");
			DrawFormatString(100, 360, GetColor(100, 100, 100), "HARD");
			DrawFormatString(100, 420, GetColor(100, 100, 100), "EXPERT");

			ShowRanking(400, 120, 0);

			if (key[KEY_INPUT_ESCAPE] == 1) {
				*menu = 0;
				(*cursor) = 0;
			}
			else {
				if (key[KEY_INPUT_S] == 1) {
					*cursor = (*cursor + 1) % 4;
				}
				else if (key[KEY_INPUT_W] == 1) {
					*cursor = *cursor - 1;
					if (*cursor < 0) *cursor = 3;
				}
			}
			break;
		case 1:
			DrawFormatString(100, 240, GetColor(100, 100, 100), "EASY");
			DrawFormatString(100, 300, GetColor(255, 255, 255), "NORMAL");
			DrawFormatString(100, 360, GetColor(100, 100, 100), "HARD");
			DrawFormatString(100, 420, GetColor(100, 100, 100), "EXPERT");

			ShowRanking(400, 120, 1);

			if (key[KEY_INPUT_ESCAPE] == 1) {
				*menu = 0;
				(*cursor) = 0;
			}
			else {
				if (key[KEY_INPUT_S] == 1) {
					*cursor = (*cursor + 1) % 4;
				}
				else if (key[KEY_INPUT_W] == 1) {
					*cursor = *cursor - 1;
					if (*cursor < 0) *cursor = 3;
				}
			}
			break;
		case 2:
			DrawFormatString(100, 240, GetColor(100, 100, 100), "EASY");
			DrawFormatString(100, 300, GetColor(100, 100, 100), "NORMAL");
			DrawFormatString(100, 360, GetColor(255, 255, 255), "HARD");
			DrawFormatString(100, 420, GetColor(100, 100, 100), "EXPERT");

			ShowRanking(400, 120, 2);

			if (key[KEY_INPUT_ESCAPE] == 1) {
				*menu = 0;
				(*cursor) = 0;
			}
			else {
				if (key[KEY_INPUT_S] == 1) {
					*cursor = (*cursor + 1) % 4;
				}
				else if (key[KEY_INPUT_W] == 1) {
					*cursor = *cursor - 1;
					if (*cursor < 0) *cursor = 3;
				}
			}
			break;
		case 3:
			DrawFormatString(100, 240, GetColor(100, 100, 100), "EASY");
			DrawFormatString(100, 300, GetColor(100, 100, 100), "NORMAL");
			DrawFormatString(100, 360, GetColor(100, 100, 100), "HARD");
			DrawFormatString(100, 420, GetColor(255, 255, 255), "EXPERT");

			ShowRanking(400, 120, 3);

			if (key[KEY_INPUT_ESCAPE] == 1) {
				*menu = 0;
				(*cursor) = 0;
			}
			else {
				if (key[KEY_INPUT_S] == 1) {
					*cursor = (*cursor + 1) % 4;
				}
				else if (key[KEY_INPUT_W] == 1) {
					*cursor = *cursor - 1;
					if (*cursor < 0) *cursor = 3;
				}
			}
			break;
		}
	}
	

}

void GameOver(int *here, int *menu) {
	SetFontThickness(6);
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);
	SetFontSize(60);

	DrawFormatString(200, 50, GetColor(200, 200, 200), "GAME OVER");

	SetFontSize(30);

	DrawFormatString(250, 360, GetColor(255, 255, 255), "タイトルへ");

	if (key[KEY_INPUT_SPACE] == 1) {
		*here = 0;
		*menu = 0;
	}
}

void Menu(int *here, int *menu, int *cursor, int *point, int *time, int *fp) {
	SetFontThickness(6);
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);
	SetFontSize(30);

	switch (*cursor) {
	case 0:
		DrawFormatString(250, 360, GetColor(255, 255, 255), "ゲームに戻る");
		DrawFormatString(250, 420, GetColor(100, 100, 100), "タイトルへ");
		break;
	case 1:
		DrawFormatString(250, 360, GetColor(100, 100, 100), "ゲームに戻る");
		DrawFormatString(250, 420, GetColor(255, 255, 255), "タイトルへ");
		break;
	}

	if (key[KEY_INPUT_S] == 1) {
		if (*cursor == 0) {
			*cursor = 1;
		}
	}
	else if (key[KEY_INPUT_W] == 1) {
		if (*cursor == 1) {
			*cursor = 0;
		}
	}
	else if (key[KEY_INPUT_SPACE] == 1) {
		if (*cursor == 0) {
			*cursor = 0;
			*here = 1;
			*menu = 1;
			*time = point[2];
			fp[0] = point[3];
		}
		else {
			*cursor = 0;
			*here = 0;
			*menu = 1;
		}
	}
}

void Sort(int gamemode) {
	Rank rank;

	for (int i = 0; i < 10; i++) {
		for (int j = i + 1; j < 10; j++) {
			if (Ranking[gamemode][i].score < Ranking[gamemode][j].score) {
				rank = Ranking[gamemode][i];
				Ranking[gamemode][i] = Ranking[gamemode][j];
				Ranking[gamemode][j] = rank;
			}
		}
	}
	
}

void GameClear(int *here, int *menu, int *score, int *gamemode, int *HP) {
	SetFontThickness(6);
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);
	SetFontSize(60);

	DrawFormatString(25, 50, GetColor(200, 200, 200), "名前を入力してください。");
	score[1] = score[1] + score[2] + (*HP * 100);
	SetFontSize(30);
 	for (int i = 0; i < 10; i++) {

			if (Ranking[*gamemode][i].score == 0) {
				KeyInputSingleCharString(100, 150, 10, Ranking[*gamemode][i].name, FALSE);
				Ranking[*gamemode][i].score = score[1];
				break;
			}
			else if(i == 9){
				for (int j = 0; j < 10; j++) {
					if (Ranking[*gamemode][j].score < score[1]) {
						KeyInputSingleCharString(100, 150, 10, Ranking[*gamemode][i].name, FALSE);
						Ranking[*gamemode][j].score = score[1];
						break;
					}
				}
			}
		
	}

	Sort(*gamemode);
	*here = 0;
	*menu = 0;

	if (*gamemode == 2) {
		*here = 1;
		*gamemode = 3;
	}

}

int Score(int *score) {
	if (score[0] < score[1]) {
		score[0] = score[0] + 10;
	}

	return score[0];
}

void ControlFighter(base *chara) {
	int putkey[2];

	Control(putkey);

	if ((chara->X() + (chara->Speed() * putkey[0])) < 0) {
		chara->SetX(0);
	}
	else if (624 < (chara->X() + (chara->Speed() * putkey[0]))) {
		chara->SetX(624);
	}
	else {
		chara->X(putkey[0]);
	}

	if ((chara->Y() + (chara->Speed() * putkey[1])) < 0) {
		chara->SetY(0);
	}
	else if (384 < (chara->Y() + (chara->Speed() * putkey[1]))) {
		chara->SetY(384);
	}
	else {
		chara->Y(putkey[1]);
	}
}

void Shot(base *chara, Bullet *bullet, int *fp, int *point, int tama) {
	for (int i = 0; i < 100; i++) {
		if (bullet[i].flag == 1) {
			bullet[i].Base.Y(-1);

			if (bullet[i].Base.isHit(0, 0, 720, 480) == 0) {
				bullet[i].flag = 0;
			}
		}
	}

	if (key[KEY_INPUT_SPACE] > 0) {
		if (point[1] < tama && fp[1] == 0) {
			point[1]++;
			fp[1] = 1;
			fp[2] = 1;

			for (int i = 0; i < 100; i++) {
				if (bullet[i].flag == 0) {
					bullet[i].flag = 1;
					bullet[i].Base.SetX(chara->X() + 42);
					bullet[i].Base.SetY(chara->Y() - 12);
					break;
				}
			}
		}
	}

	for (int i = 0; i < 100; i++) {
		if (bullet[i].flag == 1) {
			DrawGraph(bullet[i].Base.X(), bullet[i].Base.Y(), bullet[i].Base.Graph(), TRUE);
		}
	}

	if (fp[1] >= 10) {
		fp[1] = 0;
	}

	if (fp[2] >= 120) {
		point[1] = 0;
		fp[2] = 0;
	}
}

void EnemyShot(base *chara, Bullet *bullet, int mode, int x, int y, int w, int h) {
	switch (mode) {
	case 0:
		for (int i = 0; i < 100; i++) {
			if (bullet[i].flag == 0) {
				bullet[i].flag = 1;
				bullet[i].Base.SetX(x + ((w / 2) - 6));
				bullet[i].Base.SetY(y + ((h / 2) - 6));
				bullet[i].addX = (((chara->X() + 24) - (x + ((w / 2) - 6))) ) / sqrt(((chara->X() + 24) - (x + ((w / 2) - 6))) * ((chara->X() + 24) - (x + ((w / 2) - 6))) + ((chara->Y() + 24) - (y + ((h / 2) - 6))) * ((chara->Y() + 24) - (y + ((h / 2) - 6))));
				bullet[i].addY = (((chara->Y() + 24) - (y + ((h / 2) - 6))) ) / sqrt(((chara->X() + 24) - (x + ((w / 2) - 6))) * ((chara->X() + 24) - (x + ((w / 2) - 6))) + ((chara->Y() + 24) - (y + ((h / 2) - 6))) * ((chara->Y() + 24) - (y + ((h / 2) - 6))));
				break;
			}
		}
		break;
	case 1:
		for (int i = 0; i < 100; i++) {
			if (bullet[i].flag == 0) {
				bullet[i].flag = 1;
				bullet[i].Base.SetX(x + ((w / 2) - 6));
				bullet[i].Base.SetY(y + ((h / 2) - 6));
				bullet[i].addX = 0;
				bullet[i].addY = -1;
				break;
			}
		}

		for (int i = 0; i < 100; i++) {
			if (bullet[i].flag == 0) {
				bullet[i].flag = 1;
				bullet[i].Base.SetX(x + ((w / 2) - 6));
				bullet[i].Base.SetY(y + ((h / 2) - 6));
				bullet[i].addX = 1;
				bullet[i].addY = -1;
				break;
			}
		}

		for (int i = 0; i < 100; i++) {
			if (bullet[i].flag == 0) {
				bullet[i].flag = 1;
				bullet[i].Base.SetX(x + ((w / 2) - 6));
				bullet[i].Base.SetY(y + ((h / 2) - 6));
				bullet[i].addX = 1;
				bullet[i].addY = 0;
				break;
			}
		}

		for (int i = 0; i < 100; i++) {
			if (bullet[i].flag == 0) {
				bullet[i].flag = 1;
				bullet[i].Base.SetX(x + ((w / 2) - 6));
				bullet[i].Base.SetY(y + ((h / 2) - 6));
				bullet[i].addX = 1;
				bullet[i].addY = 1;
				break;
			}
		}

		for (int i = 0; i < 100; i++) {
			if (bullet[i].flag == 0) {
				bullet[i].flag = 1;
				bullet[i].Base.SetX(x + ((w / 2) - 6));
				bullet[i].Base.SetY(y + ((h / 2) - 6));
				bullet[i].addX = 0;
				bullet[i].addY = 1;
				break;
			}
		}

		for (int i = 0; i < 100; i++) {
			if (bullet[i].flag == 0) {
				bullet[i].flag = 1;
				bullet[i].Base.SetX(x + ((w / 2) - 6));
				bullet[i].Base.SetY(y + ((h / 2) - 6));
				bullet[i].addX = -1;
				bullet[i].addY = 1;
				break;
			}
		}

		for (int i = 0; i < 100; i++) {
			if (bullet[i].flag == 0) {
				bullet[i].flag = 1;
				bullet[i].Base.SetX(x + ((w / 2) - 6));
				bullet[i].Base.SetY(y + ((h / 2) - 6));
				bullet[i].addX = -1;
				bullet[i].addY = 0;
				break;
			}
		}

		for (int i = 0; i < 100; i++) {
			if (bullet[i].flag == 0) {
				bullet[i].flag = 1;
				bullet[i].Base.SetX(x + ((w / 2) - 6));
				bullet[i].Base.SetY(y + ((h / 2) - 6));
				bullet[i].addX = -1;
				bullet[i].addY = -1;
				break;
			}
		}
		break;
	}
}

int HowManyHit(int x, int y, int w, int h, Bullet *bullet) {
	int hit = 0;
	for (int i = 0; i < 100; i++) {
		if (bullet[i].flag == 1) {
			if (bullet[i].Base.isHit(x, y, w, h) == 1) {
				hit++;
				bullet[i].flag = 0;
			}
		}
	}

	return hit;
}

void EnemyBullet(base *chara, Bullet *bullet, int *fp, int *HP) {
	int hit = HowManyHit(chara->X() + 35, chara->Y(), 26, 96, bullet);
	if (hit > 0) {
		*HP = *HP - 1;
		fp[10] = 1;
	}

	for (int i = 0; i < 100; i++) {
		if (bullet[i].flag == 1) {
			DrawGraph(bullet[i].Base.X(), bullet[i].Base.Y(), bullet[i].Base.Graph(), TRUE);
		}
	}

	for (int i = 0; i < 100; i++) {
		if (bullet[i].flag == 1) {
			bullet[i].Base.X(bullet[i].addX);
			bullet[i].Base.Y(bullet[i].addY);

			if (bullet[i].Base.isHit(0, 0, 720, 480) == 0) {
				bullet[i].flag = 0;
			}
		}
	}
}

void ShowHP(int HP, int maxHP) {
	for (int i = 0; i < maxHP; i++) {
		if (HP > i) {
			DrawGraph(24 * i, 24, Image.heart, TRUE);
		}
		else {
			DrawGraph(24 * i, 24, Image.heart2, TRUE);
		}
	}
}

void Enemy(int image, int *fp, int *point, int num, int x, int w, int h, int *score, base *chara, base *fighter, Bullet **bullet, int addscore) {
	if (point[num] > 0) {
		if (fp[num] == 0) {
			fp[num] = 1;
			chara->Graph(image);
			chara->SetX(x);
			chara->SetY(-h);
			chara->Speed(1);
		}
		int hit = HowManyHit(chara->X(), chara->Y(), w, h, bullet[0]);

		if (hit > 0) {
			point[num] = point[num] - hit;
			fp[num + 10] = 1;
		}

		if ((fp[num + 10] % 2) || fp[num + 10] == 0) {
			DrawGraph(chara->X(), chara->Y(), chara->Graph(), TRUE);
		}
		else if (fp[num + 10] > 5) {
			fp[num + 10] = 0;
		}

		if (point[num] == 0) {
			fp[num] = 0;
			score[1] = score[1] + addscore;
		}
		else if (chara->Y() > 480) {
			point[num] = 0;
		}
	}
}

void BallEnemyType1(int *fp, int *point, int num, int x, int *score, base *chara, base *fighter, Bullet **bullet) {
	Enemy(Image.ballEnemy, fp, point, num, x, 48, 48, score, chara, fighter, bullet, 100);
	if (point[num] > 0) {
		if (fp[num] % 240 < 120) {
			chara->Y(1);
		}
		else if (fp[num] % 120 == 0) {
			EnemyShot(fighter, bullet[1], 0, chara->X(), chara->Y(), 48, 48);
		}
	}
}

void BallEnemyType2(int *fp, int *point, int num, int x, int *score, base *chara, base *fighter, Bullet **bullet) {
	Enemy(Image.ballEnemy, fp, point, num, x, 48, 48, score, chara, fighter, bullet, 100);
	if (point[num] > 0) {
		if (fp[num] % 240 < 120) {
			chara->Y(1);
		}
		
		if (fp[num] % 120 == 0) {
			EnemyShot(fighter, bullet[1], 0, chara->X(), chara->Y(), 48, 48);
		}
		else if (fp[num] % 120 == 60) {
			EnemyShot(fighter, bullet[1], 1, chara->X(), chara->Y(), 48, 48);
		}
	}
}

void BossEnemyType1(int *fp, int *point, int num, int x, int *score, base *chara, base *fighter, Bullet **bullet) {
	Enemy(Image.bossEnemy, fp, point, num, x, 96, 96, score, chara, fighter, bullet, 1000);
	if (point[num] > 0) {
		chara->Speed(3);

		if (chara->Y() < 96) {
			chara->Y(1);
			point[num + 10] = 0;
		}
		else {
			if (fp[num] % 120 == 0) {
				EnemyShot(fighter, bullet[1], 0, chara->X(), chara->Y(), 96, 96);
			}

			if (point[num + 10] == 0) {
				chara->X(-1);
			}
			else {
				chara->X(1);
			}

			if (chara->X() > 600) {
				point[num + 10] = 0;
			}
			else if (chara->X() < 24) {
				point[num + 10] = 1;
			}
		}
	}
}

void BossEnemyType2(int *fp, int *point, int num, int x, int *score, base *chara, base *fighter, Bullet **bullet) {
	Enemy(Image.bossEnemy, fp, point, num, x, 96, 96, score, chara, fighter, bullet, 1000);
	if (point[num] > 0) {
		chara->Speed(3);

		if (chara->Y() < 96) {
			chara->Y(1);
			point[num + 10] = 0;
		}
		else {
			if (fp[num] % 60 == 0) {
				EnemyShot(fighter, bullet[1], 1, chara->X(), chara->Y(), 96, 96);
			}

			if (point[num + 10] == 0) {
				chara->X(-1);
			}
			else {
				chara->X(1);
			}

			if (chara->X() > 600) {
				point[num + 10] = 0;
			}
			else if (chara->X() < 24) {
				point[num + 10] = 1;
			}
		}
	}
}

void EnemyFighterEnemyType1(int *fp, int *point, int num, int x, int *score, base *chara, base *fighter, Bullet **bullet) {
	Enemy(Image.enemyFighter, fp, point, num, x, 96, 96, score, chara, fighter, bullet, 3000);
	if (point[num] > 0) {
		chara->Speed(3);

		if (chara->Y() < 96) {
			chara->Y(1);
			point[num + 10] = 0;
		}
		else {
			if (fp[num] % 120 == 0) {
				EnemyShot(fighter, bullet[1], 0, chara->X(), chara->Y(), 96, 96);
			}

			if (point[num + 10] == 0) {
				chara->X(-1);
			}
			else {
				chara->X(1);
			}

			if (chara->X() > 600) {
				point[num + 10] = 0;
			}
			else if (chara->X() < 24) {
				point[num + 10] = 1;
			}
		}
	}
}

void EnemyFighterEnemyType2(int *fp, int *point, int num, int x, int *score, base *chara, base *fighter, Bullet **bullet) {
	Enemy(Image.enemyFighter, fp, point, num, x, 96, 96, score, chara, fighter, bullet, 3000);
	if (point[num] > 0) {
		chara->Speed(5);

		if (chara->Y() < 96) {
			chara->Y(1);
			point[num + 10] = 0;
		}
		else {
			if (fp[num] % 120 == 0) {
				EnemyShot(fighter, bullet[1], 0, chara->X(), chara->Y(), 96, 96);
				EnemyShot(fighter, bullet[1], 1, chara->X(), chara->Y(), 96, 96);
			}

			if (point[num + 10] == 0) {
				chara->X(-1);
			}
			else {
				chara->X(1);
			}

			if (chara->X() > 600) {
				point[num + 10] = 0;
			}
			else if (chara->X() < 24) {
				point[num + 10] = 1;
			}
		}
	}
}

void EnemyFighterEnemyType3(int *fp, int *point, int num, int x, int *score, base *chara, base *fighter, Bullet **bullet) {
	Enemy(Image.enemyFighter, fp, point, num, x, 96, 96, score, chara, fighter, bullet, 3000);
	if (point[num] > 0) {
		chara->Speed(5);

		if (chara->Y() < 96) {
			chara->Y(1);
			point[num + 10] = 0;
		}
		else {
			if (fp[num] % 60 == 0) {
				EnemyShot(fighter, bullet[1], 0, chara->X(), chara->Y(), 96, 96);
				EnemyShot(fighter, bullet[1], 1, chara->X(), chara->Y(), 96, 96);
			}
			else if (fp[num] % 60 == 30) {
				EnemyShot(fighter, bullet[1], 0, chara->X(), chara->Y(), 96, 96);
			}

			if (point[num + 10] == 0) {
				chara->X(-1);
			}
			else {
				chara->X(1);
			}

			if (chara->X() > 600) {
				point[num + 10] = 0;
			}
			else if (chara->X() < 24) {
				point[num + 10] = 1;
			}
		}
	}
}

void Easy(int *menu, int *cursor, int *fp, int *point, int *time, int *gamemode, int *score, base **chara, Bullet **item, int *HP, int *here) {
	if (*menu == 0) {
		for (int i = 0; i < 100; i++) {
			fp[i] = 0;
			point[i] = 0;
		}

		*time = 500;
		score[0] = 0;
		score[1] = 0;

		chara[0]->Graph(Image.fighter);
		chara[0]->Speed(5);
		chara[0]->SetX(264);
		chara[0]->SetY(384);

		*HP = 10;

		point[11] = 5;
		point[12] = 5;
		point[13] = 10;
		point[14] = 5;
		point[15] = 5;
		point[16] = 20;

		ResetBullet(item[0], 100, Image.bullet, 10);
		ResetBullet(item[1], 100, Image.enemyBullet, 5);
		*menu = 1;
	}
	EnemyBullet(chara[0], item[1], fp, HP);

	if (*time < 500) {
		BallEnemyType1(fp, point, 11, 540, score, chara[1], chara[0], item);
	}

	if (*time < 450 || point[11] == 0) {
		BallEnemyType1(fp, point, 12, 180, score, &(chara[1][2]), chara[0], item);
	}

	if (*time < 440 || (point[11] == 0 && point[12] == 0)) {
		BossEnemyType1(fp,point, 13, 312, score, &(chara[1][3]), chara[0], item);
	}

	if (point[13] == 0) {
		if (point[0] == 0) {
			point[0] = *time;
		}
		BallEnemyType1(fp, point, 14, 180, score, &(chara[1][4]), chara[0], item);
	}

	if (*time < point[0] - 10 || point[14] == 0) {
		BallEnemyType1(fp, point, 15, 540, score, &(chara[1][5]), chara[0], item);
	}

	if (*time < point[0] - 20 || (point[14] == 0 && point[15] == 0)) {
		EnemyFighterEnemyType1(fp, point, 16, 312, score, &(chara[1][6]), chara[0], item);
	}

	if (point[16] == 0) {
		if (score[0] == score[1]) {
			*here = 3;
			score[2] = *time;
		}
		else {
			if (key[KEY_INPUT_SPACE] == 1) {
				score[0] = score[1];
			}
		}
	}

	ControlFighter(chara[0]);
	Shot(chara[0], item[0], fp, point, 20);

	if ((fp[10] % 2) || fp[10] == 0) {
		DrawGraph(chara[0]->X(), chara[0]->Y(), chara[0]->Graph(), TRUE);
	}
	else if (fp[10] > 5) {
		fp[10] = 0;
	}



	ShowHP(*HP, 10);
	if (*HP == 0) {
		*here = 2;
	}
}

void Normal(int *menu, int *cursor, int *fp, int *point, int *time, int *gamemode, int *score, base **chara, Bullet **item, int *HP, int *here) {
	if (*menu == 0) {
		for (int i = 0; i < 100; i++) {
			fp[i] = 0;
			point[i] = 0;
		}

		*time = 500;
		score[0] = 0;
		score[1] = 0;

		chara[0]->Graph(Image.fighter);
		chara[0]->Speed(5);
		chara[0]->SetX(264);
		chara[0]->SetY(384);

		*HP = 5;

		point[11] = 5;
		point[12] = 5;
		point[13] = 10;
		point[14] = 5;
		point[15] = 5;
		point[16] = 20;

		ResetBullet(item[0], 100, Image.bullet, 10);
		ResetBullet(item[1], 100, Image.enemyBullet, 5);
		*menu = 1;
	}
	EnemyBullet(chara[0], item[1], fp, HP);

	if (*time < 500) {
		BallEnemyType1(fp, point, 11, 540, score, chara[1], chara[0], item);
	}

	if (*time < 450 || point[11] == 0) {
		BallEnemyType1(fp, point, 12, 180, score, &(chara[1][2]), chara[0], item);
	}

	if (*time < 440 || (point[11] == 0 && point[12] == 0)) {
		BossEnemyType2(fp, point, 13, 312, score, &(chara[1][3]), chara[0], item);
	}

	if (point[13] == 0) {
		if (point[0] == 0) {
			point[0] = *time;
		}
		BallEnemyType1(fp, point, 14, 180, score, &(chara[1][4]), chara[0], item);
	}

	if (*time < point[0] - 10 || point[14] == 0) {
		BallEnemyType1(fp, point, 15, 540, score, &(chara[1][5]), chara[0], item);
	}

	if (*time < point[0] - 20 || (point[14] == 0 && point[15] == 0)) {
		EnemyFighterEnemyType2(fp, point, 16, 312, score, &(chara[1][6]), chara[0], item);
	}

	if (point[16] == 0) {
		if (score[0] == score[1]) {
			*here = 3;
			score[2] = *time;
		}
		else {
			if (key[KEY_INPUT_SPACE] == 1) {
				score[0] = score[1];
			}
		}
	}

	ControlFighter(chara[0]);
	Shot(chara[0], item[0], fp, point, 10);

	if ((fp[10] % 2) || fp[10] == 0) {
		DrawGraph(chara[0]->X(), chara[0]->Y(), chara[0]->Graph(), TRUE);
	}
	else if (fp[10] > 5) {
		fp[10] = 0;
	}



	ShowHP(*HP, 5);
	if (*HP == 0) {
		*here = 2;
	}
}

void Hard(int *menu, int *cursor, int *fp, int *point, int *time, int *gamemode, int *score, base **chara, Bullet **item, int *HP, int *here) {
	if (*menu == 0) {
		for (int i = 0; i < 100; i++) {
			fp[i] = 0;
			point[i] = 0;
		}

		*time = 500;
		score[0] = 0;
		score[1] = 0;

		chara[0]->Graph(Image.fighter);
		chara[0]->Speed(5);
		chara[0]->SetX(264);
		chara[0]->SetY(384);

		*HP = 3;

		point[11] = 5;
		point[12] = 5;
		point[13] = 10;
		point[14] = 5;
		point[15] = 5;
		point[16] = 20;

		ResetBullet(item[0], 100, Image.bullet, 10);
		ResetBullet(item[1], 100, Image.enemyBullet, 5);
		*menu = 1;
	}
	EnemyBullet(chara[0], item[1], fp, HP);

	if (*time < 500) {
		BallEnemyType1(fp, point, 11, 540, score, chara[1], chara[0], item);
	}

	if (*time < 450 || point[11] == 0) {
		BallEnemyType1(fp, point, 12, 180, score, &(chara[1][2]), chara[0], item);
	}

	if (*time < 440 || (point[11] == 0 && point[12] == 0)) {
		BossEnemyType2(fp, point, 13, 312, score, &(chara[1][3]), chara[0], item);
	}

	if (point[13] == 0) {
		if (point[0] == 0) {
			point[0] = *time;
		}
		BallEnemyType1(fp, point, 14, 180, score, &(chara[1][4]), chara[0], item);
	}

	if (*time < point[0] - 10 || point[14] == 0) {
		BallEnemyType1(fp, point, 15, 540, score, &(chara[1][5]), chara[0], item);
	}

	if (*time < point[0] - 20 || (point[14] == 0 && point[15] == 0)) {
		EnemyFighterEnemyType2(fp, point, 16, 540, score, &(chara[1][6]), chara[0], item);
	}

	if (point[16] == 0) {
		if (score[0] == score[1]) {
			*here = 3;
			score[2] = *time;
		}
		else {
			if (key[KEY_INPUT_SPACE] == 1) {
				score[0] = score[1];
			}
		}
	}

	ControlFighter(chara[0]);
	Shot(chara[0], item[0], fp, point, 5);

	if ((fp[10] % 2) || fp[10] == 0) {
		DrawGraph(chara[0]->X(), chara[0]->Y(), chara[0]->Graph(), TRUE);
	}
	else if (fp[10] > 5) {
		fp[10] = 0;
	}



	ShowHP(*HP, 3);
	if (*HP == 0) {
		*here = 2;
	}
}

void Expert(int *menu, int *cursor, int *fp, int *point, int *time, int *gamemode, int *score, base **chara, Bullet **item, int *HP, int *here) {
	if (*menu == 0) {
		for (int i = 0; i < 100; i++) {
			fp[i] = 0;
			point[i] = 0;
		}

		*time = 500;
		score[0] = 0;
		score[1] = 0;

		chara[0]->Graph(Image.fighter);
		chara[0]->Speed(5);
		chara[0]->SetX(264);
		chara[0]->SetY(384);

		*HP = 3;

		point[11] = 5;
		point[12] = 5;
		point[13] = 10;
		point[14] = 5;
		point[15] = 5;
		point[16] = 20;

		ResetBullet(item[0], 100, Image.bullet, 10);
		ResetBullet(item[1], 100, Image.enemyBullet, 5);
		*menu = 1;
	}
	EnemyBullet(chara[0], item[1], fp, HP);

	if (*time < 500) {
		BallEnemyType2(fp, point, 11, 540, score, chara[1], chara[0], item);
	}

	if (*time < 450 || point[11] == 0) {
		BallEnemyType2(fp, point, 12, 180, score, &(chara[1][2]), chara[0], item);
	}

	if (*time < 440 || (point[11] == 0 && point[12] == 0)) {
		BossEnemyType2(fp, point, 13, 312, score, &(chara[1][3]), chara[0], item);
	}

	if (point[13] == 0) {
		if (point[0] == 0) {
			point[0] = *time;
		}
		BallEnemyType2(fp, point, 14, 180, score, &(chara[1][4]), chara[0], item);
	}

	if (*time < point[0] - 10 || point[14] == 0) {
		BallEnemyType2(fp, point, 15, 540, score, &(chara[1][5]), chara[0], item);
	}

	if (*time < point[0] - 20 || (point[14] == 0 && point[15] == 0)) {
		EnemyFighterEnemyType3(fp, point, 16, 312, score, &(chara[1][6]), chara[0], item);
	}

	if (point[16] == 0) {
		if (score[0] == score[1]) {
			*here = 3;
			score[2] = *time;
		}
		else {
			if (key[KEY_INPUT_SPACE] == 1) {
				score[0] = score[1];
			}
		}
	}

	ControlFighter(chara[0]);
	Shot(chara[0], item[0], fp, point, 2);

	if ((fp[10] % 2) || fp[10] == 0) {
		DrawGraph(chara[0]->X(), chara[0]->Y(), chara[0]->Graph(), TRUE);
	}
	else if (fp[10] > 5) {
		fp[10] = 0;
	}



	ShowHP(*HP, 3);
	if (*HP == 0) {
		*here = 2;
	}
}

void Game(int *menu, int *cursor, int *fp, int *point, int *time, int *gamemode, int *score, base **chara, Bullet **item, int *HP, int *here) {
	SetFontThickness(6);
	SetFontSize(30);
	if (*menu == 3) {
		Menu(here, menu, cursor, point, time, fp);
	}
	else {
		switch (*gamemode) {
		case 0:
			Easy(menu, cursor, fp, point, time, gamemode, score, chara, item, HP, here);
			break;
		case 1:
			Normal(menu, cursor, fp, point, time, gamemode, score, chara, item, HP, here);
			break;
		case 2:
			Hard(menu, cursor, fp, point, time, gamemode, score, chara, item, HP, here);
			break;
		case 3:
			Expert(menu, cursor, fp, point, time, gamemode, score, chara, item, HP, here);
			break;
		}

		DrawFormatString(0, 0, GetColor(200, 200, 200), "TIME %d:%02d  SCORE %d", (*time / 100), (*time % 100), Score(score));
		if (fp[0] == 0) {
			fp[0] = 1;
		}
		else if (*time < 0) {
			fp[0] = 0;
			*here = 2;
		}
		else if (fp[0] >= 60) {
			fp[0] = 1;
			if ((*time % 100) == 0) {
				*time = *time - 41;
			}
			else {
				*time = *time - 1;
			}
		}

		if (key[KEY_INPUT_ESCAPE] == 1) {
			point[2] = *time;
			point[3] = fp[0];
			*menu = 3;
		}
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR  lpCmdLine, int nCmdShow) {
	ChangeWindowMode(TRUE);
	int fp[100];
	int point[100];

	for (int i = 0; i < 100; i++) {
		fp[i] = 0;
		point[i] = 0;
	}

	FILE *file;
	fopen_s(&file, "save.txt", "r");
	if (file != NULL) {
		fread(Ranking, sizeof(Ranking), 1, file);
	}
	fclose(file);

	int time = 500;
	int score[3] = {0, 0, 0};
	int heart = 0;
	int here = 0;
	int menu = 0;
	int cursor = 0;
	int gamemode = 0;
	int showmode = 0;
	int HP = 0;

	base *chara[2];
	Bullet *item[3];

	base back;
	base fighter;
	base enemy[10];

	Bullet fighterBullet[100];
	Bullet enemyBullet[100];

	chara[0] = &fighter;
	chara[1] = enemy;
	item[0] = fighterBullet;
	item[1] = enemyBullet;
	SetGraphMode(720, 480, 32);

	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);
	Image.SetImage();

	back.Graph(Image.back);
	back.Speed(1);

	while (!ProcessMessage() && !gpUpdateKey() && !ScreenFlip()) {
		for (int i = 0; i < 100; i++) {
			if (fp[i] > 0) fp[i]++;
		}
		ClearDrawScreen();
		background(&back);

		switch (here) {
		case 0:
			Title(&here, &menu, &cursor, &gamemode, &showmode);
			break;
		case 1:
			Game(&menu, &cursor, fp, point, &time, &gamemode, score, chara, item, &HP, &here);
			break;
		case 2:
			GameOver(&here, &menu);
			break;
		case 3:
			GameClear(&here, &menu, score, &gamemode, &HP);
			fopen_s(&file, "save.txt", "w");
			fwrite(Ranking, sizeof(Ranking), 1, file);
			fclose(file);
			break;
		}
		if (gameend == 1) break;
	}
	
	DxLib_End();
	return 0;
}