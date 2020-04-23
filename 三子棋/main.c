#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "project.h"

int flag, _time;

void menu()
{
    printf("//////////////////////////////////\n");
    printf("//       1.Play    0.exit       //\n");
    printf("//////////////////////////////////\n");
}

void PalyGame(char arr[][COL])
{
    flag = 0;
    _time = 0;
    int _rand = rand();
    if (_rand % 2 == 1) {
        // 电脑先走
        flag = 1;
        printf("电脑走:\n");
        arr[ROW/2][COL/2] = '*';
        ++_time;
    }
    
    DispBoard(arr);
    while (1) {
        printf("玩家走:\n");
        printf("请输入要下棋的坐标(如:1 1):>");
        PlayerSet(arr);
        DispBoard(arr);
        
        int ret;
        ret = IsWin(arr);
        switch (ret) {
            case PLAYERW:
                printf("玩家赢！\n");
                return;
            case COMW:
                printf("电脑赢！\n");
                return;
            case DRAW:
                printf("平局！\n");
                return;
            default:
                break;
        }
        printf("电脑走:\n");
        ComputerSet(arr, ++_time, flag);
        DispBoard(arr);
        
        ret = IsWin(arr);
        switch (ret) {
            case PLAYERW:
                printf("玩家赢\n");
                return;
            case COMW:
                printf("电脑赢！\n");
                return;
            case DRAW:
                printf("平局！\n");
                return;
            default:
                break;
        }
    }
}

void game()
{
    int input = 0;
    char arr[ROW][COL];
    menu();
    do{
        printf("请输入选项:>");
        scanf("%d",&input);
        switch (input) {
            case PLAY:
                InitBoard(arr);
                PalyGame(arr);
                menu();
                break;
            case EXIT:
                printf("游戏结束！\n");
                break;
            default:
                printf("选择错误！\n");
                break;
        }
    }while (input);
}

int main(int argc, const char * argv[]) {
	system("clear");
  srand((unsigned int)time(NULL));
  game();
  return 0;
}
