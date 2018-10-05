//
//  structure_using_blocks.cpp
//  c++_datastructure
//
//  Created by Vivek Singh on 04/10/18.
//  Copyright © 2018 Vivek Singh. All rights reserved.
//
// https://www.hackerearth.com/practice/data-structures/advanced-data-structures/segment-trees/practice-problems/algorithm/blocks-2/

#include <iostream>
using namespace std;

#define left(i)         2 * i + 1
#define right(i)        2 * i + 2

const int MAX = 2000001, MAX_X = 200000;
int segment[MAX], lazy[MAX];

int query(int low, int high, int ql, int qh, int pos);
void update(int low, int high, int ul, int uh, int delta, int pos);

void update_lazy(int pos, int low, int high);

void forEachBlocks() {
    int l, h, p, c, x;
    cin >> l >> h >> p >> c >> x;
    
    int mq = query(0, MAX_X, x, x + l - 1, 0);
    if(c) {
        update(0, MAX_X, x, x + l - 1, mq + 1, 0);
        update(0, MAX_X, x + p - 1, x + p - 1, mq + h + 1, 0);
    } else {
        int mt = query(0, MAX_X, x + p - 1, x + p - 1, 0);
        if(mq - mt >= h) {
            update(0, MAX_X, x, x + l - 1, mq + 1, 0);
        } else {
            update(0, MAX_X, x, x + l - 1, mt + h + 1, 0);
        }
    }
}

int query(int low, int high, int ql, int qh, int pos) {
    if(low > high)
        return 0;
    if(lazy[pos])
        update_lazy(pos, low, high);
    if(qh < low || ql > high) return 0;
    if(ql <= low && qh >= high) {
        return segment[pos];
    }
    int mid = (low + high) >> 1;
    return max(query(low, mid, ql, qh, left(pos)), query(mid + 1, high, ql, qh, right(pos)));
}

void update(int low, int high, int ul, int uh, int delta, int pos) {
    if(low > high)
        return;
    if(lazy[pos])
        update_lazy(pos, low, high);
    if(uh < low || ul > high) return;
    if(ul <= low && uh >= high) {
        segment[pos] = delta;
        if(low != high) {
            lazy[left(pos)] = lazy[right(pos)] = delta;
        }
        return;
    }
    int mid = (low + high) >> 1;
    update(low, mid, ul, uh, delta, left(pos));
    update(mid + 1, high, ul, uh, delta, right(pos));
    segment[pos] = max(segment[left(pos)], segment[right(pos)]);
}

void update_lazy(int pos, int low, int high) {
    segment[pos] = lazy[pos];
    lazy[left(pos)] = lazy[right(pos)] = lazy[pos];
    lazy[pos] = 0;
}

int main()
{
    int blocks;
    cin >> blocks;
    
    while(blocks-- > 0) {
        forEachBlocks();
    }
    cout << segment[0] << endl;
    return 0;
}
