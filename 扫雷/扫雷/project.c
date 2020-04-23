//
//  project.c
//  扫雷
//
//  Created by admin on 17/12/5.
//  Copyright © 2017年 Amon. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "project.h"

void InitMine(char MINE[][COLS])
{
    int x,y;
    int i,j;
    int count = MINES;
    
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            MINE[i][j] = '0';
        }
    }
    
    while (count) {
        
        x = rand()%ROWS;
        y = rand()%COLS;
        
        if ( x >= 1 && x < ROWS-1 && y >= 1 && y < COLS-1 && MINE[x][y] == '0') {
            
            MINE[x][y] = '1';
            count--;
        }
    }
}


void InitSHOW(char SHOW[][COLS])
{
    int i,j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            SHOW[i][j] = '*';
        }
    }
 
}



void DisPlay(char arr[][COLS])
{
    int i,j;
    printf("  ");
    for (i = 1; i <= ROW; i++) {
        printf("%-2d",i);
    }
    
    printf("\n");
    for (i = 1; i <= ROW; i++) {
        printf("%-2d",i);
        
        for (j = 1; j <= COL; j++) {
            
            printf("%c ",arr[i][j]);
            
        }
        printf("\n");
    }
    
}


char ADD(char MINE[][COLS], int x, int y)
{
    
    char c = MINE[x-1][y] + MINE[x-1][y+1] + MINE[x-1][y-1] + MINE[x+1][y] + MINE[x+1][y+1] + MINE[x+1][y-1] + MINE[x][y+1] + MINE[x][y-1] - 7*'0';
    if (c == '0') {
        c = ' ';
    }
    return c;
}





void Extend(char MINE[][COLS], char SHOW[][COLS], int x, int y)
{
    if (SHOW[x][y] == ' ' && x >= 1 && x <= ROW && y >= 1 && y <= COL) {

        if (SHOW[x][y-1] == '*') {
            
            SHOW[x][y-1] = ADD(MINE, x, y-1);
            Extend(MINE, SHOW, x, y-1);
    
        }
        
        
        if (SHOW[x-1][y-1] == '*') {
            
            SHOW[x-1][y-1] = ADD(MINE, x-1, y-1);
            Extend(MINE, SHOW, x-1, y-1);
            
        }
        
        
        if (SHOW[x-1][y] == '*') {
            
            SHOW[x-1][y] = ADD(MINE, x-1, y);
            Extend(MINE, SHOW, x-1, y);
            
        }
        
        
        
        if (SHOW[x-1][y+1] == '*') {
            
            SHOW[x-1][y+1] = ADD(MINE, x-1, y+1);
            Extend(MINE, SHOW, x-1, y+1);
            
        }
        
        
        
        if (SHOW[x][y+1] == '*') {
            
            SHOW[x][y+1] = ADD(MINE, x, y+1);
            Extend(MINE, SHOW, x, y+1);
        }
        
        if (SHOW[x+1][y+1] == '*') {
            
            SHOW[x+1][y+1] = ADD(MINE, x+1, y+1);
            Extend(MINE, SHOW, x+1, y+1);
        }
        
        if (SHOW[x+1][y] == '*') {
            
            SHOW[x+1][y] = ADD(MINE, x+1, y);
            Extend(MINE, SHOW, x+1, y);        }
        
        if (SHOW[x+1][y-1] == '*') {
            
            SHOW[x+1][y-1] = ADD(MINE, x+1, y-1);
            Extend(MINE, SHOW, x+1, y-1);
            
        }

    }
    
}


void RemoveMINE1(char MINE[][COLS],char SHOW[][COLS], int x, int y)
{
    while ( MINE[x][y] == '1')
    {
        InitMine(MINE);
        
    }
    
    SHOW[x][y] = ADD(MINE, x, y);
    Extend(MINE, SHOW, x, y);
        
    
}


int RemoveMINE2(char MINE[][COLS],char SHOW[][COLS], int x, int y)
{
    if ( MINE[x][y] == '1')
    {
        printf("你被炸死了！\n");
        return 1;
        
    }
    else{
        SHOW[x][y] = ADD(MINE, x, y);
        Extend(MINE, SHOW, x, y);
        
    }
    return 0;
}

int RemoveMINE3(char MINE[][COLS],char SHOW[][COLS], int x, int y)
{
    if ( MINE[x][y] == '1')
    {
        SHOW[x][y] = '$';
        return 0;
        
    }
    else{
        printf("排雷失败！\n");
        return 1;
    }
}


