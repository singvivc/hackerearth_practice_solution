//
//  segment_tree_lazy_propogation.cpp
//  hackerearth_practice_solution
//
//  Created by Vivek Singh on 02/10/18.
//  Copyright © 2018 Vivek Singh. All rights reserved.
#include "segment_tree.h"

int N, Q;

// increment the value for the given range
void update(int* seg, int* lazy, int low, int high, int ul, int uh, int delta, int pos);

// query for the minimum value for the given range
int  query(int* seg, int* lazy, int low, int high, int ul, int uh, int pos);

// solve for each individual queries
void solve_for_queries(int* seg, int* lazy, int Q);

// main
int main()
{
    cin >> N >> Q; // input N Q eg. 5 4 (5, the number of elements in an array, 4, the number of queries)
    int st = next_power_of_two(N);
    int seg[segmentLength(st)], lazy[segmentLength(st)];
    int arr[N];
    
    for(int i = 0; i < N; i++) cin >> arr[i]; // initialize the array eg. {-1, 2, 4, 1, 7, 1, 3, 2}
    construct_segment_tree(arr, seg, 0, N - 1, 0);
    solve_for_queries(seg, lazy, Q);
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

void solve_for_queries(int* seg, int* lazy, int Q) {
    char type; // query type = i ∈ {i, q} where i is increment and q is query
    cout << endl;
    while(Q-- > 0) {
        cin >> type;
        if(type == 'i') {
            int l, h, val; // low, high, value Eg. 0 3 3
            cin >> l >> h >> val;
            update(seg, lazy, 0, N - 1, l, h, val, 0);
        }
        
        if(type == 'q') {
            int l, r;
            cin >> l >> r;
            int ans = query(seg, lazy, 0, N - 1, l, r, 0);
            cout << ans << endl;
        }
    }
}

void update(int* seg, int* lazy, int low, int high, int ul, int uh, int delta, int pos) {
    if(low > high) return;
    if(lazy[pos]) {
        seg[pos] += lazy[pos];
        if(low != high) {
            lazy[left(pos)]  += lazy[pos];
            lazy[right(pos)] += lazy[pos];
        }
        lazy[pos] = 0;
    }
    if(uh < low || high < ul) return;
    if(ul <= low && uh >= high) {
        seg[pos] += delta;
        if(low != high) {
            lazy[left(pos)]  += delta;
            lazy[right(pos)] += delta;
        }
        return;
    }
    int mid = (low + high) >> 1;
    update(seg, lazy, low, mid, ul, uh, delta, left(pos));
    update(seg, lazy, mid + 1, high, ul, uh, delta, right(pos));
    seg[pos] = min(seg[left(pos)], seg[right(pos)]);
}

int query(int* seg, int* lazy, int low, int high, int ql, int qh, int pos) {
    if(low > high) return INT_MAX;
    if(lazy[pos]) {
        seg[pos] += lazy[pos];
        if(low != high) {
            lazy[left(pos)]  += lazy[pos];
            lazy[right(pos)] += lazy[pos];
        }
        lazy[pos] = 0;
    }
    
    if(qh < low || high < ql) return INT_MAX;
    if(ql <= low && qh >= high) {
        return seg[pos];
    }
    int mid = (low + high) >> 1;
    int left  = query(seg, lazy, low, mid, ql, qh, left(pos));
    int right = query(seg, lazy, mid + 1, high, ql, qh, right(pos));
    return min(left, right);
}
