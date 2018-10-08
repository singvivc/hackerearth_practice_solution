//
//  city_and_flood.cpp
//  hackerearth_practice_solution
//
//  Created by Vivek Singh on 08/10/18.
//  Copyright © 2018 Vivek Singh. All rights reserved.
//
//  https://www.hackerearth.com/practice/data-structures/disjoint-data-strutures/basics-of-disjoint-data-structures/practice-problems/algorithm/city-and-flood-1/
//

#include <iostream>
using namespace std;

class city_and_flood
{
    int cities, *empires;
public:
    city_and_flood(int nodes)
    {
        this->cities = nodes;
        this->empires = (int*) malloc((this->cities + 1) * sizeof(int));
        for(int iter = 1; iter <= this->cities; ++iter) this->empires[iter] = iter;
    }
    ~city_and_flood() { delete this->empires; }
    void make_connection(int u, int v);
    int  find_connection(int u);
    int  existed_empire();
};

void city_and_flood :: make_connection(int u, int v)
{
    int u_root = this->find_connection(u), v_root = this->find_connection(v);
    this->empires[u_root] = v_root;
}

int city_and_flood :: find_connection(int u)
{
    while(u != this->empires[u])
    {
        this->empires[u] = this->empires[this->empires[u]];
        u = this->empires[u];
    }
    return u;
}

int city_and_flood :: existed_empire()
{
    int ans = 0;
    for(int iter = 1; iter <= this->cities; ++iter)
    {
        if(iter == this->find_connection(iter))
        {
            ans++;
        }
    }
    return ans;
}

int main()
{
    int N, K;
    cin >> N;
    city_and_flood caf(N);
    
    cin >> K;
    
    while(K-- > 0)
    {
        int u, v;
        cin >> u >> v;
        caf.make_connection(u, v);
    }
    cout << caf.existed_empire() << endl;
    return 0;
}
