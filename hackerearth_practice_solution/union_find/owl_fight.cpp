//
//  owl_fight.cpp
//  hackerearth_practice_solution
//
//  Created by Vivek Singh on 08/10/18.
//  Copyright © 2018 Vivek Singh. All rights reserved.
//
// https://www.hackerearth.com/practice/data-structures/disjoint-data-strutures/basics-of-disjoint-data-structures/practice-problems/algorithm/owl-fight/

#include <iostream>
using namespace std;

class owl_fight
{
    int connection, *tree;
public:
    owl_fight(int node)
    {
        this->connection = node;
        this->tree = (int*) malloc((this->connection + 1) * sizeof(int));
        for(int iter = 0; iter <= this->connection; ++iter) this->tree[iter] = iter;
    }
    ~owl_fight() { delete this->tree; }
    void make_connection(int u, int v);
    int find_root(int u);
    int* get_connections();
};

void owl_fight :: make_connection(int u, int v)
{
    int u_root = this->find_root(u), v_root = this->find_root(v);
    if(u_root < v_root)
    {
        this->tree[u_root] = v_root;
    }
    else
    {
        this->tree[v_root] = u_root;
    }
}

int owl_fight :: find_root(int u)
{
    while(u != this->tree[u])
    {
        this->tree[u] = this->tree[this->tree[u]];
        u = this->tree[u];
    }
    return u;
}

int* owl_fight :: get_connections()
{
    return this->tree;
}

int main()
{
    int N, M;
    cin >> N >> M;
    owl_fight of(N);
    
    while(M-- > 0)
    {
        int u, v;
        cin >> u >> v;
        of.make_connection(u, v);
    }
    int queries;
    cin >> queries;
    
    while(queries-- > 0)
    {
        int u, v;
        cin >> u >> v;
        
        int u_root = of.find_root(u), v_root = of.find_root(v);
        if(u_root == v_root) {
            cout << "TIE" << endl;
        } else {
            if(u_root < v_root) {
                cout << v << endl;
            } else {
                cout << u << endl;
            }
        }
    }
    return 0;
}
