//
//  project.h
//  扫雷
//
//  Created by admin on 17/12/5.
//  Copyright © 2017年 Amon. All rights reserved.
//

#ifndef project_h
#define project_h

#define ROW 10
#define COL 10

#define ROWS ROW+2
#define COLS COL+2

#define MINES 10

void InitMine(char MINE[][COLS]);
void InitSHOW(char SHOW[][COLS]);
void DisPlay(char arr[][COLS]);
void RemoveMINE1(char MINE[][COLS], char SHOW[][COLS], int x, int y);
int RemoveMINE2(char MINE[][COLS], char SHOW[][COLS], int x, int y);
int RemoveMINE3(char MINE[][COLS],char SHOW[][COLS], int x, int y);

#endif /* project_h */
