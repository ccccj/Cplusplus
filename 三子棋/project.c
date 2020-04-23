#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "project.h"

int p_x, p_y;

void InitBoard(char arr[][COL])
{
    int i,j;
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            arr[i][j] = ' ';
        }
    }
}

void DispBoard(char arr[][COL])
{
    int i = 0, j = 0;
    for ( i = 0; i < ROW; i++) {
        for ( j = 0; j < COL; j++) {
            printf(" %c ",arr[i][j]);
            if (j < COL-1) {
                printf("|");
            }
        }
        if (i < ROW-1) {
            printf("\n");
            for (j = 0; j < COL; j++) {
                if (j < COL-1) {
                    printf("---|");
                }
                else
                    printf("---");
            }
            printf("\n");
        }
        else
            printf("\n");
    }
}

void PlayerSet(char arr[][COL])
{
    scanf("%d%d",&p_x,&p_y);
    while (p_x > ROW || p_x <= 0 || p_y > COL || p_y <= 0 || arr[p_x-1][p_y-1] != ' ')
    {
        printf("输入错误，请重新输入:>");
        scanf("%d %d",&p_x,&p_y);
    }
    --p_x;
    --p_y;
    if(arr[p_x][p_y] == ' ') {
        arr[p_x][p_y] = 'X';
    }
}

void com_set_2(char arr[][COL]) {
    while (1) {
        int x = rand() % ROW, y = rand() % COL;
        if ( (x == 0 || x == ROW) && (y == 0 || y == COL) && arr[x][y] == ' ') {
            if ( ((x == p_x + 1 || x == p_x - 1) && y == p_y) || ((y == p_y + 1 || y == p_y - 1) && x == p_x) )
                arr[x][y] = '*';
            break;
        }
    }
}

int set_win(char arr[][COL], char chess) {
	// 第一行
	if (arr[0][0] == chess) {
			if (arr[1][1] == chess && arr[2][2] == ' ') {
					arr[2][2] = '*';
					return 1;
			} else if (arr[1][1] == ' ' && arr[2][2] == chess) {
					arr[1][1] = '*';
					return 1;
			} else if (arr[0][1] == chess && arr[0][2] == ' ') {
					arr[0][2] = '*';
					return 1;
			} else if (arr[0][1] == ' ' && arr[0][2] == chess) {
					arr[0][1] = '*';
					return 1;
			} 
	} else if (arr[0][0] == ' ') {
		 if (arr[1][1] == chess && arr[2][2] == chess) {
					arr[0][0] = '*';
					return 1;
			} else if (arr[0][1] == chess && arr[0][2] == chess) {
					arr[0][0] = '*';
					return 1;
			} 
	}
	// 第二行
	if (arr[1][0] == chess) {
			if (arr[1][1] == chess && arr[1][2] == ' ') {
					arr[1][2] = '*';
					return 1;
			} else if (arr[1][1] == ' ' && arr[1][2] == chess) {
					arr[1][1] = '*';
					return 1;
			}
	} else if (arr[1][0] == ' ') {
			if (arr[1][1] == chess && arr[1][2] == chess) {
					arr[1][0] = '*';
					return 1;
			}
	}
	// 第三行
	if (arr[2][0] == chess) {
			if (arr[2][1] == chess && arr[2][2] == ' ') {
					arr[2][2] = '*';
					return 1;
			} else if (arr[2][1] == ' ' && arr[2][2] == chess) {
					arr[2][1] = '*';
					return 1;
			}
	} else if (arr[2][0] == ' ') {
			if (arr[2][1] == chess && arr[2][2] == chess) {
					arr[2][0] = '*';
					return 1;
			}
	}
	// 第一列
	if (arr[0][0] == chess) {
			if (arr[1][0] == chess && arr[2][0] == ' ') {
					arr[2][0] = '*';
					return 1;
			} else if (arr[1][0] == ' ' && arr[2][0] == chess) {
					arr[1][0] = '*';
					return 1;
			}
	} else if (arr[0][0] == ' ') {
			if (arr[1][0] == chess && arr[2][0] == chess) {
					arr[0][0] = '*';
					return 1;
			}
	}
	// 第二列
	if (arr[0][1] == chess) {
			if (arr[1][1] == chess && arr[2][1] == ' ') {
					arr[2][1] = '*';
					return 1;
			} else if (arr[1][1] == ' ' && arr[2][1] == chess) {
					arr[1][1] = '*';
					return 1;
			}
	} else if (arr[0][1] == ' ') {
			if (arr[1][1] == chess && arr[2][1] == chess) {
					arr[0][1] = '*';
					return 1;
			}
	}
	// 第三列
	if (arr[0][2] == chess) {
			if (arr[1][1] == chess && arr[2][0] == ' ') {
          // 斜对角
					arr[2][0] = '*';
					return 1;
			} else if (arr[1][1] == ' ' && arr[0][2] == chess) {
					arr[1][1] = '*';
					return 1;
			} else if (arr[1][2] == chess && arr[2][2] == ' ') {
					arr[2][2] = '*';
					return 1;
			} else if (arr[1][2] == ' ' && arr[2][2] == chess) {
					arr[1][2] = '*';
					return 1;
			}
	} else if (arr[0][2] == ' ') {
			if (arr[1][1] == chess && arr[2][0] == chess) {
					arr[0][2] = '*';
					return 1;
			} else if (arr[1][2] == chess && arr[2][2] == chess) {
					arr[0][2] = '*';
					return 1;
			}
	}
	return 0;
}

