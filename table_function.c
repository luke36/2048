//
//  table_function.c
//  2048
//
//  Created by luzhihua on 16/10/7.
//  Copyright (c) 2016 by Lu Xiaoyang. All rights reserved.
//

#include "header.h"

#define EMPTY 0

void init_table(int table[len][wid], int init_num)
{
    int i, j;
    
    for (i = 0; i < len; i++)
        for (j = 0; j < wid; j++)
            table[i][j] = EMPTY;
    for (i = 0; i < init_num; i++)
        add_num(table, RAND_NUM);
}

int is_full(const int table[len][wid])
{
    int i, j;
    
    for (i = 0; i < len; i++)
        for (j = 0; j < len; j++)
            if (!table[i][j])
                return 0;
    return 1;
}

int is_mergeable(const int table[len][wid])
{
    int i, j;
    
    for (i = 0; i < len - 1; i++)
        for (j = 0; j < wid; j++)
            if (table[i][j] == table[i + 1][j])
                return 1;
    for (i = 0; i < len; i++)
        for (j = 0; j < wid - 1; j++)
            if (table[i][j] == table[i][j + 1])
                return 1;
    return 0;
}

#define NOT_MOVED -1

int *get_element(int [len][wid], int, int, enum dir);

int merge_table(int table[len][wid], enum dir dir)
{
    int i, j, moved, *p, score = 0;
    int move_table(int [len][wid], enum dir);
    
    moved = move_table(table, dir);
    for (i = len - 2; i >= 0; i--)
        for (j = 0; j < wid; j++)
            if (*(p = get_element(table, i, j, dir)) == *get_element(table, i + 1, j, dir) && *p != EMPTY) {
                score += *get_element(table, i + 1, j, dir) *= 2;
                *p = EMPTY;
                move_table(table, dir);
                moved = 1;
            }
    return moved ? score : NOT_MOVED;
}

int move_table(int table[len][wid], enum dir dir)
{
    int i, j, k, *p, moved = 0;
    
    for (i = len - 2; i >= 0; i--)
        for (j = 0; j < wid; j++) {
            for (k = i + 1; k < len; k++)
                if (*get_element(table, k, j, dir) != EMPTY)
                    break;
            if (k != i + 1 && *(p = get_element(table, i, j, dir)) != EMPTY) {
                *get_element(table, k - 1, j, dir) = *p;
                *p = EMPTY;
                moved = 1;
            }
        }
    return moved;
}

int *get_element(int table[len][wid], int m, int n, enum dir dir)
{
    if (dir == DOWN)
        return &table[m][n];
    else if (dir == UP)
        return &table[len - m - 1][wid - n - 1];
    else if (dir == RIGHT)
        return &table[len - n - 1][m];
    return &table[n][wid - m - 1];
}

#include <time.h>

void add_num(int table[len][wid], int num)
{
    int *p;
    
    for (;;)
        if (*(p = &table[rand() % len][rand() % wid]) == EMPTY) {
            *p = num;
            return;
        }
}

#include <stdio.h>
#include <string.h>

#define WID_CHAR '-'
#define LEN_CHAR '|'
#define NODE_CHAR '*'

void print_table(const int table[len][wid], int cell_wid, int cell_len)
{
    int i, j, k;
    void print_times(char, int), print_mid(int, int);
    
    for (i = 0; i < len; i++) {
        for (j = 0; j < wid; j++) {
            putchar(NODE_CHAR);
            print_times(WID_CHAR, cell_wid);
        }
        putchar(NODE_CHAR);
        printf("\n");
        for (j = 0; j < cell_len; j++) {
            for (k = 0; k < wid; k++) {
                putchar(LEN_CHAR);
                if (j == cell_len / 2 && table[i][k] != EMPTY)
                    print_mid(table[i][k], cell_wid);
                else
                    print_times(' ', cell_wid);
            }
            putchar(LEN_CHAR);
            printf("\n");
        }
    }
    for (i = 0; i < wid; i++) {
        putchar(NODE_CHAR);
        print_times(WID_CHAR, cell_wid);
    }
    putchar(NODE_CHAR);
    printf("\n");
}

void print_times(char c, int times)
{
    for (; times-- > 0;)
        putchar(c);
}

#include <windows.h>

#define DIVID 256
#define LOW_COLOR FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
#define HIGH_COLOR FOREGROUND_INTENSITY | FOREGROUND_RED
#define DEFAULT_COLOR FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE

void print_mid(int num, int wid)
{
    int len = 1, n = num;
    
    while ((num /= 10) > 0)
        len++;
    print_times(' ', (wid - len) / 2.0 + 0.5);
    if (num < DIVID)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LOW_COLOR);
    else
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), HIGH_COLOR);
    printf("%d", n);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DEFAULT_COLOR);
    print_times(' ', (wid - len) / 2);
}
