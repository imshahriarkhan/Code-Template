#include<bits/stdc++.h>
using namespace std ;

const int mx = 1e5 + 1 ;

int n , vis[mx] ;

vector<int> adj[mx] ;

stack<int> st ;

void dfs(int s)
{
    vis[s] = 1 ;
    for(int i = 0 ; i < adj[s].size() ; ++i)
    {
        if(!vis[adj[s][i]]) dfs(adj[s][i]) ;
    }
    st.push(s) ;
}

int main()
{
}