void com_set_block(char arr[][COL]) {
	if (set_win(arr, '*')) {
		return;
	}
	if (set_win(arr, 'X')) {
		return;
	}
	while (1) {
			int x = rand() % ROW, y = rand() % COL;
			if ( arr[x][y] == ' ') {
					arr[x][y] = '*';
					break;
			}
	}
}

void ComputerSet(char arr[][COL], int _time, int flag)
{
    if (flag == 1) {
        if (_time == 2) {
            // 电脑先走，电脑第二次走
            if ( (p_x != 0 && p_x != ROW) && (p_y != 0 && p_y != COL) ) {
                // 玩家第一次走在边中间，走贴着这个点的角位置
                com_set_2(arr);
            } else {
                com_set_block(arr);
            }
        } else {
            // 电脑不是第二次走
            com_set_block(arr);
        }
    } else {
        if (_time == 1) {
            // 玩家先走，电脑第一次走
            if (p_x != ROW/2 || p_y != COL/2) {
                arr[ROW/2][COL/2] = '*';
            } else {
							  // 走在角上
								if (set_win(arr, '*')) {
									return;
								}
								if (set_win(arr, 'X')) {
									return;
								}
                while (1) {
                    int x = rand() % ROW, y = rand() % COL;
                    if ( (x == 0 || x == ROW) && (y == 0 || y == COL) && arr[x][y] == ' ') {
                        arr[x][y] = '*';
                        break;
                    }
                }
            }
        } else {
            // 玩家先走，电脑不是第一次走
            com_set_block(arr);
        }
    }
}

int IsFull(char arr[][COL])
{
    int i,j;
    int flag = DRAW;
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            if (arr[i][j] == ' ') {
                flag = UNFULL;
            }
        }
    }
    return flag;
}

int IsWin(char arr[][COL])
{
    int i,j,flag = UNFULL;
    for (i = 0; i < ROW; i++) {
        for (j = 1; j < COL-1; j++) {
            if (arr[i][j-1] == arr[i][j] && arr[i][j] == arr[i][j+1] && arr[i][j] == 'X' ) {
                flag = PLAYERW;
            }
        }
    }
    for (j = 0; j < COL; j++) {
        for (i = 1; i < ROW-1; i++) {
            if (arr[i-1][j] == arr[i][j] && arr[i][j] == arr[i+1][j] && arr[i][j] == 'X' ) {
                flag = PLAYERW;
            }
        }
    }
    for (i = 0; i < ROW; i++) {
        for (j = 1; j < COL-1; j++) {
            if (arr[i][j-1] == arr[i][j] && arr[i][j] == arr[i][j+1] && arr[i][j] == '*' ) {
                flag = COMW;
            }
        }
    }
    for (j = 0; j < COL; j++) {
        for (i = 1; i < ROW-1; i++) {
            if (arr[i-1][j] == arr[i][j] && arr[i][j] == arr[i+1][j] && arr[i][j] == '*' ) {
                flag = COMW;
            }
        }
    }
    
    for (i = 1; i < ROW-1; i++) {
        for (j = 1; j < COL-1; j++) {
            if (arr[i-1][j-1] == arr[i][j] && arr[i][j] == arr[i+1][j+1] && arr[i][j] == 'X' ) {
                flag = PLAYERW;
            }
        }
    }
    for (i = 1; i < ROW-1; i++) {
        for (j = 1; j < COL-1; j++) {
            if (arr[i-1][j+1] == arr[i][j] && arr[i][j] == arr[i+1][j-1] && arr[i][j] == 'X' ) {
                flag = PLAYERW;
            }
        }
    }
    for (i = 1; i < ROW-1; i++) {
        for (j = 1; j < COL-1; j++) {
            if (arr[i-1][j-1] == arr[i][j] && arr[i][j] == arr[i+1][j+1] && arr[i][j] == '*' ) {
                flag = COMW;
            }
        }
    }
    for (i = 1; i < ROW-1; i++) {
        for (j = 1; j < COL-1; j++) {
            if (arr[i-1][j+1] == arr[i][j] && arr[i][j] == arr[i+1][j-1] && arr[i][j] == '*' ) {
                flag = COMW;
            }
        }
    }
    if (flag == UNFULL) {
        int ret = IsFull(arr);
        if (ret == DRAW) {
            flag = DRAW;
        }
    }
    return flag;
}

