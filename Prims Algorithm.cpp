#include<bits/stdc++.h>
using namespace std ;

const int mx = 1e4 + 5 ;

#define pii pair<long long , int>

bool marked[mx] ;

vector<pii> adj[mx] ;

long long prime(int x)
{
    priority_queue<pii,vector<pii>,greater<pii> > q ;
    int y ;
    long long mincost = 0 ;
    pii p ;
    q.push({0,x}) ;
    while(!q.empty())
    {
        p = q.top() ;
        q.pop() ;
        x = p.second ;
        if(marked[x]) continue ;
        mincost += p.first ;
        marked[x] = true ;
        for(int i = 0 ; i < adj[x].size() ; ++i)
        {
            y = adj[x][i].second ;
            if(!marked[y]) q.push(adj[x][i]) ;
        }
    }
    return mincost ;
}

int main()
{

}
