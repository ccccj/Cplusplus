#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <pthread.h>
#include "snake.h"

void SetPos (int x, int y)
{
    printf("\033[%d;%dH", y, x);
    printf("\033[0m");
}

void menu (void)
{
    SetPos(16, 8);
    printf("////////////////////////////////////////\n");
    SetPos(16, 9);
    printf("//                                    //\n");
    SetPos(16, 10);
    printf("//        Welcome to Snake Game      //\n");
    SetPos(16, 11);
    printf("//                                    //\n");
    SetPos(16, 12);
    printf("//           [choose level]           //\n");
    SetPos(16, 13);
    printf("//            1.easy                  //\n");
    SetPos(16, 14);
    printf("//            2.normal                //\n");
    SetPos(16, 15);
    printf("//            3.hard                  //\n");
    SetPos(16, 16);
    printf("//                                    //\n");
    SetPos(16, 17);
    printf("//                  i                 //\n");
    SetPos(16, 18);
    printf("//   Please use [ j k l ] to control  //\n");
    SetPos(16, 19);
    printf("//                                    //\n");
    SetPos(16, 20);
    printf("////////////////////////////////////////\n");
    SetPos(20, 22);
    int choice;
    scanf("%d",&choice);
    if (choice == EASY){
        SPEED = 150000;
    } else if (choice == NORMAL) {
        SPEED = 100000;
    } else if (choice == HARD) {
        SPEED = 50000;
    }
}

void CreateMap (void)
{
    int i;
    for (i = 2; i <= 2*COL; i += 2) {
        SetPos(i,1);
        printf(FOOD);
        SetPos(i,ROW);
        printf(FOOD);
    }
    for (i = 2; i <= ROW-1; i++){
        SetPos(2,i);
        printf(FOOD);
        SetPos(2*COL,i);
        printf(FOOD);
    }
}

void SetFood (pSnakeGame ps)
{
    ps->food = (pSnakeNode)malloc(sizeof(SnakeNode));
    ps->food->next = NULL;
flag:
    do {
        ps->food->x = rand() % (2*COL-5) + 4;
    } while (ps->food->x % 2 != 0);
    ps->food->y = rand() % (ROW-2) + 2;
    pSnakeNode cur = ps->snake;
    while (cur != NULL) {
        if (ps->food->x == cur->x && ps->food->y == cur->y){
            goto flag;
        } else {
            cur = cur->next;
        }
    }
}

void InitSnake (pSnakeGame ps)
{
    srand((unsigned)time(NULL));
    pSnakeNode cur = (pSnakeNode)malloc(sizeof(SnakeNode));
    cur->next = NULL;
    cur->x = INIT_X;
    cur->y = INIT_Y;
    
    int i;
    for (i = 1; i < 5; i++) {
        pSnakeNode new_node = (pSnakeNode)malloc(sizeof(SnakeNode));
        new_node->x = cur->x + 2;
        new_node->y = cur->y;
        new_node->next = cur;
        cur = new_node;
    }
    ps->snake = cur;
    ps->dir = RIGHT;
    ps->status = OK;
    ps->movespeed = SPEED;
    SetFood(ps);
}

void SnakePrint (pSnakeGame ps)
{
    pSnakeNode cur = ps->snake;
    while (cur != NULL) {
        SetPos(cur->x,cur->y);
        printf(FOOD);
        cur = cur->next;
    }
}

void FoodPrint (pSnakeGame ps)
{
    SetPos(ps->food->x, ps->food->y);
    printf(FOOD);
}

void GamePrint (pSnakeGame ps)
{
    CreateMap();
    SnakePrint(ps);
    FoodPrint(ps);
}

void SnakeMove (pSnakeGame ps)
{
    pSnakeNode new_node = (pSnakeNode)malloc(sizeof(SnakeNode));
    switch (ps->dir)
    {
        case UP:
            new_node->x = ps->snake->x;
            new_node->y = ps->snake->y - 1;
            break;
        case DOWN:
            new_node->x = ps->snake->x;
            new_node->y = ps->snake->y + 1;
            break;
        case LEFT:
            new_node->x = ps->snake->x - 2;
            new_node->y = ps->snake->y;
            break;
        case RIGHT:
            new_node->x = ps->snake->x + 2;
            new_node->y = ps->snake->y;
            break;
        default:
            break;
    }
    new_node->next = ps->snake;
    ps->snake = new_node;
    if (ps->snake->x == ps->food->x
        && ps->snake->y == ps->food->y) {
        free(ps->food);
        count++;
        SetFood(ps);
        ps->movespeed -= 1000;
        FoodPrint(ps);
        SnakePrint(ps);
        fflush(stdout);
        return;
    }
    pSnakeNode cur = ps->snake;
    while (cur->next->next != NULL) {
        SetPos(cur->x,cur->y);
        printf(FOOD);
        cur = cur->next;
    }
    SetPos(cur->next->x,cur->next->y);
    printf("  ");
    free(cur->next);
    cur->next = NULL;
    fflush(stdout);
}

void KillBySelf(pSnakeGame ps)
{
    pSnakeNode cur = ps->snake->next;
    while (cur != NULL) {
        if (cur->x == ps->snake->x && cur->y == ps->snake->y) {
            ps->status = KILL_BY_SELF;
            break;
        }
        cur = cur->next;
    }
}

void KillByWall(pSnakeGame ps)
{
    if (ps->snake->x <= 2 || ps->snake->x >= COL*2
        || ps->snake->y <= 1 || ps->snake->y >= ROW) {
        ps->status = KILL_BY_WALL;
    }
}

void GetDir (pSnakeGame ps, char ch)
{
    switch (ch){
        case 'j':
            if (ps->dir != RIGHT) {
                ps->dir = LEFT;
            }
            break;
        case 'l':
            if (ps->dir != LEFT) {
                ps->dir = RIGHT;
            }
            break;
        case 'i':
            if (ps->dir != DOWN) {
                ps->dir = UP;
            }
            break;
        case 'k':
            if (ps->dir != UP){
                ps->dir = DOWN;
            }
            break;
        default:
            break;
    }
}

struct termios org_opts;
int getch()
{
    int c=0;
    struct termios new_opts;
    int res=0;
    res=tcgetattr(STDIN_FILENO, &org_opts);
    memcpy(&new_opts, &org_opts, sizeof(new_opts));
    new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
    c=getchar();
    res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
    return c;
}

int dir = 'd';
void* r( void *arg)
{
    while ( 1 ) {
        dir = getch();
        usleep(1000);
        fflush(stdout);
    }
}

void SnakeRun (pSnakeGame ps)
{
    pthread_t tid;
    pthread_create(&tid, NULL, r, NULL);
    do {
        GetDir(ps, dir);
        SnakeMove(ps);
        usleep(ps->movespeed);
        fflush(stdout);
        KillBySelf(ps);
        KillByWall(ps);
    } while (ps->status == OK);
    SetPos(10, 10);
    if (ps->status == KILL_BY_WALL) {
        printf("哈哈你被撞死啦!\n");
    } else if(ps->status == KILL_BY_SELF) {
        printf("哈哈你咬到自己啦！\n");
    }
    SetPos(10, 11);
    printf("一共吃到%d个苹果\n",count);
}

int main ()
{
    system("clear");
    menu();
    system("clear");
    SnakeGame s;
    InitSnake(&s);
    GamePrint(&s);
    SnakeRun(&s);
    
    tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
    SetPos(5, 30);
    return 0;
}
