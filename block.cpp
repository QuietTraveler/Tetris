#include "block.h"
#include"tetris.h"
#include<iostream>
using namespace std;

int block::blockSize = 36;
IMAGE* block::imgs[7] = { NULL, };

const int allBlocks[7][4]{
	1,3,5,7,  // Ⅰ型
	2,4,5,7,  // Z1型
	3,5,4,6,  // Z2型
	3,5,4,7,  // T型
	2,3,5,7,  // L型
	3,5,7,6,  // J型
	2,3,4,5,  // 田型
};


block::block()
{
	this->left = leftMargin;
	this->top = topMargin;
	this->rows = ROWS;
	this->cols = COLS;

	
	if(!imgs[0])
	{
		this->SetTile();
	}

	this->blockType = rand() % 7;
	this->offset_x = rand() % 8;

	for (int i = 0; i < 4; i++)
	{
		smallBlocks[i].x = allBlocks[this->blockType][i] % 2 + offset_x;
		smallBlocks[i].y = allBlocks[this->blockType][i] / 2;
		
	}


	this->imgBk = this->imgs[blockType];
}

void block::drop()
{

	for (int i = 0; i < 4; i++)
	{
		this->smallBlocks[i].y++;
	}
}

void block::rotate()
{
	point p = smallBlocks[1];
	for (int i = 0; i < 4; i++)
	{
		point tmp = smallBlocks[i];
		smallBlocks[i].x = p.x - tmp.y + p.y;
		smallBlocks[i].y = p.y + tmp.x - p.x;
	}
}

void block::leftRightMove(int dx)
{

	for (int i = 0; i < 4; i++)
	{
		this->smallBlocks[i].x += dx;
	}
}

void block::SetTile()
{
	IMAGE imgTmp;
	loadimage(&imgTmp, "D:\\Gitee_bank\\Game\\Tetris\\res\\tiles.png");

	SetWorkingImage(&imgTmp);
	 
	int size = this->blockSize;

	for (int i = 0; i < 7; i++)
	{
		this->imgs[i] = new IMAGE;
		getimage(this->imgs[i], i * size, 0, size, size);
	}

	SetWorkingImage();
}

void block::draw(point offset)
{
	    point p = { 0,0 };
		int size = this->blockSize;
		int x = this->smallBlocks[0].x * size + this->left;
		int y = this->smallBlocks[0].y * size + this->top;
		if(offset.x)
		{
			p = { offset.x - x,offset.y - y };
		}
	for (int i = 0; i < 4; i++)
	{
		 x = this->smallBlocks[i].x * size + this->left;
		 y = this->smallBlocks[i].y * size + this->top;
		putimage(x+p.x, y+p.y, this->imgBk);
	}
}

IMAGE** block::getBlockType()
{
	return imgs;
}

point* block::getSmallBlock()
{
	return this->smallBlocks;
}

block& block::operator=(const block& other)
{
	if (this == &other)
	{
		return *this;
	}
	this->blockSize = other.blockSize;
	this->blockType = other.blockType;
	this->imgBk = other.imgBk;

	for (int i = 0; i < 4; i++)
	{
		this->smallBlocks[i] = other.smallBlocks[i];
	}
	return *this;
}

bool block::blockInMap(const vector<vector<int>>& map_s)
{
	for (int i = 0; i < 4; i++)
	{

		if (smallBlocks[i].x < 0 || smallBlocks[i].x >= this->cols ||
			smallBlocks[i].y < 0 || smallBlocks[i].y >= this->rows ||
			map_s[smallBlocks[i].y][smallBlocks[i].x])
			return false;
	}
	return true;
}

void block::solidfy(vector<vector<int>>& map_s)
{

	for (int i = 0; i < 4; i++)
	{
		map_s[smallBlocks[i].y][smallBlocks[i].x] = this->blockType+1;
	}
}

int block::getType()
{
	return this->blockType;
}
 