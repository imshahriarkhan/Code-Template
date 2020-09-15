
#include<bits/stdc++.h>
using namespace std ;

struct shortest_path
{
    const int INF = 1e9 ;
    vector<vector<pair<int,int> > > adj ;

    shortest_path(int n , int start , vector<vector<pair<int,int> > > &arr , vector<int> &d , vector<int> &p)
    {
        adj = arr ;
        djikstra(n,start,d,p) ;
    }

    void djikstra(int n , int s , vector<int> &d , vector<int> &p)
    {
        d.assign(n,INF) ;
        p.assign(n,-1) ;
        d[s] = 0 ;
        using pii = pair<int,int> ;
        priority_queue<pii,vector<pii>, greater<pii> > q ;
        q.push({0,s}) ;
        while(!q.empty())
        {
            int v = q.top().second ;
            int d_v = q.top().first ;
            q.pop() ;
            if(d_v != d[v]) continue ;
            for(auto edge : adj[v])
            {
                int to = edge.first , len = edge.second ;

                if((d[v] + len) < d[to])
                {
                    d[to] = d[v] + len ;
                    p[to] = v ;
                    q.push({d[to],to}) ;
                }
            }
        }
    }
} ;
