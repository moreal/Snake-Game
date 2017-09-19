//Snake Game with L V 0.9 Beta

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <direct.h>

#define _CRT_SECURE_NO_WARNINGS
#define SPACE 32
#define ESC 27
#define LEFT 75
#define UP 72
#define RIGHT 77
#define DOWN 80

FILE *f;
int _x = 49, _y = 30; //block_hate() 사용
int j; //배열변수
int key, speed; //키 받아오는 변수와 스피드
int t, ta = 0;
char d = 0;

char dir,ago;
char dif;//difficult =  난이도

int length = 2, point, best_point, p;

short body_x[500] = { 0 }, body_y[500] = { 0 };
short hate_x[10] = { 0 }, hate_y[10] = { 0 };
short x, y;//x,y사용


void gotoxy(int a, int b) //커서 위치를 설정
{
	COORD pos = { a,b };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void printxy(int a, int b, char c[]) //커서위치를 설정하고 입력한다.
{
	gotoxy(a, b);
	printf("%s", c);
}

char length_array(char ch[])
{
	j = 0;
	while (ch[j] != '\0')
	{
		j++;
	}
	return j;
}

void setcolor(int a)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}

void Cursor_out()
{
	CONSOLE_CURSOR_INFO curinfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curinfo);
	curinfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curinfo);
}

void Title()
{
	if (fopen("C:\\GamesL\\SnakeGame\\bestpoint.txt", "r+") == NULL)
	{
		_mkdir("C:\\GamesL");
		_mkdir("C:\\GamesL\\SnakeGame");
		f = fopen("C:\\GamesL\\SnakeGame\\bestpoint.txt", "w");
		fclose(f);
	}
	f = fopen("C:\\GamesL\\SnakeGame\\bestpoint.txt", "r+");
	fscanf(f,"%d\n", &best_point);
	fflush(f);
	fclose(f);
	key = 0;
	system("mode con:cols=50 lines=20");
	system("title Snake Game with L - Title");
	Cursor_out();
	setcolor(15);
	printxy(15, 4, "===스네이크 게임===");
	
	setcolor(11);
	printxy(15, 6, "  ===모드선택===");
	
	setcolor(12);
	printxy(15, 8, "     하드모드\n\t\t      H Key");
	
	setcolor(10);
	printxy(15, 11, "     일반모드\n\t\t      G Key");
	
	setcolor(15);
	gotoxy(3, 16);
	printf(" Developer");
	printf(" likes ");
	setcolor(11);
	printf("Mafumafu");
	setcolor(15);
	printf(", ");
	setcolor(11);
	printf("Reol ");
	setcolor(15);
	printf("and ");
	setcolor(11);
	printf("Hanatan");
	
	setcolor(15);
	printxy(0, 19, "By L\t\t\t\t\t   ver 1.0");
	
	while (1)
	{
		if (_kbhit())
		{
			key = _getch();
			if (key == 104)
			{
				system("mode con:cols=40 lines=10");
				system("title Snake Game with L");
				gotoxy(10, 3);
				setcolor(12);
				printf("하드모드");
				setcolor(15);
				printf("로 시작합니다\n\t취소하려면 ESC를 누르세요");
				Sleep(100);
				for (j = 3; j > 0; j--)
				{
					if(_kbhit()) key = _getch();
					if (key == ESC) Title();
					gotoxy(11, 6);
					printf("%d초 후 시작합니다.",j);
					Sleep(1000);
				}
				speed = 50, dif = 2;
				break;
			}

			if (key == 103)
			{
				system("mode con:cols=40 lines=10");
				system("title Snake Game with L");
				gotoxy(10, 3);
				setcolor(10);
				printf("일반모드");
				setcolor(15);
				printf("로 시작합니다\n\t취소하려면 ESC를 누르세요");
				Sleep(100);
				for (j = 4; j > 0; j--)
				{
					if (_kbhit()) key = _getch();
					if (key == ESC) Title();
					gotoxy(11, 6);
					printf("%d초 후 시작합니다.", j);
					Sleep(1000);
				}
				speed = 200, dif = 2;
				break;
			}
			if (key == ESC) exit(0);
			key = 0;
		}
	}
}

void move()
{
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case 112:
		dir = ago;
		move();
		break;
	}
	
	for (int j = length; j > 0; --j)
	{
		body_x[j] = body_x[j - 1];
		body_y[j] = body_y[j - 1];
	}
		
	body_x[0] = x;
	body_y[0] = y;
	
}

void draw_body()
{
	for (j = 0; j < length; j++)
	{
		printxy(body_x[j]*2, body_y[j], "  ");
	}
	
	move();
	
	for (j = 0; j < length; j++)
	{
		printxy(body_x[j]*2, body_y[j], "■");
	}

	
}

void pause()
{
	while (1)
	{
		if (key == 112)
		{
			printxy(20, 30, "일시정지 당!");
			Sleep(400);
			printxy(20, 30, "           ");
			Sleep(400);
		}
		else
		{
			printxy(20, 30, "즐겜 중이당!");
			return;
		}
		if (_kbhit())
		{
			do {
				key = _getch();
			} while (key == 224);
		}
	}
	
}

