//Snake Game with L V 1.0 Beta

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
#define P 112

FILE *f;

int _x = 49, _y = 30; //block_hate() ���
char j, d, o = 0; //�迭����
int key, speed; //Ű �޾ƿ��� ������ ���ǵ�
int t, ta = 0; //�ð�

char dir, ago; // ���Ⱚ(+���Ź��Ⱚ
char dif; //difficult =  ���̵�

int length = 2, point, best_point, p, nBlock;

short body_x[500] = { 0 }, body_y[500] = { 0 }; //����(body) ��ǥ
short hate_x[20] = { 0 }, hate_y[20] = { 0 }; //��ֹ� �� ��ǥ
short x, y;//x,y���


void check_level()
{
	if ((speed >= 30) && (ta % 5 == 0)) speed -= 10, nBlock += 1;
	return;
}

void gotoxy(int a, int b) //Ŀ�� ��ġ�� ����
{
	COORD pos = { a,b };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void printxy(int a, int b, char c[]) //Ŀ����ġ�� �����ϰ� �Է��Ѵ�.
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
	fscanf(f, "%d\n", &best_point);
	fflush(f);
	fclose(f);
	key = 0;
	system("mode con:cols=50 lines=20");
	system("title Snake Game with L - Title");
	Cursor_out();
	setcolor(15);
	printxy(15, 4, "===������ũ ����===");

	setcolor(11);
	printxy(15, 6, "  ===��弱��===");

	setcolor(12);
	printxy(15, 8, "     �ϵ���\n\t\t      H Key");

	setcolor(10);
	printxy(15, 11, "     �Ϲݸ��\n\t\t      G Key");
	printxy(3, 15, "Tip��");
	srand(time(NULL));
	switch (rand()%10)
	{
	case 0:
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
		break;
	case 1:
		setcolor(15);
		gotoxy(4, 16);
		printf("������� ");
		setcolor(11);
		printf("��Ʈ");
		setcolor(15);
		printf("�� �����ϴ�(?) ");
		setcolor(11);
		printf("��Ÿ����");
		setcolor(15);
		printf("�Դϴ�.");
		break;
	case 2:
		setcolor(15);
		gotoxy(4, 16);
		printf("����!! ���ĸ��Ĵ� ���ڶ��ϴ�!!");
		break;
	case 3:
		setcolor(15);
		gotoxy(4, 16);
		printf("�Ķ��� �׸�� �Ӹ��Դϴ�!!");
		break;
	case 4:
		setcolor(15);
		gotoxy(4, 16);
		printf("P�� ������ �Ͻ� ���� �Ҽ� �ֽ��ϴ�!!\n    ���鶧�� ���� ������!!");
		break;
	case 5:
		setcolor(15);
		gotoxy(4, 16);
		printf("���� ������ ");
		setcolor(11);
		printf("\"���� + (�ð�x��ֹ���)\" ");
		setcolor(15);
		printf("�Դϴ�");
		break;
	default:
		setcolor(15);
		gotoxy(4, 16);
		printf("�ȳ��ϼ��� �����ڿ���");
	}
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
				printf("�ϵ���");
				setcolor(15);
				printf("�� �����մϴ�\n\t����Ϸ��� ESC�� ��������");
				Sleep(100);
				for (j = 3; j > 0; j--)
				{
					if (_kbhit()) key = _getch();
					if (key == ESC) Title();
					gotoxy(11, 6);
					printf("%d�� �� �����մϴ�.", j);
					Sleep(1000);
				}
				speed = 70, dif = 2, nBlock=15;
				break;
			}

			if (key == 103)
			{
				system("mode con:cols=40 lines=10");
				system("title Snake Game with L");
				gotoxy(10, 3);
				setcolor(10);
				printf("�Ϲݸ��");
				setcolor(15);
				printf("�� �����մϴ�\n\t����Ϸ��� ESC�� ��������");
				Sleep(100);
				for (j = 4; j > 0; j--)
				{
					if (_kbhit()) key = _getch();
					if (key == ESC) Title();
					gotoxy(11, 6);
					printf("%d�� �� �����մϴ�.", j);
					Sleep(1000);
				}
				speed = 200, dif = 1, nBlock=5;
				break;
			}
			if (key == ESC) exit(0);
			key = 0;
		}
	}
}

