#include<vector>
#include<iostream>
#include<cstdlib>
#include"Board.h"
#include<GL\glut.h>

using namespace std;

Board::Board(int width, int height)		///-1:邊界	1:蛇位置	2:蘋果
{
	ishack = 0;
	col = width; row = height;
	state = -1;///初始蛇狀態
	apple = 0; ///蘋果數量
	score = 0;
	cnttime = 100;
	islose = 0;
	UpdateTime = 100;///畫面更新時間
	maps = new int*[height];
	for (int i = 0; i < height; i++)
	{
		maps[i] = new int[width];
	}
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			maps[i][j] = 0;
	/*建立邊界*/
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
	
	/*初始隨機重生蛇頭的位置*/
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
		/*如果蛇仍為初始狀態-1就不動作*/
		if (state != -1)
		{
			snake.Move(state);
			/*計算時間*/
			if (endss - starts > 1000)
			{
				starts = clock();
				cnttime--;
			}
			endss = clock();
			//cout << starts << " " << endss << endl;


			/*檢查蛇是否撞到障礙物是否要結束遊戲*/
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
					bool check = 0;	///檢查是否有撞到障礙物
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

			/*補充蘋果*/
			addApple();

			Point h = snake.GetHead();

			/*如果蛇吃到蘋果*/
			vector<Point> arr = snake.GetBody();
			if (maps[h.y][h.x] == 2)
			{
				cnttime += 5;
				score++;
				snake.Grow(h.x, h.y);
				apple--;
			}
			snake.Update(); ///更新身體位置

							/*邊界維護*/
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