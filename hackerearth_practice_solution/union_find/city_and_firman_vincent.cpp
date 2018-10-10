//
//  city_and_firman_vincent.cpp
//  hackerearth_practice_solution
//
//  Created by Vivek Singh on 09/10/18.
//  Copyright © 2018 Vivek Singh. All rights reserved.
// https://www.hackerearth.com/practice/data-structures/disjoint-data-strutures/basics-of-disjoint-data-structures/practice-problems/algorithm/city-and-fireman-vincent/
//

#include <iostream>
using namespace std;

const int MODULO = 1000000007;

class city_and_fireman_vincent
{
    int cities, *connection, *size;
public:
    city_and_fireman_vincent(int node)
    {
        this->cities = node;
        this->connection = (int*) malloc((this->cities + 1) * sizeof(int));
        this->size = (int*) malloc((this->cities + 1) * sizeof(int));
        
        for(int iter = 1; iter <= this->cities; ++iter)
        {
            this->connection[iter] = iter;
            this->size[iter] = 1;
        }
    }
    ~city_and_fireman_vincent() { delete this->connection; delete this->size; }
    void make_connection(int costs[], int u, int v);
    int  find_connection(int u);
    int* get_connection();
    int* get_size();
};

void city_and_fireman_vincent :: make_connection(int costs[], int u, int v)
{
    int u_root = find_connection(u), v_root = find_connection(v);
    if(u_root == v_root) return;
    
    if(this->size[u_root] < this->size[v_root])
    {
        this->connection[u_root] = this->connection[v_root];
        this->size[v_root] += this->size[u_root];
    }
    else
    {
        this->connection[v_root] = this->connection[u_root];
        this->size[u_root] += this->size[v_root];
    }
}

int city_and_fireman_vincent :: find_connection(int u)
{
    while(u != this->connection[u])
    {
        this->connection[u] = this->connection[this->connection[u]];
        u = this->connection[u];
    }
    return u;
}

int* city_and_fireman_vincent :: get_connection()
{
    return this->connection;
}

int* city_and_fireman_vincent :: get_size()
{
    return this->size;
}

int main()
{
    int N;
    cin >> N;
    city_and_fireman_vincent cafv(N);
    
    int costs[N + 1];
    bool visited[N + 1];
    
    for(int iter = 1; iter <= N; ++iter) visited[iter] = false;
    for(int iter = 1; iter <= N; ++iter) cin >> costs[iter];
    
    int k;
    cin >> k;
    while(k-- > 0)
    {
        int u, v;
        cin >> u >> v;
        cafv.make_connection(costs, u, v);
    }
    
    long ans = 1l;
    for(int u = 1; u <= N; ++u)
    {
        int cnt = 1;
        if(!visited[u])
        {
            int u_root = cafv.find_connection(u);
            int u_cost = costs[u];
            for(int v = u + 1; v <= N; ++v)
            {
                if(!visited[v])
                {
                    int v_root = cafv.find_connection(v);
                    int v_cost = costs[v];
                    if(u_root == v_root)
                    {
                        if(v_cost < u_cost)
                        {
                            cnt = 1;
                            u_cost = v_cost;
                        }
                        else if(u_cost == v_cost)
                        {
                            cnt++;
                        }
                        visited[v] = true;
                    }
                }
            }
            visited[u] = true;
            ans *= cnt;
            ans %= MODULO;
        }
    }
    cout << ans << endl;
    return 0;
}
