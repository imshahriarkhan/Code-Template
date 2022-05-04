//Problem Name : Meteors
//Link : https://oj.uz/problem/view/POI11_met
//Circular 1-based BIT

#include<bits/stdc++.h>
using namespace std ;

const int MX = 3e5 + 5 ;

struct query
{
    int l = 0 , r = 0 ;
    long long val = 0 ;
};

struct BIT
{
    int n ;
    vector<long long> bit ;
    void init(int _n)
    {
        n = _n ;
        bit = vector<long long>(n+5,0) ;
    }
    int low_bit(int idx)
    {
        return idx&(-idx) ;
    }
    void add(int idx , long long val)
    {
        for(; idx <= n ; idx += low_bit(idx))
        {
            bit[idx] += val ;
        }
    }
    void update(int l , int r , long long val)
    {
        add(r + 1 , -val) , add(l , val) ;
        if(l>r) add(1,val) , add(n+1,-val) ;
    }
    long long query(int idx)
    {
        long long ret = 0 ;
        for(; idx > 0 ; idx -= low_bit(idx))
        {
            ret += bit[idx] ;
        }
        return ret ;
    }
} B ;

int n , m , k , o[MX] , ans[MX] ;

long long p[MX] ;

vector<int> owner[MX] ;

vector<query> q ;

void palbs(int low , int high , vector<int> &vals)
{
    if(low>high) return ;
    if(vals.empty()) return ;
    int mid = (low+high)>>1 ;
    for(int i = low ; i <= mid ; ++i)
    {
        B.update(q[i].l,q[i].r,q[i].val) ;
    }
    vector<int> ok , not_ok ;
    for(int c : vals)
    {
        unsigned long long sum = 0 ;
        for(int land : owner[c])
        {
           sum += B.query(land) ;
        }
        if(sum>=p[c]) ans[c] = mid , ok.push_back(c) ;
        else
        {
            p[c] -= sum ;
            not_ok.push_back(c) ;
        }
    }
    for(int i = low ; i <= mid ; ++i)
    {
        B.update(q[i].l,q[i].r,-q[i].val) ;
    }
    if(low==high) return ;
    palbs(low,mid,ok) ;
    palbs(mid+1,high,not_ok) ;
}

int main()
{
    vector<int> v ;
    scanf("%d%d",&n,&m) ;
    B.init(m+2) ;
    for(int i = 1 ; i <= m ; ++i)
    {
        scanf("%d",&o[i]) ;
        owner[o[i]].push_back(i) ;
    }
    for(int i = 1 ; i <= n ; ++i)
    {
        scanf("%lld",&p[i]) ;
        ans[i] = -1 ;
        v.push_back(i) ;
    }
    scanf("%d",&k) ;
    for(int i = 1 ; i <= k ; ++i)
    {
        int l , r ;
        long long a ;
        scanf("%d%d%lld",&l,&r,&a) ;
        q.push_back({l,r,a}) ;
    }
    palbs(0,k-1,v) ;
    for(int i = 1 ; i <= n ; ++i)
    {
        if(ans[i]>=0) printf("%d\n",ans[i]+1) ;
        else puts("NIE") ;
    }
    return 0 ;
}
