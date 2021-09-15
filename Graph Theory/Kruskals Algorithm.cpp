#include<bits/stdc++.h>
using namespace std ;

const int mx = 2e5 + 5 ;

int root[mx] , siz[mx] , n , m ;

long long ans ;

struct triplet
{
    int x , y ;
    long long w ;
};

bool comp(triplet &a , triplet &b)
{
    return a.w<b.w ;
}

vector<triplet> edges ;

int find_root(int p)
{
    if(root[p]==p) return p ;
    return root[p] = find_root(root[p]) ;
}

void add(int x , int y)
{
    int root_x = find_root(x) , root_y = find_root(y) ;
    if(siz[root_x]<siz[root_y]) swap(root_x,root_y) ;
    root[root_y] = root_x ;
    siz[root_x] += siz[root_y] ;
}

int main()
{
    scanf("%d%d",&n,&m) ;
    for(int i = 1 ; i <= n ; ++i) root[i] = i , siz[i] = 1 ;
    for(int i = 1 ; i <= m ; ++i)
    {
        int x , y , w ;
        scanf("%d%d%d",&x,&y,&w) ;
        edges.push_back({x,y,w}) ;
    }
    sort(edges.begin(),edges.end(),comp) ;
    for(int i = 0 ; i < m ; ++i)
    {
        triplet edge = edges[i] ;
        if(find_root(edge.x)==find_root(edge.y)) continue ;
        add(edge.x,edge.y) ;
        ans += edge.w ;
    }
    printf("%lld\n",ans) ;
    return 0 ;
}
