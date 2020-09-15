#include<bits/stdc++.h>
using namespace std ;

struct LCA{
    vector<int> level , euler , first , logx ;
    vector<vector<int> > adj , st ;
    int cnt = 0 ;

    LCA(vector<vector<int> > &arr , int n)
    {
        level.resize(n+1) ;
        first.resize(n+1) ;
        logx.resize(3*n) ;
        adj = arr ;
        st = vector<vector<int> > (3*n,vector<int>(26,0)) ;
        dfs(1,0) ;
        precomplog(n) ;
        sparsetable(n) ;
    }

    void dfs(int s , int p)
    {
        level[s] = level[p] + 1 ;
        first[s] = cnt ;
        euler.push_back(s) ;
        ++cnt ;
        for(int t : adj[s])
        {
            if(t==p) continue ;
            dfs(t,s) ;
            euler.push_back(s) ;
            ++cnt ;
        }
    }

    void precomplog(int n)
    {
        logx[1] = 0 ;
        for(int i = 2 ; i < 3*n ; ++i) logx[i] = logx[i/2] + 1 ;
    }

    void sparsetable(int n)
    {
        int siz = euler.size() ;
        for(int i = 0 ; i < siz ; ++i) st[i][0] = euler[i] ;
        for(int j = 1 ; j <= 25 ; ++j)
        {
            for(int i = 0 ; i + (1<<j) < siz ; ++i)
            {
                int pp = level[st[i][j-1]] , qq = level[st[i+(1<<(j-1))][j-1]] ;
                if(pp<qq) st[i][j] = st[i][j-1] ;
                else st[i][j] = st[i+(1<<(j-1))][j-1] ;
            }
        }
    }

    int minquery(int l , int r)
    {
        int j = logx[r-l+1] ;
        if(level[st[l][j]]<level[st[r-(1<<j)+1][j]]) return st[l][j] ;
        else return st[r-(1<<j)+1][j] ;
    }

    int find_LCA(int u , int v)
    {
        return minquery(min(first[v],first[u]),max(first[u],first[v])) ;
    }
} ;
