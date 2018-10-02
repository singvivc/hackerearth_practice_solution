//
//  range_min_query.cpp
//  hackerearth_practice_solution
//
//  Created by Vivek Singh on 02/10/18.
//  Copyright © 2018 Vivek Singh. All rights reserved.
//

#include "segment_tree.h"

// number of elements in an original array
int N, Q;

void solve_for_each_query(int*, int*);
int query(int*, int, int, int, int, int);
void update(int*, int, int, int, int, int);

int main()
{
    cin >> N >> Q;
    int st = next_power_of_two(N);
    int arr[N], seg[2 * st - 1];
    
    for(int i = 0; i < N; i++) {
        int elements;
        cin >> elements;
        arr[i] = elements;
    }
    
    construct_segment_tree(arr, seg, 0, N - 1, 0);
    solve_for_each_query(arr, seg);
    return 0;
}

void construct_segment_tree(int* arr, int* seg, int low, int high, int pos) {
    if(low == high) {
        seg[pos] = arr[low];
        return;
    }
    int mid = (low + high) >> 1;
    construct_segment_tree(arr, seg, low, mid, left(pos));
    construct_segment_tree(arr, seg, mid + 1, high, right(pos));
    seg[pos] = min(seg[left(pos)], seg[right(pos)]);
}

void solve_for_each_query(int* arr, int* seg) {
    cout << "\n";
    while(Q-- > 0) {
        char op;
        int x, y, ans;
        cin >> op >> x >> y;
        switch(op) {
            case 'q':
                ans = query(seg, 0, N - 1, x - 1, y - 1, 0);
                cout << ans << endl;
                break;
                
            case 'u':
                arr[x - 1] = y;
                update(seg, 0, N - 1, x - 1, y, 0);
                break;
                
            default :
                cout << "Bad request!" << "\n Please try again with either of 'q' or 'u' as an option" << endl;
        }
    }
}

int query(int* seg, int low, int high, int ql, int qr, int pos) {
    if(low == high) {
        return seg[pos];
    }
    if(qr < low || ql > high) return INT_MAX;
    
    if(ql <= low && qr >= high) {
        return seg[pos];
    }
    int mid = (low + high) >> 1;
    int left = query(seg, low, mid, ql, qr, left(pos));
    int right = query(seg, mid + 1, high, ql, qr, right(pos));
    return min(left, right);
}

void update(int* seg, int low, int high, int idx, int val, int pos) {
    if(low == high) {
        seg[pos] = val;
        return;
    }
    int mid = (low + high) >> 1;
    if(low <= idx && idx <= mid) {
        update(seg, low, mid, idx, val, left(pos));
    } else {
        update(seg, mid + 1, high, idx, val, right(pos));
    }
    seg[pos] = min(seg[left(pos)], seg[right(pos)]);
}
