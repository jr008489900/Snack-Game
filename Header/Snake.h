#pragma once
#ifndef _Snake_H_
#define _Snake_H_
#include<vector>
#endif /*_Snake_H_*/

using namespace std;

struct Point
{
	Point();
	Point(int X, int Y) : x(X), y(Y) {}
	int x, y;
};

class Snake	/// store Snake's body
{
public:
	Snake();
	vector<Point> GetBody();
	Point GetHead();
	void Move(int dirction);	///move up:0 right:1 down:2 left:3
	void Grow(int x, int y);
	void Update();	///��s�����m
private:
	int state;	/// �ΨӧP�w�D�O�_�n����
	vector<Point> arr;	///store snake's body;
};