void reset()
{
	while (_kbhit()) key = _getch(), key = 0;
	Title();//Ÿ��Ʋ
	system("mode con:cols=100 lines=33");
	system("title Snake Game with L - Play");//�̸�

	

	

	for (j = 0; j < 20; j++) //��ֹ� �ʱ�ȭ
	{
		printxy(hate_x[j], hate_y[j], "  ");
		hate_x[j] = 0;
		hate_y[j] = 0;
	}

	for (j = 0; j < 500; j++)//body �ʱ�ȭ
	{
		body_x[j] = 0;
		body_y[j] = 0;
		if (body_x[j] == 0 && body_y[j] == 0) break;
	}

	for (x = 0; x <= 49; x++)//�⺻������ ����
	{
		for (y = 0; y <= 29; y++)
		{
			if (y == 0 || y == 29 || x == 0 || x == 49)
			{
				printxy(x * 2, y, "��");
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
	ta = 0;
	t = 0;
	
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
	case P:
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
	printxy(body_x[0] * 2, body_y[0], "��");

	printxy(body_x[length - 1] * 2, body_y[length - 1], "  ");

	move();

	setcolor(11);

	printxy(body_x[0] * 2, body_y[0], "��");

	setcolor(15);
}

void pause()
{
	while (1)
	{
		if (key == P)
		{
			printxy(20, 30, "�Ͻ����� ��!");
			Sleep(400);
			printxy(20, 30, "           ");
			Sleep(400);
		}
		else
		{
			printxy(20, 30, "��� ���̴�!");
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
	gotoxy(20, 30);
	printf("%d", t / 5000);
	
	
	if (ta < t / 5000)
	{
		check_level();
		point += t / 1000 * c;
		ta += 1;
		for (j = 0; j < c; j++)
		{
			if (!(hate_x[j] == 0 && hate_y[j] == 0))
			{
				printxy(hate_x[j] * 2, hate_y[j], "  ");
			}
		}

		for (d = 0; d < c; d++)
		{
			srand((unsigned int)time(NULL));
			_x = rand() % 47 + 1;
			_y = rand() % 28 + 1;
			
			

			for (j = 0; j < d; )//������ ���� �Ȱ�ġ��
			{

				if (hate_x[j] == _x && hate_y[j] == _y)
				{
					_x = rand() % 47 + 1;
					_y = rand() % 28 + 1;
				}
				else
				{
					j++;
				}
				for (o = 0; o < length; )//���� �� ��ġ��
				{

					if (body_x[o] == _x && body_y[o] == _y)
					{
						_x = rand() % 47 + 1;
						_y = rand() % 28 + 1;
					}
					else
					{
						o++;
					}
				}
			}
			

			hate_x[d] = _x;
			hate_y[d] = _y;
		}
		
		gotoxy(0, 31);
		if (fopen("C:\\GamesL\\SnakeGame\\Log.txt", "r+") == NULL)
		{
			f = fopen("C:\\GamesL\\SnakeGame\\Log.txt", "w");
			fclose(f);
		}
		f = fopen("C:\\GamesL\\Snakegame\\Log.txt", "a");
		fprintf(f, "\n\n%d", ta);
		for (j = 0; j <= 10; j++)
		{
			printf("%d ", hate_x[j]);
			printf("%d; ", hate_y[j]);
			fprintf(f, "X : %d Y : %d", hate_x[j], hate_y[j]);
		}
		printf("\n");
		for (; j < 20; j++)
		{
			printf("%d ", hate_x[j]);
			printf("%d; ", hate_y[j]);
			fprintf(f, "X : %d Y : %d\n", hate_x[j], hate_y[j]);
		}
		fprintf(f, "\n");
		fclose(f);
		
	}
	setcolor(12);

	for (j = 0; j < c; j++)
	{
		if (hate_x[j] == 0 && hate_y[j] == 0) break;
		printxy(hate_x[j] * 2, hate_y[j], "��");
	}

	setcolor(15);
}

char check_die()
{
	if (x == 0 || x == 49 || y == 0 || y == 29)
	{
		return 1;
	}
	for (j = 1; j < length; j++)
	{
		if (x == body_x[j] && y == body_y[j]) return 1;
	}
	for (j = 0; j < 20; j++)
	{
		if (x == hate_x[j] && y == hate_y[j]) return 1;
		if (0 == hate_x[j] && 0 == hate_y[j]) break;
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
	printf("����� ���� :");
	char ch[10];
	_itoa(point, ch, 10);
	gotoxy(20 - (length_array(ch) / 2) - (length_array(ch) % 2), 5); setcolor(11); printf("%d", point); setcolor(15);

	Sleep(1000);

	gotoxy(15, 7);
	printf("�ְ� ���� :");
	if (best_point < point) best_point = point;
	_itoa(best_point, ch, 10);

	gotoxy(20 - (length_array(ch) / 2) - (length_array(ch) % 2), 8);
	setcolor(11);
	printf("%d", best_point);
	setcolor(15);

	f = fopen("C:\\GamesL\\SnakeGame\\bestpoint.txt", "r+");
	fprintf_s(f, "%d\n", best_point);
	fflush(f);
	fclose(f);

	Sleep(500);

	gotoxy(8, 15);
	printf("%d�ʵ��� ������ �ϼ̽��ϴ�.", t / 1000);
	Sleep(2000);
}

int main()
{
	while (1)
	{
		reset();

		while (1)
		{

			printxy(0, 0, "��");
			t += speed;
			key = 0;
			gotoxy(6, 30);
			printf("point : %d", point);
			gotoxy(40, 30);
			printf("length : %d", length);
			point += length;
			Sleep(speed);
			if (x == 1 && y == 1) point += length;
			if (x == 1 || y == 1 || y == 28 || x == 48) point += length / 2;
			if (_kbhit())
			{

				key = _getch();
				ago = dir;
				if (key == P)
				{
					pause();
				}
				if (key == 224)
				{
					key = _getch();
				}
				if ((key == LEFT || key == RIGHT || key == UP || key == DOWN || key == P) &&
					((dir == LEFT && key != RIGHT) || (dir == RIGHT && key != LEFT) ||
					(dir == UP && key != DOWN) || (dir == DOWN && key != UP)))
				{
					dir = key;
				}

				key = 0;
			}

			draw_body();
			
			block_hate(nBlock);

			if ((point % 10) == 0) length++;
			if (check_die() == 1)
			{
				Sleep(2000);
				while (_kbhit()) key = _getch();
				game_over();
				break;
			}
		}
	}
}