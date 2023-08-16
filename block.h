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
	void drop();   //����
	void rotate();  //��ת
	void leftRightMove(int offset);  //�����ƶ�
	void SetTile();                   //���ɷ����������ɫ����
	void draw(point offset);          //���Ƴ�����
	static IMAGE** getBlockType();    //���ش洢���з������͵ļ���
	point* getSmallBlock();    //����С��������
	
	block& operator =(const block& other);   //�Ⱥ�����

	bool blockInMap(const vector<vector<int>>&map_s);     //�жϷ����Ƿ��ڵ�ͼ��
	void solidfy(vector<vector<int>>& map_s);    //����̻�
	int getType();                             //��ȡ��������

private:
	int left;
	int top;
	point smallBlocks[4];    //����˹��������
	int blockType;			 //������ɫ����
	IMAGE* imgBk;			 //��Ϸ����ͼƬ
	int offset_x;			 //x��ƫ����
	int cols;            
	int rows; 



private:
	static IMAGE* imgs[7];    //���з����������ɫ���� 
	static int blockSize;    //�����С
};

