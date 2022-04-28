//Problem Name : PSEGTREE - Make Versions in Segment Tree
//Link : https://www.spoj.com/problems/PSEGTREE/

#include<bits/stdc++.h>
using namespace std ;

struct Node
{
    int left = 0 , right = 0 ;
    long long val = 0 ;
};

struct psegtree
{
    int sz = 0 , cnt = 0 ;
    vector<Node> T ;
    vector<int> root ;
    void init(int n , int m , long long a[])
    {
        //as n <= 1e5, I have used 100*n...
        T = vector<Node> (100*n + 100) ;
        root = vector<int> (m + 10 , 0) ;
        root[0] = build(a,++sz,1,n) ;
    }
    int build(long long a[] , int node , int low , int high)
    {
        if(low==high)
        {
            T[node].val = a[low] ;
            return node ;
        }
        int mid = (low+high)>>1 ;
        T[node].left = build(a,++sz,low,mid) ;
        T[node].right = build(a,++sz,mid+1,high) ;
        T[node].val = (T[T[node].left].val+T[T[node].right].val) ;
        return node ;
    }
    int update_(int node , int low , int high , int idx , long long val)
    {
        if(low==high)
        {
            ++sz ;
            T[sz].val = T[node].val + val ;
            return sz ;
        }
        int mid = (low+high)>>1 , cur = ++sz ;
        if(idx<=mid) T[cur].left = update_(T[node].left,low,mid,idx,val) , T[cur].right = T[node].right ;
        else T[cur].left = T[node].left , T[cur].right = update_(T[node].right,mid+1,high,idx,val) ;
        T[cur].val = (T[T[cur].left].val+T[T[cur].right].val) ;
        return cur ;
    }
    void update(int f , int low , int high , int idx , long long val)
    {
        ++cnt ;
        root[cnt] = update_(root[f],low,high,idx,val) ;
    }
    long long query_(int node , int low , int high , int l , int r)
    {
        if((r<low) || (l>high)) return 0 ;
        if((l<=low) && (high<=r))
        {
            return T[node].val ;
        }
        int mid = (low+high)>>1 ;
        return (query_(T[node].left,low,mid,l,r)+query_(T[node].right,mid+1,high,l,r)) ;
    }
    long long query(int x , int low , int high , int l , int r)
    {
        return query_(root[x],low,high,l,r) ;
    }
};

int main()
{
    int n ;
    scanf("%d",&n) ;
    long long a[n+2] ;
    for(int i = 1 ; i <= n ; ++i)
    {
        scanf("%lld",&a[i]) ;
    }
    int q ;
    scanf("%d",&q) ;
    psegtree p ;
    p.init(n,q,a) ;
    for(int i = 1 ; i <= q ; ++i)
    {
        int type ;
        scanf("%d",&type) ;
        if(type==1)
        {
            int f , idx ;
            long long val ;
            scanf("%d%d%lld",&f,&idx,&val) ;
            p.update(f,1,n,idx,val) ;
        }
        else
        {
            int x , l , r ;
            scanf("%d%d%d",&x,&l,&r) ;
            printf("%lld\n",p.query(x,1,n,l,r)) ;
        }
    }
    return 0 ;
}
