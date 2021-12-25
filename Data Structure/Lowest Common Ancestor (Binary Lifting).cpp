#include<bits/stdc++.h>
using namespace std ;

const int MX = 1e5 + 5 , LG = 30 ;

struct triple
{
    int type , x , y ;
};

int up[MX][LG] , dp[MX][LG] , st[MX] , ed[MX] , timer ;

vector<int> adj[MX] ;

vector<triple> query ;

pair<int,int> v[MX] ;

void precomp(int s , int p)
{
    st[s] = ++timer ;
    for(int t : adj[s])
    {
        if(t==p) continue ;
        precomp(t,s) ;
    }
    ed[s] = ++timer ;
}

bool is_ancestor(int u , int v)
{
    return ((st[u]<=st[v]) && (ed[u]>=ed[v])) ;
}

int find_ancestor(int u , int idx)
{
    for(int i = LG - 1 ; i >= 0 ; --i)
    {
        if(is_ancestor(up[u][i],u) && (dp[u][i]<idx))
        {
            u = up[u][i] ;
        }
    }
    return u ;
}

int main()
{
    int n , m ;
    scanf("%d%d",&n,&m) ;
    for(int i = 1 ; i <= m ; ++i)
    {
        int type ;
        scanf("%d",&type) ;
        if(type==1)
        {
            int x , y ;
            scanf("%d%d",&x,&y) ;
            adj[y].push_back(x) ;
            up[x][0] = y ;
            dp[x][0] = i ;
            query.push_back({1,x,y}) ;
        }
        else if(type==2)
        {
            int x ;
            scanf("%d",&x) ;
            query.push_back({2,x,0}) ;
        }
        else
        {
            int x , y ;
            scanf("%d%d",&x,&y) ;
            query.push_back({3,x,y}) ;
        }
    }
    for(int i = 1 ; i <= n ; ++i)
    {
        if(!up[i][0]) precomp(i,0) ;
    }
    for(int j = 1 ; j < LG ; ++j)
    {
        for(int i = 1 ; i <= n ; ++i)
        {
            up[i][j] = up[up[i][j-1]][j-1] ;
            dp[i][j] = max(dp[i][j-1],dp[up[i][j-1]][j-1]) ;
        }
    }
    int siz = query.size() , cur = 0  ;
    for(int i = 0 ; i < siz ; ++i)
    {
        int type = query[i].type , x = query[i].x , y = query[i].y ;
        if(type==2)
        {
            ++cur ;
            v[cur] = {find_ancestor(x,i+1),x} ;
        }
        else if(type==3)
        {
            if(is_ancestor(v[y].first,x) && is_ancestor(x,v[y].second)) puts("YES") ;
            else puts("NO") ;
        }
    }
    return 0 ;
}
