//
//  main.c
//  猜数字游戏
//
//  Created by admin on 17/11/8.
//  Copyright © 2017年 admin. All rights reserved.
//
//  当输入一个数，大于要猜的数时，提示猜大了，小于要猜的数时，提示猜小了。


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void game()
{
    int i;
    int num;
    
    i = rand()%100 + 1;
    
    while (1) {
        printf("请输入猜的数字:>");
        scanf("%d",&num);
    
        if (num > i) {
            printf("猜大了\n");
        }
    
        else if (num < i){
            printf("猜小了\n");
        }
    
        else{
            printf("猜对了\n\n");
            break;
        }
        
        
    }
    
}


void menu()
{
    printf("************************\n");
    printf("**  1.play    0.exit  **\n");
    printf("************************\n");
    
}


int main(int argc, const char * argv[]) {
    
    int ch = 0;
    srand((unsigned int)time(NULL));
    
    do{
        menu();
        
        printf("请选择:>");
        
        scanf("%d",&ch);
        
        if (ch == 1) {
            printf("游戏开始\n");
            game();
            
        }
        
        else if(ch == 0){
            printf("游戏结束\n");
            break;
        }
        
        else{
            printf("输入错误\n");
        }
        
    }while (ch);
    
    return 0;
}








