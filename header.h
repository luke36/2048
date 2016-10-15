//
//  header.h
//  2048
//
//  Created by luzhihua on 16/10/7.
//  Copyright (c) 2016 by Lu Xiaoyang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define RAND_NUM (rand() % 2 ? 2 : 4)

enum dir { DOWN, UP, RIGHT, LEFT };

extern int wid;
extern int len;

void add_num(int [len][wid], int num);
