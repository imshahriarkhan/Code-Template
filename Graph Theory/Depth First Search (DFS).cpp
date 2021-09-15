#include<bits/stdc++.h>
using namespace std ;

const int mx = 1e5 + 1 ;

int n , visited[mx] ;

vector<int> adj[mx] ;

void dfs(int s)
{
    visited[s] = 1 ;
    for(int u:adj[s])
    {
        if(!visited[u]) dfs(u) ;
    }
}
