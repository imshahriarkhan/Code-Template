//Problem Name : Xenia and Tree
//Problem Link : https://codeforces.com/contest/342/problem/E

#include<bits/stdc++.h>
using namespace std ;

const int MX = 1e5 + 5 , LG = 25 , INF = 1e9 + 5 ;

struct centroid_tree
{
    int n = 0 , timer = 0 ;
    vector<int> par , cost , sub , centroid , tin , tout , depth ;
    vector<vector<int> > adj , up ;
    void init(int N , vector<int> f[])
    {
        n = N ;
        par = vector<int> (N+2,0) ;
        cost = vector<int> (N+2,INF) ;
        sub = vector<int> (N+2,0) ;
        adj = vector<vector<int> > (N+2) ;
        centroid = vector<int> (N+2,0) ;
        tin = vector<int> (N+2,0) ;
        tout = vector<int> (N+2,0) ;
        depth = vector<int> (N+2,0) ;
        up = vector<vector<int> > (N+2,vector<int>(LG+1,0)) ;
        for(int i = 1 ; i <= N ; ++i)
        {
            for(int j : f[i])
            {
                adj[i].push_back(j) ;
            }
        }
        build_tree(1,0) ;
        dfs2(1,1) ;
    }
    void dfs(int s , int p)
    {
        sub[s] = 1 ;
        for(int t : adj[s])
        {
            if(t==p) continue ;
            if(centroid[t]) continue ;
            dfs(t,s) ;
            sub[s] += sub[t] ;
        }
    }
    int find_centroid(int s , int p , int x)
    {
        for(int t : adj[s])
        {
            if(t==p) continue ;
            if(centroid[t]) continue ;
            if(sub[t]>(x/2)) return find_centroid(t,s,x) ;
        }
        return s ;
    }
    void build_tree(int s , int p)
    {
        dfs(s,p) ;
        int C = find_centroid(s,p,sub[s]) ;
        centroid[C] = 1 , par[C] = p ;
        for(int t : adj[C])
        {
            if(centroid[t]) continue ;
            build_tree(t,C) ;
        }
    }
    void dfs2(int s , int p)
    {
        up[s][0] = p , tin[s] = ++timer , depth[s] = depth[p] + 1 ;
        for(int i = 1 ; i < LG ; ++i)
        {
            up[s][i] = up[up[s][i-1]][i-1] ;
        }
        for(int t : adj[s])
        {
            if(t==p) continue ;
            dfs2(t,s) ;
        }
        tout[s] = ++timer ;
    }
    int is_ancestor(int u , int v)
    {
        return ((tin[u]<=tin[v]) && (tout[u]>=tout[v])) ;
    }
    int find_lca(int u , int v)
    {
        if(is_ancestor(u,v)) return u ;
        if(is_ancestor(v,u)) return v ;
        for(int i = LG - 1 ; i >= 0 ; --i)
        {
            if(!is_ancestor(up[u][i],v))
            {
                u = up[u][i] ;
            }
        }
        return up[u][0] ;
    }
    int dist(int u , int v)
    {
        int lca = find_lca(u,v) ;
        return depth[u] + depth[v] - (2*depth[lca]) ;
    }
    void update(int u)
    {
        int org = u ;
        while(u)
        {
            cost[u] = min(cost[u],dist(org,u)) ;
            u = par[u] ;
        }
    }
    int query(int u)
    {
        int ret = INF , org = u ;
        while(u)
        {
            ret = min(ret,cost[u] + dist(org,u)) ;
            u = par[u] ;
        }
        return ret ;
    }
};

int main()
{
    int n , m ;
    scanf("%d%d",&n,&m) ;
    vector<int> adj[MX] ;
    for(int i = 1 ; i < n ; ++i)
    {
        int a , b ;
        scanf("%d%d",&a,&b) ;
        adj[a].push_back(b) ;
        adj[b].push_back(a) ;
    }
    centroid_tree C ;
    C.init(n,adj) ;
    C.update(1) ;
    while(m--)
    {
        int t , v ;
        scanf("%d%d",&t,&v) ;
        if(t==1) C.update(v) ;
        else printf("%d\n",C.query(v)) ;
    }
    return 0 ;
}
