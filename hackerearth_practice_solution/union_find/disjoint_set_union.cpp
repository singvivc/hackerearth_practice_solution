//
//  disjoint_set_union.cpp
//  hackerearth_practice_solution
//
//  Created by Vivek Singh on 06/10/18.
//  Copyright © 2018 Vivek Singh. All rights reserved.
//
// https://www.hackerearth.com/practice/data-structures/disjoint-data-strutures/basics-of-disjoint-data-structures/tutorial/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void printAns(int*, int);

class disjoint_set_union {
private:
    // N is the number of nodes
    int N;
    int *set, *size;
    
public:
    disjoint_set_union(int nodes) {
        N = nodes;
        set = (int*) malloc((N + 1) * sizeof(int));
        size = (int*) malloc((N + 1) * sizeof(int));
        for(int i = 1; i < N + 1; i++) {
            set[i] = i;
            size[i] = 1;
        }
    }
    ~disjoint_set_union();
    void make_union(int p, int q);
    int  get_root(int p);
    int* get_size();
};

disjoint_set_union :: ~disjoint_set_union()
{
    delete set;
    delete size;
}

void disjoint_set_union :: make_union(int p, int q)
{
    int root_p = get_root(p), root_q = get_root(q);
    if(root_p == root_q) return;
    
    if(size[root_p] < size[root_q])
    {
        set[root_p] = set[root_q];
        size[root_q] += size[root_p];
        size[root_p] = 0;
    }
    else
    {
        set[root_q] = set[root_p];
        size[root_p] += size[root_q];
        size[root_q] = 0;
    }
}

int disjoint_set_union :: get_root(int p)
{
    while(p != set[p])
    {
        set[p] = set[set[p]];
        p = set[p];
    }
    return p;
}

int* disjoint_set_union :: get_size()
{
    return size;
}

int main()
{
    int N, M; // placeholder for the number of nodes and the number of edges
    cin >> N >> M;
    
    disjoint_set_union dsu(N);
    
    while(M-- > 0)
    {
        int p, q;
        vector<int> ans;
        cin >> p >> q;
        dsu.make_union(p, q);
        int* cc = dsu.get_size();
        printAns(cc, N + 1);
        cout << endl;
    }
    return 0;
}

void printAns(int* size, int n)
{
    vector<int> ans;
    for(int i = 1; i < n; i++) ans.push_back(size[i]);
    sort(ans.begin(), ans.end());
    
    for(int it = 1; it < n; ++it) {
        if(ans[it] > 0 && ans[it] < 1001) {
            cout << ans[it] << " ";
        }
    }
}
