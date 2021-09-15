#include<bits/stdc++.h>
#include "factories.h"
using namespace std ;
 
const int mx = 5e5 + 10 ;
const long long INF = 1e18 ;
 
vector<pair<int,long long> > edges[mx] ;
 
int n , sub[mx] , par[mx] , depth[mx] , vis[mx] ;
 
long long ans[mx] , dist[mx][20] ;
 
stack<int> st ;
 
void dfs(int x , int p , int d)
{
    sub[x] = 1 ;
    for(auto i : edges[x])
    {
        if(i.first == p) continue ;
        if(vis[i.first]) continue ;
        if(d) dist[i.first][d-1] = dist[x][d-1] + i.second ;
        dfs(i.first,x,d) ;
        sub[x] += sub[i.first] ;
    }
}
 
int find_centroid(int x , int p , int range)
{
    for(auto i : edges[x])
    {
        if(i.first==p) continue ;
        if(vis[i.first]) continue ;
        if(sub[i.first]>range)
        {
            return find_centroid(i.first,x,range) ;
        }
    }
    return x ;
}
 
void build(int x , int p , int d)
{
    dfs(x,-1,d) ;
    int c = find_centroid(x,-1,sub[x]/2) ;
    par[c] = p , vis[c] = 1 , depth[c] = d ;
    for(auto i : edges[c])
    {
        if(vis[i.first]) continue ;
        dist[i.first][d] = i.second ;
        build(i.first,c,d+1) ;
    }
    vis[c] = 0 ;
}
 
void update(int x)
{
    int cur = x ;
    while(cur)
    {
        ans[cur] = min(ans[cur],dist[x][depth[cur]]) ;
        st.push(cur) ;
        cur = par[cur] ;
    }
}
 
long long query(int x)
{
    long long res = ans[x] ;
    int cur = x ;
    while(cur)
    {
        res = min(res,ans[cur] + dist[x][depth[cur]]) ;
        cur = par[cur] ;
    }
    return res ;
}
 
void Init(int N , int A[] , int B[] , int D[])
{
    n = N ;
    for(int i = 0 ; i < (N-1) ; ++i)
    {
        edges[A[i] + 1].push_back({B[i]+1,D[i]}) ;
        edges[B[i] + 1].push_back({A[i]+1,D[i]}) ;
    }
    build(1,0,0) ;
    for(int i = 1 ; i <= N ; ++i) ans[i] = INF ;
}
 
long long Query(int S , int X[] , int T , int Y[])
{
    for(int i = 0 ; i < S ; ++i)
    {
        update(X[i] + 1) ;
    }
    long long res = INF ;
    for(int i = 0 ; i < T ; ++i)
    {
        res = min(res,query(Y[i] + 1)) ;
    }
    while(!st.empty())
    {
        ans[st.top()] = INF ;
        st.pop() ;
    }
    return res ;
}
