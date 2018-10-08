//
//  teachers_dilemma.cpp
//  hackerearth_practice_solution
//
//  Created by Vivek Singh on 07/10/18.
//  Copyright © 2018 Vivek Singh. All rights reserved.
//
// https://www.hackerearth.com/practice/data-structures/disjoint-data-strutures/basics-of-disjoint-data-structures/practice-problems/algorithm/teachers-dilemma-3/

#include <iostream>
#include <cmath>
using namespace std;

const long MODULO = 1000000007;
class teachers_dilemma
{
    int nodes, *friends, *ranks;
public:
    teachers_dilemma(int nodes)
    {
        this->nodes = nodes;
        friends = (int*) malloc((this->nodes + 1) * sizeof(int));
        ranks   = (int*) malloc((this->nodes + 1) * sizeof(int));
        
        for(int i = 1; i < nodes + 1; ++i)
        {
            friends[i] = i; ranks[i] = 1;
        }
    }
    ~teachers_dilemma() { delete friends; delete ranks; }
    void make_union(int a, int b);
    int  find_root (int a);
    int* get_rank();
};

void teachers_dilemma :: make_union(int a, int b)
{
    int a_root = find_root(a), b_root = find_root(b);
    if(a_root == b_root) return;
    
    if(ranks[a_root] < ranks[b_root])
    {
        friends[a_root] = friends[b_root];
        ranks[b_root] += ranks[a_root];
        ranks[a_root] = 0;
    }
    else
    {
        friends[b_root] = friends[a_root];
        ranks[a_root] += ranks[b_root];
        ranks[b_root] = 0;
    }
}

int teachers_dilemma :: find_root(int a)
{
    while(a != friends[a])
    {
        friends[a] = friends[friends[a]];
        a = friends[a];
    }
    return a;
}

int* teachers_dilemma :: get_rank()
{
    return ranks;
}

int main()
{
    int N, M;
    cin >> N >> M;
    teachers_dilemma td(N);
    
    while(M-- > 0)
    {
        int u, v;
        cin >> u >> v;
        
        td.make_union(u, v);
    }
    int* ranks = td.get_rank();
    
    long long ans = 1l;
    for(int i = 1; i < N + 1; i++)
    {
        if(ranks[i] != 0)
        {
            ans *= ranks[i];
            ans %= MODULO;
        }
    }
    cout << ans << endl;
    return 0;
}
