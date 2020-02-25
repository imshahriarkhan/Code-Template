#include<bits/stdc++.h>
using namespace std ;

const int mx = 2e5 + 5 ;

vector<int> adj[mx] ;

int subtree[mx] , vis[mx] , n , half ;

void dfs(int s , int par)
{
    int siz = adj[s].size() ;
    subtree[s] = 1 ;
    for(int i = 0 ; i < siz ; ++i)
    {
        if(adj[s][i]!=par)
        {
            dfs(adj[s][i],s) ;
            subtree[s] += subtree[adj[s][i]] ;
        }
    }
}


int centroid(int s , int par , int n)
{
    int siz = adj[s].size() ;
    for(int i = 0 ; i < siz ; ++i)
    {
        if(adj[s][i]!=par)
        {
            if((subtree[adj[s][i]])>n) return centroid(adj[s][i],s,n) ;
        }
    }
    return s ;
}

void solve(int c)
{

}

void decomp(int s , int par)
{
    dfs(s,par) ;
    int c = centroid(s,par,subtree[s]/2) ;
    solve(c) , vis[c] = 1 ;
    int siz = adj[c].size() ;
    for(int i = 0 ; i < siz ; ++i)
    {
        if(!vis[adj[c][i]]) decomp(adj[c][i],c) ;
    }
}

int main()
{

}
