#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <math.h>

using namespace std;
const int width = 35;
const int height = 20;
char displayarr[height][width];
int fruitx, fruity;
int score = 0;
bool gameover;
enum Direction {STOP = 0, LEFT, RIGHT, UP, DOWN};
Direction dir;
int snaketail = 1;
char Fruit = 'X';
char snakehead = 'O';
char snakebody = 'o';
int tailx[100], taily[100];

void setup() {
	gameover = false;
	dir = STOP;
	tailx[0] = height / 2;
	taily[0] = width / 2;
	fruitx = rand() % height;
	fruity = rand() % width;
	for (int r = 0; r < 20; r++) {
		for (int c = 0; c < 35; c++) {
			displayarr[r][c] = ' ';
		}
	}
	displayarr[tailx[0]][taily[0]] = snakehead;
	displayarr[fruitx][fruity] = Fruit;
}
void display() {
	system("cls");
	for (int r = 0; r < 20; r++) {
		for (int c = 0; c < 35; c++) {
			displayarr[r][c] = ' ';
		}
	}

	displayarr[tailx[0]][taily[0]] = snakehead;

	for (int i = 1; i < snaketail; i++) {
		displayarr[tailx[i]][taily[i]] = snakebody;
	}
	displayarr[fruitx][fruity] = Fruit;

	for (int i = 0; i < width + 2; i++) {
		cout << "_";
	}
	cout << endl;
	for (int r = 0; r < height; r++) {
		for (int c = 0; c < width; c++) {
			if (c == 0) {
				cout << "|" << displayarr[r][c];
			}
			else if (c == width - 1) {
				cout << displayarr[r][c] << "|" << endl;
			}
			else {
				cout << displayarr[r][c];
			}
		}
	}
	for (int i = 0; i < width + 2; i++) {
		if ((i == 0) || (i == width + 1)) {
			cout << "|";
		}
		else {
			cout << "_";
		}
	}
	cout << endl;
	cout << "Score: " << score;
}
void getinput() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			dir = UP;
			break;
		case 'a':
			dir = LEFT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		}
	}
}
void move() {
	switch (dir) {
	case UP:
		displayarr[tailx[0]][taily[0]] = ' ';
		if (tailx[0] == 0) {
			tailx[0] = height - 1;
		}
		else {
			tailx[0]--;
		}
		break;
	case DOWN:
		displayarr[tailx[0]][taily[0]] = ' ';
		if (tailx[0] == height - 1) {
			tailx[0] = 0;
		}
		else {
			tailx[0]++;
		}
		break;
	case RIGHT:
		displayarr[tailx[0]][taily[0]] = ' ';
		taily[0] = taily[0]++ % width;
		break;
	case LEFT:
		displayarr[tailx[0]][taily[0]] = ' ';
		if (taily[0] == 0) {
			taily[0] = width - 1;
		}
		else {
			taily[0]--;
		}			
		break;
	}
}

void logic() {
	if ((fruitx == tailx[0]) && (fruity == taily[0])) {
		score += 10;
		fruitx = rand() % height;
		fruity = rand() % width;
		snaketail++;	
	}
	if (!(snaketail < 2)) {
		for (int i = 1; i < snaketail; i++) {
			if ((tailx[0] == tailx[i]) && (taily[0] == taily[i])) {
				gameover = true;
			}
		}
	}
}



void tailloc() {
	if (!(snaketail < 2)) {
	int prevx = tailx[0];
	int prevy = taily[0];
	int prev2x, prev2y;
	
		for (int i = 1; i < snaketail; i++) {
			prev2x = tailx[i];
			prev2y = taily[i];
			tailx[i] = prevx;
			taily[i] = prevy;
			prevx = prev2x;
			prevy = prev2y;
		}
	}
}

int main() {
	srand(time(0));
	cout << "Welcome to the Snake Game.\n";
	cout << "You can play as long as you do not try to eat yourself.\n";
	cout << "If you bite yourself you will die from your own venom.\n";
	cout << "use W, A, S, & D to move\n";
	cout << "press any button to continue...";
	system("pause");
	setup();
	while (!(gameover)) {
		getinput();
		tailloc();
		move();
		logic();
		display();
		if ((dir == UP) || (dir == DOWN)) {
			Sleep(40);
		}
		else {
			Sleep(13);
		}
	}
	if (gameover) {
		cout << "GAMEOVER....You bit yourself."
	}
	return 0;
}