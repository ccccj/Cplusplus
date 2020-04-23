//
//  main.c
//  扫雷
//
//  Created by admin on 17/12/5.
//  Copyright © 2017年 Amon. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "project.h"
int mine = MINES;

void menu()
{
    printf("/////////////////////////////////\n");
    printf("//      1.play     0.exit      //\n");
    printf("/////////////////////////////////\n");
    
}


void game()
{
    srand((unsigned int)time(NULL));
    
    char MINE[ROWS][COLS];
    char SHOW[ROWS][COLS];
    
    InitMine(MINE);
    InitSHOW(SHOW);
    
    //DisPlay(MINE);
    DisPlay(SHOW);
    
    
    printf("请输入您要选的位置\n如第一行第二列无雷:1 1 0\n如第一行第二列排雷:1 1 $\n:>");
    int x,y;
    char k;
    int flag = 0;
    while (scanf("%d %d %c",&x,&y,&k) != EOF ) {
        
        switch (k) {
            case '0':
                if (x >= 1 && x <= ROW && y >= 1 && y <= COL) {
                    if (flag == 0) {
                        RemoveMINE1(MINE,SHOW,x,y);
                        DisPlay(SHOW);
                        printf("请输入您要选的位置:>");
                        flag++;
                        
                        
                    }
                    
                    else{
                        int ret = RemoveMINE2(MINE,SHOW,x,y);
                        if (ret == 1) {
                            return;
                        }
                        DisPlay(SHOW);
                        printf("请输入您要选的位置:>");
                    }
                }
                
                else{
                    printf("输入错误，请重新输入:>");
                }
                break;
            
            case '$':{
                
                int ret = RemoveMINE3(MINE,SHOW,x,y);
                if (ret == 1) {
                    return;
                }
            
                DisPlay(SHOW);
                printf("排雷成功！\n");
                mine--;
                if (mine == 0) {
                    printf("恭喜您通关！\n");
                    return;
                } else
                    printf("请输入您要选的位置:>");
            }
                break;
                
            default:
                printf("输入错误，请重新输入:>");
                break;
        }
        
        
        
        
        
    
    }
    
}


int main(int argc, const char * argv[]) {

    
    int CHOICE;
    menu();
    
    do {
        printf("请输入您的选择:>");
        scanf("%d",&CHOICE);
        
        switch (CHOICE) {
            case 1:
                game();
                menu();
                break;
            case 0:
                printf("游戏结束！\n");
                return 0;
            default:
                printf("选择错误！\n");
                break;
        }
    } while (CHOICE);
    
    
    return 0;
}
