#pragma once
#include<easyx.h>
#include<vector>

#define ROWS 20
#define COLS 10
const int leftMargin = 263;
const int topMargin = 134;
using namespace std;

typedef struct point {
	int x;
	int y;
}point;

class block{
public:

	block();
	void drop();   //下落
	void rotate();  //旋转
	void leftRightMove(int offset);  //左右移动
	void SetTile();                   //生成方块的类型颜色集合
	void draw(point offset);          //绘制出方块
	static IMAGE** getBlockType();    //返回存储所有方块类型的集合
	point* getSmallBlock();    //返回小方块坐标
	
	block& operator =(const block& other);   //等号重载

	bool blockInMap(const vector<vector<int>>&map_s);     //判断方块是否在地图内
	void solidfy(vector<vector<int>>& map_s);    //方块固化
	int getType();                             //获取方块类型

private:
	int left;
	int top;
	point smallBlocks[4];    //俄罗斯方块坐标
	int blockType;			 //方块颜色类型
	IMAGE* imgBk;			 //游戏方块图片
	int offset_x;			 //x轴偏移量
	int cols;            
	int rows; 



private:
	static IMAGE* imgs[7];    //所有方块的类型颜色集合 
	static int blockSize;    //方块大小
};

