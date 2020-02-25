#include<bits/stdc++.h>
using namespace std ;

#define pii pair<int,int>

const int mx = 1e6 , INF = 1e9 ;

vector<pii> adj[mx] ;

int vis[mx] , d[mx] , n ;

void djikstra(int s)
{
    memset(d,INF,n) ;
    memset(vis,0,n) ;
    priority_queue<pii,vector<pii>,greater<pii> > pq ;
    pq.push(s) ;
    while(!pq.empty())
    {
        int from = pq.top().second ;
        pq.pop() ;
        if(vis[from]) continue ;
        vis[from] = 1 ;
        for(auto edge : adj)
        {
            int to = edge.first , val = edge.second ;
            if((d[from]+val)<d[to])
            {
                d[to] = d[from] + val ;
                pq.push({d[to],to}) ;
            }
        }
    }
}
