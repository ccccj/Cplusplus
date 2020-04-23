#pragma once

#define ROW 3
#define COL 3

enum CHOICE {
	EXIT,
	PLAY
};

enum SCORE{
	DRAW,
	PLAYERW,
	COMW,
	UNFULL
};

void InitBoard(char arr[][COL]);

void DispBoard(char arr[][COL]);

void PlayerSet(char arr[][COL]);

void ComputerSet(char arr[][COL], int _time, int flag);

int IsWin(char arr[][COL]);

