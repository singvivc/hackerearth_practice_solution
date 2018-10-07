//
//  still_maximum.cpp
//  hackerearth_practice_solution
//
//  Created by Vivek Singh on 06/10/18.
//  Copyright © 2018 Vivek Singh. All rights reserved.
//
// https://www.hackerearth.com/practice/data-structures/disjoint-data-strutures/basics-of-disjoint-data-structures/practice-problems/algorithm/still-maximum/

#include <iostream>
#include <set>

using namespace std;

const int N = 1e5+10;
int parent[N], rnk[N];
multiset<int> values[N];
int u[N], v[N], val[N];
int ans[N], remve[N];

void make(int v)
{
    parent[v] = v;
    rnk[v] = 0;
    values[v].insert(val[v]);
}

int find(int v)
{
    if(parent[v] != v)
        parent[v] = find(parent[v]);
    return parent[v];
}

void merge(int a, int b)
{
    for(auto it : values[b])
    {
        values[a].insert(it);
    }
    values[b].clear();
}

void make_union(int a, int b)
{
    a = find(a); b = find(b);
    if(a != b)
    {
        if(rnk[a] < rnk[b])
            swap(a, b);
        parent[b] = a;
        merge(a, b);
        if(rnk[a] == rnk[b])
            rnk[a]++;
    }
}

int main()
{
    int n;
    cin >> n;
    
    for(int i = 1; i < n; i++) cin >> u[i] >> v[i];
    for(int i = 1; i <= n; ++i) cin >> val[i];
    
    set<int> items;
    for(int i = 1; i < n; ++i) {
        cin >> remve[i];
        items.insert(remve[i]);
    }
    
    for(int i = 0; i <= n; ++i){
        make(i);
    }
    int x;
    int mx = 0;
    
    for(int i = n-1; i >= 1; --i){
        ans[i] = mx;
        x = remve[i];
        make_union(u[x], v[x]);
        
        int tmp = find(u[x]);
        mx = max(mx, *(--values[tmp].end()) - (*values[tmp].begin()));
    }
    
    for(int i = 1; i < n; ++i){
        cout << ans[i] << endl;
    }
}
