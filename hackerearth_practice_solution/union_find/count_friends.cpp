//
//  count_friends.cpp
//  hackerearth_practice_solution
//
//  Created by Vivek Singh on 07/10/18.
//  Copyright © 2018 Vivek Singh. All rights reserved.
//
// https://www.hackerearth.com/practice/data-structures/disjoint-data-strutures/basics-of-disjoint-data-structures/practice-problems/algorithm/count-friends/

#include <iostream>
using namespace std;

class count_friends
{
    int n, *relationship, *rank;
public:
    count_friends(int friends)
    {
        n = friends;
        relationship = (int*) malloc((n + 1) * sizeof(int));
        rank  = (int*) malloc((n + 1) * sizeof(int));
        for(int i = 1; i < n + 1; i++)
        {
            relationship[i] = i;
            rank[i] = 1;
        }
    }
    ~count_friends() { delete relationship; delete rank; }
    void build_relation(int a, int b);
    int find_relation(int a);
    void count_relation();
};

void count_friends :: build_relation(int a, int b)
{
    int root_a = find_relation(a), root_b = find_relation(b);
    if(root_a == root_b) return;
    
    if(rank[root_a] < rank[root_b])
    {
        relationship[root_a] = relationship[root_b];
        rank[root_b] += rank[root_a];
    }
    else
    {
        relationship[root_b] = relationship[root_a];
        rank[root_a] += rank[root_b];
    }
}

int count_friends :: find_relation(int a)
{
    while(a != relationship[a]) {
        relationship[a] = relationship[relationship[a]];
        a = relationship[a];
    }
    return a;
}

void count_friends :: count_relation()
{
    for(int i = 1; i < n + 1; i++)
    {
        int root_val = find_relation(i);
        cout << rank[root_val] - 1 << " ";
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    
    count_friends cf(n);
    
    while(m-- > 0) {
        int u, v;
        cin >> u >> v;
        cf.build_relation(u, v);
    }
    cf.count_relation();
    return 0;
}
