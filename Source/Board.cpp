#include<vector>
#include<iostream>
#include<cstdlib>
#include"Board.h"
#include<GL\glut.h>

using namespace std;

Board::Board(int width, int height)		///-1:���	1:�D��m	2:ī�G
{
	ishack = 0;
	col = width; row = height;
	state = -1;///��l�D���A
	apple = 0; ///ī�G�ƶq
	score = 0;
	cnttime = 100;
	islose = 0;
	UpdateTime = 100;///�e����s�ɶ�
	maps = new int*[height];
	for (int i = 0; i < height; i++)
	{
		maps[i] = new int[width];
	}
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			maps[i][j] = 0;
	/*�إ����*/
	for (int i = 0; i < width; i++)
	{
		maps[0][i]= -1;
		maps[height - 1][i] = -1;
	}
	for (int i = 0; i < height; i++)
	{
		maps[i][0] = -1;
		maps[i][width-1] = -1;
	}
	/*________________*/
	
	/*��l�H�����ͳD�Y����m*/
	snake.Grow(rand() % (width - 1) + 1, rand() % (height - 1) + 1);
	Point h = snake.GetHead();
	snake.Grow(h.x,h.y);
}

bool Board::IsLose()
{
	Point h = snake.GetHead();
	if (maps[h.y][h.x] == -1)	return true;
	if (!ishack&&maps[h.y][h.x] == 1) return true;
	else if (ishack&&maps[h.y][h.x] == 1) return false;
	return false;
} 

void Board::KeyEvent(unsigned char key)
{
	if (key == 'w' || key == 'W')
		state = 0;
	else if (key == 'd' || key == 'D')
		state = 1;
	else if (key == 's' || key == 'S')
		state = 2;
	else if (key == 'a' || key == 'A')
		state = 3;
}

void Board::addApple()
{
	if (!apple)
	{
		vector<Point> arr;
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				if (maps[i][j] == 0)	arr.push_back(Point(j, i));
		srand(time(NULL));
		int rr = (rand()+rand())%arr.size();
		int rx = arr[rr].x, ry = arr[rr].y;
		maps[ry][rx] = 2;
		apple++;
	}
}

void Board::Update()
{
	if (cnttime < 0)cnttime = 0;
	if (!islose&&cnttime > 0)
	{
		/*�p�G�D������l���A-1�N���ʧ@*/
		if (state != -1)
		{
			snake.Move(state);
			/*�p��ɶ�*/
			if (endss - starts > 1000)
			{
				starts = clock();
				cnttime--;
			}
			endss = clock();
			//cout << starts << " " << endss << endl;


			/*�ˬd�D�O�_�����ê���O�_�n�����C��*/
			cout << state << endl;
			if (ishack)
				while (IsLose())
				{
					snake.Move((state + 2) % 4);
					state = (state + 1) % 4;
					snake.Move(state);
				}
			else
			{
				Point h = snake.GetHead();
				if (maps[h.y][h.x] == 1) cnttime -= 10;
				else
				{
					bool check = 0;	///�ˬd�O�_�������ê��
					while (IsLose())
					{
						check = 1;
						snake.Move((state + 2) % 4);
						state = (state + 1) % 4;
						snake.Move(state);
					}
					if(check)
						cnttime -= 10;
				}

			}

			/*�ɥRī�G*/
			addApple();

			Point h = snake.GetHead();

			/*�p�G�D�Y��ī�G*/
			vector<Point> arr = snake.GetBody();
			if (maps[h.y][h.x] == 2)
			{
				cnttime += 5;
				score++;
				snake.Grow(h.x, h.y);
				apple--;
			}
			snake.Update(); ///��s�����m

							/*��ɺ��@*/
			for (int i = 0; i < col; i++)
			{
				maps[0][i] = -1;
				maps[row - 1][i] = -1;
			}
			for (int i = 0; i < row; i++)
			{
				maps[i][0] = -1;
				maps[i][col - 1] = -1;
			}

			for (int i = 0; i < row; i++)
				for (int j = 0; j < col; j++)
				{
					if (maps[i][j] == 1)
						maps[i][j] = 0;
				}
			for (int i = 0; i < int(arr.size()); i++)
			{
				int x = arr[i].x, y = arr[i].y;
				maps[y][x] = 1;
			}
		}
		else starts = clock();
	}
	else
	{
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
			{
					maps[i][j] = 0;
			}
		islose = 1;
	}
}



 int** Board::getMap()
 {
	 return maps;
 }

 Board::~Board()
 {
	 for (int i = 0; i < row; i++)
		 delete maps[i];
	 delete maps;
 }