#include "tetris.h"
#include<cstdlib>
#include<iostream>
#include<Windows.h>
#include<time.h>
#include<conio.h>

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) 

#include<mmsystem.h>

#pragma comment(lib,"winmm.lib")

using namespace std;

const int SPEED[MAX_LEVEL] = { 500,350,250,150,50};

int tetris::addScores[4]= { 10,30,60,80 };

tetris::tetris(int leftMargin, int topMargin)
{
	this->leftMargin = leftMargin;
	this->topMargin = topMargin;
	this->rows = ROWS;
	this->cols = COLS;
	this->size = 36;
	this->level = 1;
	this->delay = SPEED[this->level-1];
	this->update = true;
	this->curBlock = NULL;
	this->nextBlock = NULL;
	this->direction = 1;
	this->offset = {720,280};
	this->upspeed = 70;
	this->score = 0;
	this->lineCount = 0;
	this->heighScore = 0;
	this->iswin = 0;

	for (int i = 0; i < this->rows; i++)
	{
		vector<int>mapRow;
		for (int j = 0; j < this->cols; j++)
		{
			mapRow.push_back(0);
		}
			map_s.push_back(mapRow);
	}

	initgraph(WIDTH, HEIGHT);

}

void tetris::init()
{
	mciSendString("stop D:\\Gitee_bank\\Game\\Tetris\\res\\welcome\\bg.mp3", 0, 0, 0);
	
	loadimage(&(this->imgBg), "D:\\Gitee_bank\\Game\\Tetris\\res\\bg2.png");

	mciSendString("play D:\\Gitee_bank\\Game\\Tetris\\res\\bg.mp3 repeat", 0, 0, 0);
	
	char p[80];
	for (int i = 0; i < 12; i++)
	{
		sprintf_s(p, sizeof(p), "D:\\Gitee_bank\\Game\\Tetris\\res\\tx\\%d.png", i);
		IMAGE img;
		loadimage(&img, p,360,36);
		this->Line[i] = img;
	}
	memset(drawLine, sizeof(bool)*20, 0);

	srand((unsigned int)time(NULL));
	
	this->update = true;
	this->level = 1;
	this->delay = SPEED[this->level-1];
	this->offset = {720, 280};
	this->direction = 1;
	this->score = 0;
	this->upspeed = 70;
	this->lineCount = 0;
	this->iswin = 0;

	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			map_s[i][j] = 0;
		}
	}

	fstream heighfile;
	heighfile.open("heighScores.txt", ios::in);
	if (heighfile.fail())
	{
		cout << "文件打开失败" << endl;
	}
	else
	heighfile >> this->heighScore;

	heighfile.close();

}

void tetris::play()
{
	this->init();

	this->nextBlock = new block;
	this->curBlock = nextBlock;
	this->nextBlock= new block;

	long int timer = 0;

	while (1)
	{

		this->keyEvent();

		timer += this->getClockcount();  //累计时间
		if (timer > this->delay)
		{
			this->drop();
			update = true;
			timer = 0;
		}

		if (update)
		{
			update = false;

			//更新游戏画面
			this->updateWindow();

			//更改游戏数据
			this->clearLine();

			
		} 
	}
}

void tetris::end(int iswin)
{
	if (this->score >= this->heighScore)
	{
		fstream heighfile;
		heighfile.open("heighScores.txt", ios::out);
		heighfile<<this->score;
		heighfile.close();
	}

	IMAGE endImg;
	mciSendString("stop D:\\Gitee_bank\\Game\\Tetris\\res\\bg.mp3", 0, 0, 0);

   if(iswin==-1)
   {
	   loadimage(&endImg, "D:\\Gitee_bank\\Game\\Tetris\\res\\over.png");
	   mciSendString("play D:\\Gitee_bank\\Game\\Tetris\\res\\over.mp3", 0, 0, 0);
   }
   else
   {
	   loadimage(&endImg, "D:\\Gitee_bank\\Game\\Tetris\\res\\win.png");
	   mciSendString("play D:\\Gitee_bank\\Game\\Tetris\\res\\win.mp3", 0, 0, 0);
   }

   putimage(265, 335, &endImg);

   while(1)
   {
	   if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	   {

		   closegraph();
		   exit(0);
	   }
	   else if(GetAsyncKeyState('R') & 0x8000)
	   {
		   this->init();
		   break;
	   }
   }
   
}

void tetris::welcome()
{
	IMAGE run[80];
	char p[100];
	int j = 78;

	IMAGE wImg;
	int k = 0;
	for (int i = 15; i < 93; i++)
	{
		sprintf_s(p, sizeof(p),"D:\\Gitee_bank\\Game\\Tetris\\res\\welcome\\_00%d_图层-%d.png", i, j);
		loadimage(&wImg, p,WIDTH,HEIGHT);
		run[k++] = wImg;
		j--;
	}
	mciSendString("play D:\\Gitee_bank\\Game\\Tetris\\res\\welcome\\bg.mp3 repeat",0,0,0);

   while(1)
   {
	   for (auto i = 0; i < k; i++)
	   {
		   IMAGE runImg;
		   runImg = run[i];
		   putimage(0, 0, &runImg);
			Sleep(100);
	   }


	   if (GetAsyncKeyState('S') & 0x8000)
	   {
		   break;
	   }
	   
   }
}

void tetris::drawLevels()
{
	this->drawStyple(200,730,this->level,0);
}

