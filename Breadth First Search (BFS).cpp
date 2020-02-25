#include<bits/stdc++.h>
using namespace std ;

const int mx = 1e5 + 1 ;

int n , s , vis[mx] ;

queue<int> q ;

vector<int> adj[mx] ;

void bfs(int s)
{
    int d[mx] , p[mx] ;
    q.push(s) ;
    vis[s] = 1 ;
    p[s] = -1 ;
    while(!q.empty())
    {
        int v = q.front() ;
        q.pop() ;
        for(int u : adj[v])
        {
            if(!vis[u])
            {
                vis[u] = 1 ;
                q.push(u) ;
                d[u] = d[v] + 1 ;
                p[u] = v ;
            }
        }
    }
}
