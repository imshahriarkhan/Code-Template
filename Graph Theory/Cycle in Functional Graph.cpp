CSES1160: Planet Queries II: https://cses.fi/problemset/task/1160/

#include<bits/stdc++.h>
using namespace std ;

const int MX = 2e5 + 5 , LG = 30 ;

vector<int> child[MX] ;

int t[MX] , in_cycle[MX] , siz[MX] , depth[MX] , level[MX] , nex[MX] , par[MX][LG] , vis[MX] , col ;

void dfs(int s , int val)
{
    nex[s] = val , vis[s] = 1 ;
    for(int t : child[s])
    {
        if(in_cycle[t]) continue ;
        level[t] = level[s] + 1 ;
        dfs(t,val) ;
    }
}

void cycle(int s)
{
    int a = t[s] , b = t[t[s]] ;
    while(a!=b)
    {
        a = t[a] ;
        b = t[t[b]] ;
    }
    ++col ;
    depth[a] = 1 , vis[a] = 1 , in_cycle[a] = col , siz[col] = 1 ;
    while(a!=t[b])
    {
        vis[t[b]] = 1 , in_cycle[t[b]] = col , depth[t[b]] = depth[b] + 1 , ++siz[col] ;
        b = t[b] ;
    }
    dfs(a,a) ;
    b = a ;
    while(a!=t[b])
    {
        dfs(t[b],t[b]) ;
        b = t[b] ;
    }
}

int find_ans(int u , int v)
{
    int dist = level[u] - level[v] ;
    for(int i = LG - 1 ; i >= 0 ; --i)
    {
        if(!par[u][i]) continue ;
        if(level[par[u][i]]>=level[v])
        {
            u = par[u][i] ;
        }
    }
    if(u!=v) return -1 ;
    else return dist ;
}

int main()
{
    int n , q ;
    scanf("%d%d",&n,&q) ;
    for(int i = 1 ; i <= n ; ++i)
    {
        scanf("%d",&t[i]) ;
        child[t[i]].push_back(i) ;
        nex[i] = i , par[i][0] = t[i] ;
    }
    for(int i = 1 ; i <= n ; ++i)
    {
        if(vis[i]) continue ;
        cycle(i) ;
    }
    for(int j = 1 ; j < LG ; ++j)
    {
        for(int i = 1 ; i <= n ; ++i)
        {
            par[i][j] = par[par[i][j-1]][j-1] ;
        }
    }
    while(q--)
    {
        int u , v ;
        scanf("%d%d",&u,&v) ;
        if((in_cycle[u]==in_cycle[v]) && (in_cycle[u]))
        {
            int dist = 0 ;
            if(depth[v]>=depth[u]) dist = depth[v] - depth[u] ;
            else dist = siz[in_cycle[u]] - depth[u] + depth[v] ;
            printf("%d\n",dist) ;
        }
        else if((in_cycle[nex[u]]==in_cycle[v]) && (in_cycle[v]))
        {
            int dist = 0 ;
            if(depth[v]>=depth[nex[u]]) dist = depth[v] - depth[nex[u]] ;
            else dist = siz[in_cycle[v]] - depth[nex[u]] + depth[v] ;
            printf("%d\n",dist+level[u]) ;
        }
        else if((in_cycle[nex[u]]==in_cycle[nex[v]]) && (in_cycle[nex[u]]))
        {
            printf("%d\n",find_ans(u,v)) ;
        }
        else puts("-1") ;
    }
    return 0 ;
}
