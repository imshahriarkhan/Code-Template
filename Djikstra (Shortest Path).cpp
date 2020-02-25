#include<bits/stdc++.h>
using namespace std ;

#define siz 100000 ;

vector<pair < int , int > > v[siz] ;

int dist[siz] , vis[siz] ;

void djikstra()
{
    dist[1] = 0 ;
    multiset<pair< int , int> > q ;
    s.insert({0,1}) ;
    while(!s.empty())
    {
        pair<int,int> p = *s.begin() ;
        s.erase(s.begin()) ;
        int x = p.s , wei = p.f ;
        if(vis[x]) continue ;
        vis[x] = 1 ;
        for(int i = 0 ; i < v[x].size() ; ++i)
        {
            int e = v[x][i].f , w = v[x][i].s ;
            if((dist[x] + w)<dist[e])
            {
                dist[e] = dist[x] + w ;
                s.insert({dist[e],e}) ;
            }
        }
    }
}

int main()
{

}
