#include<bits/stdc++.h>
using namespace std ;

const int mx = 1e5 + 5 ;

int parent[mx] , siz[mx] , a[mx] ;

int find_set(int v)
{
    if(v==parent[v]) return v ;
    return parent[v] = find_set(parent[v]) ;
}

void make_set(int v)
{
    parent[v] = v ;
    siz[v] = 1 ;
}

void union_set(int a , int b)
{
    a = find_set(a) ;
    b = find_set(b) ;
    if(a!=b)
    {
        if(siz[a]<siz[b]) swap(a,b) ;
        parent[b] = a ;
        siz[a] += siz[b] ;
    }
}

int main()
{

}
