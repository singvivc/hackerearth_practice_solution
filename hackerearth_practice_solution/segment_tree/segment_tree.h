//
//  segment_tree.h
//  hackerearth_practice_solution
//
//  Created by Vivek Singh on 02/10/18.
//  Copyright © 2018 Vivek Singh. All rights reserved.
//
#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H

#include <iostream>
#include <string>
#include <limits>
#include <cmath>

#define left(i)          2 * i + 1
#define right(i)         2 * i + 2
#define segmentLength(i) 2 * i - 1

using namespace std;

int next_power_of_two(int num)
{
    if(num == 0) return 1;
    if(num > 0 && (num & (num - 1)) == 0) return num;
    
    while((num & (num - 1)) > 0) {
        num = (num & (num - 1));
    }
    return num << 1;
}

void construct_segment_tree(int*, int*, int, int, int);
#endif /* SEGMENT_TREE_H */
