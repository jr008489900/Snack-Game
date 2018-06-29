#include"Snake.h"
#include<vector>
using namespace std;

Snake::Snake()
{
	state = 0;
}

vector<Point> Snake::GetBody()
{
	return arr;
}

void Snake::Move(int dir)
{
	switch (dir)
	{
	case 0:	///up
		arr[0].y -= 1;
		break;
	case 1:	///right
		arr[0].x += 1;
		break;
	case 2:	///down
		arr[0].y += 1;
		break;
	case 3:	///left
		arr[0].x -= 1;
		break;
	default:
		break;
	}
}

void Snake::Update()
{
	if (state)	///如果蛇有成長
	{
		for (int i = arr.size() - 2; i > 0; i--)
		{
			arr[i] = arr[i - 1];
		}
		state = 0;
	}
	else
	{
		for (int i = arr.size() - 1; i > 0; i--)
		{
			arr[i] = arr[i - 1];
		}
	}
}

Point Snake::GetHead()
{
	if (!arr.empty())	return arr[0];
	else return Point(0, 0);
}

void Snake::Grow(int x, int y)
{
	arr.push_back(Point(x, y));
	state = 1;
}
