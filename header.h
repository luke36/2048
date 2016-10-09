//
//  header.h
//  2048
//
//  Created by luzhihua on 16/10/7.
//  Copyright (c) 2016 by Lu Xiaoyang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define EMPTY 0
#define NOT_MOVED -1
#define DEFAULT_TABLE_WID 4
#define DEFAULT_TABLE_LEN 4
#define SCREEN_WID 30
#define CELL_WID (SCREEN_WID / wid)
#define CELL_LEN (CELL_WID / 2)
#define SHELL ">>> "
#define USAGE "2048 [width] [length]"

enum dir { DOWN, UP, RIGHT, LEFT };
enum dir_key { KEY_DOWN = 's', KEY_UP = 'w', KEY_RIGHT = 'd', KEY_LEFT = 'a', KEY_EXIT = 'q' };

extern int wid;
extern int len;

void add_num(int [len][wid]);
void init_table(int [len][wid]);
int is_full(const int [len][wid]);
int is_mergeable(const int [len][wid]);
int merge_table(int [len][wid], enum dir);
void print_table(const int [len][wid], int, int, char, char, char);
