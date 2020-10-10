#include<bits/stdc++.h>
using namespace std ;

const int maxn = 1e5 ;

int sz[maxn] , cnt[maxn] , color[maxn] ;

vector<int> adj[maxn] , vec[maxn] ;

void dfs_size(int v , int p)
{
    sz[v] = 1 ;
    for(auto u : adj[v])
    {
        if(u!=p)
        {
            dfs_size(u,v) ;
            sz[v] += sz[u] ;
        }
    }
}

void dfs(int v , int p , int keep)
{
    int mx = -1 , bigChild = -1 ;
    for(auto u : adj[v])
    {
        if(u != p && mx < sz[u])
        {
            mx = sz[u] , bigChild = u ;
        }
    }
    for(auto u : adj[v])
    {
        if(u != p && u != bigChild)
        {
            dfs(u,v,0) ;
        }
    }
    if(bigChild != -1)
    {
        dfs(bigChild,v,1) ;
        swap(vec[v] , vec[bigChild]) ;
    }
    vec[v].push_back(v) ;
    ++cnt[color[v]] ;
    for(auto u : adj[v])
    {
        if(u != p && u != bigChild)
        {
            for(auto x : vec[u])
            {
                ++cnt[color[x]] ;
                vec[v].push_back(x) ;
            }
        }
    }
    if(!keep)
    {
        for(auto u : vec[v])
        {
            --cnt[color[u]] ;
        }
    }
}
