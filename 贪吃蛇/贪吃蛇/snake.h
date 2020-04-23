//
//  snake.h
//  贪吃蛇
//
//  Created by admin on 17/12/23.
//  Copyright © 2017年 Amon. All rights reserved.
//

#ifndef snake_h
#define snake_h

 #define FOOD "[]"

 #define INIT_X 16
 #define INIT_Y 8

 #define EASY 1
 #define NORMAL 2
 #define HARD 3

 #define ROW 20
 #define COL 25

 int SPEED;
 int count = 0;

 enum DIRCTION {
     UP,
     DOWN,
     LEFT,
     RIGHT
 };

 enum STATUS {
     OK,
     KILL_BY_WALL,
     KILL_BY_SELF,
     END_NORMAL
 };
 typedef struct SnakeNode {
     int x;
     int y;
     struct SnakeNode* next;
 }SnakeNode,*pSnakeNode;

 typedef struct Game {
     pSnakeNode snake;    //蛇的头结点
     pSnakeNode food;     //食物
     enum DIRCTION dir;   //移动方向
     enum STATUS status;  //状态
     int movespeed;
 }SnakeGame,*pSnakeGame;

#endif /* snake_h */