void tetris::keyEvent()
{ 
		bool rotateFlag = false;
		int dx = 0;
		/*unsigned char ch;
		if (_kbhit())
		{
			ch = _getch();
			if (ch == 224)
			{
				ch = _getch();
				switch (ch)
				{
				case 72:
					rotateFlag = true;
					break;
				case 80:
					this->delay = upspeed;
					break;
				case 75:
					dx = -(this->direction);
					break;
				case 77:
					dx = (this->direction);
					break;
				}
			}
		}*/
		ExMessage msg;
		while (peekmessage(&msg, EX_KEY) && msg.message == WM_KEYDOWN)
		{
			switch (msg.vkcode)
			{
				// 上键旋转
			case 'W':
			case VK_UP:
				rotateFlag = true;
				break;

				// 下键加速下落
			case 'S':
			case VK_DOWN:
				this->delay = upspeed;
				break;

				// 左键移动
			case 'A':
			case VK_LEFT:
				dx = -(this->direction);
				break;

				// 右键移动
			case 'D':
			case VK_RIGHT:
				dx = (this->direction);
				break;
			}
		}



	if (rotateFlag)
	{
		this->rotate();
		this->update = true;
	}

	if (dx)
	{
		this->leftrightMove(dx);
		this->update = true;
	}

}

int tetris::getClockcount()  //获取距离上一次的时间
{
	clock_t prev = 0;
	static clock_t cur=0;

	if (!cur)
	{
		cur = clock();
		return 0;
	}
	else
	{
		prev = cur;
		cur = clock();
		return cur - prev;
	}
}

void tetris::updateWindow()
{
	
	IMAGE** imgs = block::getBlockType();

	BeginBatchDraw();

	putimage(0, 0, &(this->imgBg));

	this->nextBlock->draw(this->offset);
	this->curBlock->draw({ 0,0 });

	this->drawScores();
	this->drawLevels();
	this->drawLines();
	this->drawHeighScores();

	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			if (!map_s[i][j])
				continue;
			int x = j * size + leftMargin;
			int y = i * size + topMargin;
			putimage(x, y, imgs[map_s[i][j]-1]);
		}
	}

	EndBatchDraw();
}


void tetris::drop()
{
	bakBlock = *curBlock;
	this->curBlock->drop();

	if (!curBlock->blockInMap(this->map_s))
	{
		//方块固化
		bakBlock.solidfy(this->map_s);

		delete curBlock;
		curBlock=nextBlock;
		nextBlock=new block;
    

		for (int i = 0; i < 4; i++)
		{
			int d_x = curBlock->getSmallBlock()[i].x;
			int d_y = curBlock->getSmallBlock()[i].y;
			if (map_s[d_y][d_x])
			{
				this->iswin = -1;
				this->end(this->iswin);
			}
		}
	}


	this->delay = SPEED[this->level - 1];
}


void tetris::clearLine()
{
	int line = 0;
	int k = this->rows - 1;
	for (int i = this->rows - 1; i >= 0; i--)
	{
		int count = 0;
		for (int j = this->cols - 1; j >= 0; j--)
		{
			if (this->map_s[i][j])
				count++;
			map_s[k][j] = map_s[i][j];
		}
		if (count < this->cols)
		{
			if(k>0)
			k--;   
		}
		else
		{
			drawLine[k] = 1;
			line++;
		}
	}

	if (line)
	{
		this->lineCount += line;

		if (line < 5)
			this->score += this->addScores[line - 1];
		else
			this->score += 100;

		if (this->score >= 500)
		{
			this->iswin = 1;
			this->end(this->iswin);
		}
		
		this->update = true;


		mciSendString("play D:\\Gitee_bank\\Game\\Tetris\\res\\xiaochu1.mp3", 0, 0, 0);
		

		if (this->score >= this->heighScore)
		{
		   this->heighScore = this->score;
		}

		if (this->score / 100 + 1 != this->level)
		{
			this->level = this->score / 100 + 1;
		}

		this->updateWindow();
	}

}

void tetris::leftrightMove(int dx)
{
	bakBlock = *curBlock;
	this->curBlock->leftRightMove(dx);

	if (!this->curBlock->blockInMap(this->map_s))
	{
		*curBlock = bakBlock;
	}

}

void tetris::rotate()
{
	if (this->curBlock->getType() == 6)
		return;
	this->bakBlock = *this->curBlock;
	this->curBlock->rotate();

	if (!this->curBlock->blockInMap(this->map_s))
	{
		*curBlock = bakBlock;
	}
}

void tetris::drawScores()
{
	this->drawStyple(670, 727, this->score,0);
}

void tetris::drawLines()
{
	this->drawStyple(200, 815, this->lineCount, 1);
}

void tetris::drawHeighScores()
{
	this->drawStyple(670,815,this->heighScore,0);
}

void tetris::drawClear(int y)
{
	y = (y + 1)*this->size;
	for (int i = 0; i < 12; i++)
	{
		putimage(this->leftMargin, this->topMargin + y, &(this->Line[i]));
	}
}

void tetris::drawStyple(int x,int y,int contects,int d=0)
{
	char scoreText[32];
	sprintf_s(scoreText, sizeof(scoreText), "%d", contects);

	settextcolor(RGB(179, 179, 179));

	LOGFONT f;
	gettextstyle(&f);

	f.lfHeight = 60;
	f.lfWidth = 30;
	f.lfQuality = ANTIALIASED_QUALITY;  //设置字体为“抗锯齿”效果
	strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("Segoe UI Black"));
	settextstyle(&f);

	setbkmode(TRANSPARENT);   //设置字体背景为透明效果

	if (d)
	{
		int counts = 0, lines = this->lineCount;
		while (lines)
		{
			lines /= 10;
			if (lines)
				counts++;
		}
		x = x - (counts * f.lfWidth);
	}

	outtextxy(x, y, scoreText);
}



