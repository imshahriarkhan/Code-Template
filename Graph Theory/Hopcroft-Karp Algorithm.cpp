#include<bits/stdc++.h>
using namespace std ;

//Copied From: Buet_HellBent

const int N = 1e6 + 100 ;

struct Hopcroft_Karp{
    const int INF = (1<<28) ;
    int match[N] , dist[N] , n , m ;
    vector<int> G[N] ;

    void init(int left , int right)
    {
        n = left , m = right ;
        for(int i = 0 ; i <= n + m + 1 ; ++i) G[i].clear() ;
    }

    void addEdge(int u , int v)
    {
        G[u].push_back(v+n) ;
    }

    bool bfs()
    {
        queue<int> Q ;
        for(int i = 1 ; i <= n ; ++i)
        {
            if(!match[i]) dist[i] = 0 , Q.push(i) ;
            else dist[i] = INF ;
        }
        dist[0] = INF ;
        while(!Q.empty())
        {
            int u = Q.front() ; Q.pop() ;
            if(u)
            {
                for(int v : G[u])
                {
                    if(dist[match[v]]==INF)
                    {
                        dist[match[v]] = dist[u] + 1 ;
                        Q.push(match[v]) ;
                    }
                }
            }
        }
        return (dist[0]!=INF) ;
    }

    bool dfs(int u)
    {
        if(!u) return 1 ;
        for(int v : G[u])
        {
            if(dist[match[v]] == dist[u] + 1)
            {
                if(dfs(match[v]))
                {
                    match[v] = u , match[u] = v ;
                    return true ;
                }
            }
        }
        dist[u] = INF ;
        return false ;
    }

    int hopcroft_karp()
    {
        memset(dist,0,sizeof dist) ;
        memset(match,0,sizeof match) ;
        int matching = 0 ;
        while(bfs())
        {
            for(int i = 1 ; i <= n ; ++i)
            {
                if(!match[i] && dfs(i))
                {
                    ++matching ;
                }
            }
        }
        return matching ;
    }
} H ;
