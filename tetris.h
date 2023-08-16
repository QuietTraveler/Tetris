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
	void keyEvent();  //按键输入
	int getClockcount();  //获取距离上次的时间
	void updateWindow();    //渲染游戏画面          
	void drop();        //方块下落
	void clearLine();   //更新数据
	void leftrightMove(int dx);    //方块移动
	void rotate();       //方块旋转
	void drawScores();   //绘制分数
	void drawLines();     //绘制消的行数
	void drawLevels();    // 绘制关卡
	void drawStyple(int x,int y,int contects,int d);    //绘制格式函数
	void drawHeighScores();    //绘制最高分
	void drawClear(int y);         //绘制清行特效

private:
	int score;           //当前的分数
	int rows;			 //总行数
	int cols;			//总列数
	int leftMargin;    //右边界
	int topMargin;    //左边界
	int delay;      //延迟时间
	bool update;   //是否渲染游戏画面
	IMAGE imgBg;     //游戏背景图片
	point offset;    //偏移量
	int size;         //方块大小
	int level;     //当前关卡
	int direction;  //左右方向
	int upspeed;   //向下的速度
	int lineCount;   //消的行数
	int heighScore;  //历史最高分
	int iswin;       //结束参数
	bool drawLine[20];  //清行特效数组
	IMAGE Line[13];       //清行特效图片 
    
private:
	vector<vector<int>>map_s;   //地图
	block* curBlock;           //当前方块
	block* nextBlock;          //预告方块
	block bakBlock;            //备份方块
	static int addScores[4];   //得分集合
};

