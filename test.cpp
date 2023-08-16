#define _CRT_SECURE_NO_WARNINGS  1
#include"tetris.h"

int main()
{
	tetris game(leftMargin,topMargin);
	game.welcome();
	game.play();
	return 0;
}