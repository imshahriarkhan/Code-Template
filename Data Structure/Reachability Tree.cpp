//Problem Name : APIO20 Swap
//Link : https://oj.uz/problem/view/APIO20_swap
#include "swap.h"
#include<bits/stdc++.h>
using namespace std ;
 
const int LG = 30 , INF = 1e9 + 5 ;
 
struct query
{
    int u = 0 , v = 0 , w = 0 ;
};
 
bool cmp(query &a , query &b)
{
    return a.w < b.w ;
}
 
struct reachability_tree
{
    int cur = 0 , timer = 0 ;
    vector<vector<int> > adj , up , dp ;
    vector<int> tin , tout , par , swp , cost , edg , deg ;
    void init(int n , int m)
    {
        int siz = n + m + 5 ;
        adj = vector<vector<int> > (siz) ;
        up = vector<vector<int> > (siz , vector<int>(LG+1,0)) ;
        dp = vector<vector<int> > (siz , vector<int>(LG+1,0)) ;
        tin = vector<int> (siz , 0) ;
        tout = vector<int> (siz , 0) ;
        par = vector<int> (siz , 0) ;
        cost = vector<int> (siz , INF) ;
        swp = vector<int> (siz , 0) ;
        edg = vector<int> (siz , 0) ;
        deg = vector<int> (siz , 0) ;
        for(int i = 1 ; i < siz ; ++i)
        {
            par[i] = i ;
        }
        cur = n + 1 ;
    }
    int find_root(int p)
    {
        if(par[p]==p) return p ;
        return par[p] = find_root(par[p]) ;
    }
    void union_edge(int u , int v , int cst)
    {
        ++deg[u] , ++deg[v] ;
        if((deg[u]>=3) || (deg[v]>=3)) swp[cur] = 1 ;
        int root_u = find_root(u) , root_v = find_root(v) ;
 
        swp[cur] |= (swp[root_u]|swp[root_v]) ;
 
        adj[cur].push_back(root_u) ;
 
        if(root_u!=root_v) adj[cur].push_back(root_v) ;
        else swp[cur] = 1 ;
 
        par[root_u] = cur , par[root_v] = cur ;
 
        edg[cur] = cst ;
 
        ++cur ;
 
    }
 
    void dfs(int s , int p)
    {
        dp[s][0] = p , up[s][0] = max(swp[s],swp[p]) , tin[s] = ++timer ;
        for(int i = 1 ; i < LG ; ++i)
        {
            up[s][i] = max(up[s][i-1] , up[dp[s][i-1]][i-1]) ;
            dp[s][i] = dp[dp[s][i-1]][i-1] ;
        }
        for(int t : adj[s])
        {
            if(t==p) continue ;
            dfs(t,s) ;
        }
        tout[s] = ++timer ;
    }
 
    int is_ancestor(int u , int v)
    {
        return ((tin[u]<=tin[v]) && (tout[u]>=tout[v])) ;
    }
 
    int find_ancestor(int u , int v)
    {
        if(is_ancestor(u,v)) return u ;
        if(is_ancestor(v,u)) return v ;
        for(int i = LG - 1 ; i >= 0 ; --i)
        {
            if(!is_ancestor(dp[u][i],v))
            {
                u = dp[u][i] ;
            }
        }
        return dp[u][0] ;
    }
 
    int find_nearest(int u)
    {
        if(swp[u]) return edg[u] ;
        for(int i = LG - 1 ; i >= 0 ; --i)
        {
            if(!up[u][i])
            {
                u = dp[u][i] ;
            }
        }
        if(!swp[dp[u][0]]) return -1 ;
        return edg[dp[u][0]] ;
    }
 
    void process()
    {
        int root_1 = find_root(1) ;
        dfs(root_1,root_1) ;
    }
 
    int query(int x , int y)
    {
        ++x , ++y ;
        int lca = find_ancestor(x,y) ;
        int ret = find_nearest(lca) ;
        if(ret==INF) ret = -1 ;
        return ret ;
    }
} R ;
 
void init(int N, int M, vector<int> U, vector<int> V, vector<int> W)
{
    R.init(N,M) ;
    vector<query> v ;
    for(int i = 0 ; i < M ; ++i)
    {
        v.push_back({U[i]+1,V[i]+1,W[i]}) ;
    }
    sort(v.begin(),v.end(),cmp) ;
    for(query q : v)
    {
        R.union_edge(q.u,q.v,q.w) ;
    }
    R.process() ;
}
 
int getMinimumFuelCapacity(int X, int Y)
{
    return R.query(X,Y) ;
}