void block_hate(char c)
{
	//gotoxy(20, 30);
	//printf("%d", t / 5000);
	if (ta < t / 5000)
	{
		setcolor(12);
		ta += 1;
		for (j = 0; j < c; j++)
		{
			if (hate_x[j] == 0 || hate_y[j] == 0) break;
			printxy(hate_x[j] * 2, hate_y[j], "  ");
			hate_x[j] = 0; hate_y[j] = 0;
		}

		for (d = 0; d < c; d++)
		{
			srand(time(NULL));
			_x = rand() % 48;
			_y = rand() % 29;
			if (!(_x == 0 || _y == 0))
			{
				for (j = 0; j < length; j++)
				{
					while ((body_x[j] == _x && body_y[j] == _y))
					{
						_x = rand() % 48;
						_y = rand() % 29;
					}
				}
				
				for (j = 0; j < 10; j++)
				{
					while (hate_x[j] == _x && hate_y[j] == _y)
					{
						_x = rand() % 48;
						_y = rand() % 29;
						if (hate_x[j] == 0 && hate_y[j] == 0)
							continue;
					}
				}
				
				j = 0;
				while (j < 10)
				{
					if (hate_x[j] == 0 && hate_y[j] == 0)
					{
						break;
					}
					j++;
				}
				hate_x[j] = _x;
				hate_y[j] = _y;
			}
			printxy(hate_x[d] * 2, hate_y[d], "■");
		}
		
		setcolor(15);
	}
}

char check_die()
{
	if (x == 0 || x == 49 || y == 0 || y == 29)
		return 1;
		
	for (j = 1; j < length; j++)
		if (x == body_x[j] && y == body_y[j])
			return 1;
			
	for (j = 0; j < 10; j++)
	{
		if (x == hate_x[j] && y == hate_y[j]) return 1;
		else if (0 == hate_x[j] && 0 == hate_y[j]) break;
	}
	
	return 2;
}

void game_over()
{
	system("mode con:cols=40 lines=18");
	system("title Snake game with L - Lose");
	
	gotoxy(14, 2); printf("-You are "); setcolor(12); printf("Die"); setcolor(15); printf("-");

	Sleep(1000);

	gotoxy(14, 4);
	printf("당신의 점수 :");
	char ch[10];
	_itoa(point, ch, 10);
	gotoxy(20 - (length_array(ch) / 2) - (length_array(ch) % 2), 5); setcolor(11); printf("%d", point); setcolor(15);

	Sleep(1000);

	gotoxy(15, 7);
	printf("최고 점수 :");
	if (best_point < point) best_point = point;
	_itoa(best_point, ch, 10);

	gotoxy(20 - (length_array(ch) / 2) - (length_array(ch) % 2), 8);
	setcolor(11);
	printf("%d", best_point);
	setcolor(15);

	f = fopen("C:\\GamesL\\SnakeGame\\bestpoint.txt", "r+");
	fprintf(f, "%d\n", best_point);
	fflush(f);
	fclose(f);

	Sleep(1000);

	gotoxy(7, 10);
	printf("게임을 다시 하고 싶으시다면\n\t    아무키나 누르세요");

	gotoxy(8, 13);
	printf("바로 종료하고 싶으시다면\n\t     ESC를 누르세요");

	Sleep(1000);

	setcolor(11);
	for (j = 4; j > 0; j--)
	{
		if (_kbhit()) key = _getch();
		if (key == ESC) exit(0);
		if (key != 0 && key != ESC) main();
		gotoxy(12, 16);
		printf("%d초 후 종료합니다.", j);
		gotoxy(8, 17);
		printf("%d초동안 게임을 하셨습니다.", t/1000);
		Sleep(1000);
		key = 0;
	}
	exit(0);
}

int main()
{
	Title();//타이틀
	system("mode con:cols=100 lines=31");
	system("title Snake Game with L - Play");//이름
	
	for (x = 0; x <= 49; x++)//기본바탕을 설정
	{
		for (y = 0; y <= 29; y++)
		{
			if (y == 0 || y == 29 || x == 0 || x == 49)
			{
				printxy(x * 2, y, "■");
			}
			else
			{
				printxy(x * 2, y, "  ");
			}
		}
	}
	
	x = 10, y = 10;
	dir = RIGHT;
	Cursor_out();
	
	body_x[0] = x;
	body_y[0] = y;
	body_x[1] = x - 1;
	body_y[1] = y;

	length = 2;
	point = 0;

	for (j = 0; j < 10; j++)
	{
		hate_x[j] = 0;
		hate_y[j] = 0;
	}
	
	while (1)
	{
		t += speed;
		key = 0;
		gotoxy(6, 30);
		printf("point : %d", point);
		gotoxy(40, 30);
		printf("length : %d", length);
		point += length;
		Sleep(speed);
		if (x==1 && y == 1) point += length;
		if (x == 1 || y == 1 || y == 28 || x == 48) point += length / 2;
		if (_kbhit())
		{
			key = _getch();
			ago = dir;
			
			if (key == 112)
				pause();
				
			if (key == 224)
				key = _getch();
				
			if ((key == LEFT || key == RIGHT || key == UP || key == DOWN || key == 112) && ((dir == LEFT && key != RIGHT) || (dir == RIGHT && key != LEFT) || (dir == UP && key != DOWN) || (dir == DOWN && key != UP)))
				dir = key;
			
			key = 0;
		}
		
		draw_body();
		
		if (dif == 2)
			block_hate(5);
		else
			block_hate(1);

		if ((point%10) == 0) length++;
		
		if (check_die()==1)
		{
			while (_kbhit()) key = _getch();
			game_over();
			return;
		}
		
	}
}
