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
	int ishack;	///�O�_�L��
	int UpdateTime;		///�e����s�ɶ�
	int score;
	int cnttime;	///�p��ɶ�
		bool islose;
private:
	
	void addApple();	/*�ɥRī�G*/
	int apple;		
	int state;	///���ӱ���D���e�i��V
    int** maps;	///�D�n�a��

	Snake snake;	///�D
	time_t starts, endss;	///�p��
	
};
