#include<ctime>
#include<iostream>
#include<sstream>
#include<string>
#include<thread>
#include"Board.h"
#include"Text.h"
#include<GL\glut.h>

using namespace std;

time_t starts, endss;	///時間
int width = 1024, height = 768;
Board myBoard(100, 50);
Text mytext;

void mymenu(int value)
{
	if (value == 1)
		myBoard.UpdateTime = 100;
	else if (value == 2)
		myBoard.UpdateTime = 75;
	else if (value == 3)
		myBoard.UpdateTime = 50;
	else if (value == 4)
		myBoard.UpdateTime = 25;
	else if (value == 5)
		myBoard.ishack = !myBoard.ishack;
	else
	{
		exit(0);
	}
}

void init()
{
	glClearColor(0, 0, 0, 0);
	glColor3d(1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, 0, 100);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

	int menu=glutCreateMenu(mymenu);
		glutAddMenuEntry("Slow", 1);
		glutAddMenuEntry("Medium", 2);
		glutAddMenuEntry("Fast", 3);
		glutAddMenuEntry("Crazy", 4);
		glutAddMenuEntry("Hack", 5);
		glutAddMenuEntry("Exit", 6);	
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/*印出時要注意螢幕座標與投影座標的Y座標轉換*/
void mydisplay1()
{
	int** maps = myBoard.getMap();
	string str1;
	stringstream ss;
	string temp1;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if (myBoard.islose)
	{
		glColor3d(1, 1, 1);
		str1 = "GAME OVER";
		for (int i = 0; i < str1.size(); i++)
		{
			glPushMatrix();
			glTranslated(300+60*i, 300, 0);
			glScaled(5, 5, 5);
			mytext.PrintChar(str1[i]);
			glLoadIdentity();
			glPopMatrix();
		}
	}
	else
	{
		/*印出地圖*/
		for (int i = 0; i < myBoard.row; i++)
			for (int j = 0; j < myBoard.col; j++)
			{
				glPushMatrix();
				if (maps[i][j] == -1)
					glColor3d(1, 0, 0);
				else if (maps[i][j] == 1)
					glColor3d(1, 0.5, 0.25);
				else if (maps[i][j] == 2)
					glColor3d(0, 0, 1);
				else
					glColor3d(0, 0, 0);
				glPointSize(10);
				glBegin(GL_POINTS);
				glVertex3d(j * 9 + 50, myBoard.row * 8 - i * 9 + 150, 0);
				glEnd();
				glPopMatrix();
			}
	}
	/*印出時間*/

	/*glPushMatrix();
	glColor3d(1, 1, 0);
	glRasterPos2d(200, 600);
	int t = myBoard.cnttime;
	ss << t;
	ss >> temp1;
	for (int i = 0; i < str1.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str1[i]);
	for (int i = 0; i < temp1.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, temp1[i]);
	glPopMatrix();*/


	/*印出時間*/
	glPushMatrix();
		glColor3d(1, 1, 0);
		str1 = "TIME";
		for (int i = 0; i < str1.size(); i++)
		{
			glPushMatrix();
			glTranslated(300 + 25 * i, 600, 0);
			glScaled(2, 2, 2);
			mytext.PrintChar(str1[i]);
			glLoadIdentity();
			glPopMatrix();
		}
	glPopMatrix();
	/*印出時間數值*/
	glPushMatrix();
		glColor3d(1, 1, 1);
		vector<int> numarr;
		int temp = myBoard.cnttime;
		do
		{
			numarr.push_back(temp % 10);
			temp /= 10;
		} while (temp != 0);
		{

		}
		for (int i=numarr.size()-1,j=0;i>=0;i--,j++)
		{
			glPushMatrix();

			glTranslated(400+20*j, 600, 0);
			glScaled(2, 2, 2);
			

			mytext.PrintNum(numarr[i]);
			glLoadIdentity();
			glPopMatrix();
		}
	glPopMatrix();

	/*印出SCORE*/
	glPushMatrix();
	glColor3d(1, 1, 0);
	str1 = "SCORE";
	for (int i = 0; i < str1.size(); i++)
	{
		glPushMatrix();
		glTranslated(600 + 25 * i, 600, 0);
		glScaled(2, 2, 2);
		mytext.PrintChar(str1[i]);
		glLoadIdentity();
		glPopMatrix();
	}
	glPopMatrix();

	/*印出分數*/
	glPushMatrix();
	glColor3d(1, 1, 1);
	numarr.clear();
	temp = myBoard.score;
	do
	{
		numarr.push_back(temp % 10);
		temp /= 10;
	} while (temp != 0);
	for (int i = numarr.size() - 1, j = 0; i >= 0; i--, j++)
	{
		glPushMatrix();

		glTranslated(750 + 20 * j, 600, 0);
		glScaled(2, 2, 2);


		mytext.PrintNum(numarr[i]);
		glLoadIdentity();
		glPopMatrix();
	}
	glPopMatrix();

	glutSwapBuffers();
	glFlush();
}


void mytimer(int value)
{
	myBoard.Update();
	glutPostRedisplay();
	glutTimerFunc(myBoard.UpdateTime, mytimer, 1);
}

void keyFuc(unsigned char key,int x,int y)
{
	myBoard.KeyEvent(key);
}


int main(int argc,char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	int w1=glutCreateWindow("Game");	///遊戲畫圖視窗
	glutSetWindow(w1);
	init();
	glutDisplayFunc(mydisplay1);
	glutKeyboardFunc(keyFuc);
	glutTimerFunc(myBoard.UpdateTime, mytimer, 1);

	glutMainLoop();
}

