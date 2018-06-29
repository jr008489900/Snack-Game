#pragma once
#ifndef _Board_H_
#define _Board_H_
#include<ctime>
#include<vector>
#include<GL\glut.h>
#include"Snake.h"
#endif /*_Board_H_*/
using namespace std;
class Board
{
public:
	Board(int width, int height);
	bool IsLose();
	void KeyEvent(unsigned char);
	void Update();
	~Board();
	int** getMap();
	int row , col;
	int ishack;	///是否無敵
	int UpdateTime;		///畫面更新時間
	int score;
	int cnttime;	///計算時間
		bool islose;
private:
	
	void addApple();	/*補充蘋果*/
	int apple;		
	int state;	///拿來控制蛇的前進方向
    int** maps;	///主要地圖

	Snake snake;	///蛇
	time_t starts, endss;	///計時
	
};
