#pragma once
#include"block.h"
#include<fstream>
#include<Windows.h>
using namespace std;
#define WIDTH  938
#define HEIGHT 896
#define MAX_LEVEL 5

class tetris{
public:
	tetris(int leftMargin, int topMargin);
	void init();     
	void play();   
	void end(int iswin);
	void welcome();

private:
	void keyEvent();  //��������
	int getClockcount();  //��ȡ�����ϴε�ʱ��
	void updateWindow();    //��Ⱦ��Ϸ����          
	void drop();        //��������
	void clearLine();   //��������
	void leftrightMove(int dx);    //�����ƶ�
	void rotate();       //������ת
	void drawScores();   //���Ʒ���
	void drawLines();     //������������
	void drawLevels();    // ���ƹؿ�
	void drawStyple(int x,int y,int contects,int d);    //���Ƹ�ʽ����
	void drawHeighScores();    //������߷�
	void drawClear(int y);         //����������Ч

private:
	int score;           //��ǰ�ķ���
	int rows;			 //������
	int cols;			//������
	int leftMargin;    //�ұ߽�
	int topMargin;    //��߽�
	int delay;      //�ӳ�ʱ��
	bool update;   //�Ƿ���Ⱦ��Ϸ����
	IMAGE imgBg;     //��Ϸ����ͼƬ
	point offset;    //ƫ����
	int size;         //�����С
	int level;     //��ǰ�ؿ�
	int direction;  //���ҷ���
	int upspeed;   //���µ��ٶ�
	int lineCount;   //��������
	int heighScore;  //��ʷ��߷�
	int iswin;       //��������
	bool drawLine[20];  //������Ч����
	IMAGE Line[13];       //������ЧͼƬ 
    
private:
	vector<vector<int>>map_s;   //��ͼ
	block* curBlock;           //��ǰ����
	block* nextBlock;          //Ԥ�淽��
	block bakBlock;            //���ݷ���
	static int addScores[4];   //�÷ּ���
};

