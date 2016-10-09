//
//  main.c
//  2048
//
//  Created by luzhihua on 16/9/25.
//  Copyright (c) 2016 by Lu Xiaoyang. All rights reserved.
//

#include "header.h"

int wid;
int len;

int main(int argc, char *argv[]) {
    int c, right_input, t, score = 0;
    enum dir dir;
    
    if (argc == 1) {
        wid = DEFAULT_TABLE_WID;
        len = DEFAULT_TABLE_LEN;
    } else if (argc == 2) {
        if ((wid = len = atoi(argv[1])) <= 0) {
            printf("usage: "USAGE);
            exit(1);
        }
    } else if (argc == 3) {
        if ((wid = atoi(argv[1])) <= 0 || (len = atoi(argv[2])) <= 0) {
            printf("usage: "USAGE);
            exit(1);
        }
    } else {
        printf("usage: "USAGE);
        exit(1);
    }
    
    int table[len][wid];
    
    init_table(table);
    print_table(table, CELL_WID, CELL_LEN, '-', '|', '*');
    printf(SHELL);
    while ((c = getchar()) != EOF){
        right_input = 1;
        switch (c) {
            case KEY_DOWN:
                dir = DOWN;
                break;
            case KEY_UP:
                dir = UP;
                break;
            case KEY_RIGHT:
                dir = RIGHT;
                break;
            case KEY_LEFT:
                dir = LEFT;
                break;
            case KEY_EXIT:
                exit(0);
            default:
                fprintf(stderr, "unknow command %c\n", (char) c);
                right_input = 0;
        }
        if (is_full(table) && !is_mergeable(table)){
            printf("GAME OVER\n");
            exit(0);
        } else if (right_input) {
            t = merge_table(table, dir);
            if (t != NOT_MOVED) {
                score += t;
                add_num(table);
            }
        }
        print_table(table, CELL_WID, CELL_LEN, '-', '|', '*');
        printf("SCORE: %d\n", score);
        printf(SHELL);
        fflush(stdin);
    }
    exit(0);
}
