#include<bits/stdc++.h>
using namespace std ;

struct node
{
    int to = 0 , weight = 0 ;
};

struct scc
{
    //trans is the reverse graph of adj
    //color starts from 1
    //vals is the values of the nodes
    vector<vector<node> > adj , trans , cadj ;
    vector<int> color , vis , cvis , total ;
    stack<int> order , corder ;
    int n , m , idx = 0 ;
    scc(int _n , int _m , vector<vector<node> > &_adj , vector<int> &vals)
    {
        n = _n , m = _m ;
        color = vector<int> (n+5 , 0) ;
        vis = vector<int> (n+5 , 0) ;
        total = vals ;
        adj = _adj ;
        trans.resize(n+5) ;
    }
    void dfs(int u)     //order of the original graph
    {
        vis[u] = 1 ;
        for(node v : adj[u])
        {
            if(vis[v.to]) continue ;
            dfs(v.to) ;
        }
        order.push(u) ;
    }
    void dfs2(int u)
    {
        color[u] = idx ;
        for(node v : trans[u])
        {
            if(color[v.to]) continue ;
            dfs2(v.to) ;
        }
    }
    void dfs3(int u)    //order of the compressed graph
    {
        cvis[u] = 1 ;
        for(node v : cadj[u])
        {
            if(cvis[v.to]) continue ;
            dfs3(v.to) ;
        }
        corder.push(u) ;
    }
    void solve()
    {
        for(int i = 1 ; i <= n ; ++i)
        {
            if(!vis[i]) dfs(i) ;
        }
        for(int u = 1 ; u <= n ; ++u)
        {
            for(node v : adj[u])
            {
                trans[v.to].push_back({u,0}) ;
            }
        }
        while(!order.empty())
        {
            int u = order.top() ;
            order.pop() ;
            if(color[u]) continue ;
            ++idx , dfs2(u) ;
        }
    }
    void compress()
    {
        cvis = vector<int> (n+5 , 0) ;
        cadj.resize(n+5) ;
        for(int u = 1 ; u <= n ; ++u)
        {
            for(node v : adj[u])
            {
                if(color[u]!=color[v.to])
                {
                    cadj[color[u]].push_back({color[v.to],v.weight}) ;
                }
                else total[color[u]] += v.weight ;
            }
        }
    }
};
