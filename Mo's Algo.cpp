#include<bits/stdc++.h>
using namespace std ;

const int mx = 1e5 + 5 ;

int block , ans[mx] ;

unordered_map<int,int> mp ;

struct query
{
    int l , r , id ;
};

bool compare(query x , query y)
{
    if(x.l/block != y.l/block) return x.l/block < y.l/block ;
    return x.r<y.r ;
}

void result(int a[] , query q[] , int n , int m)
{
    block = (int)sqrt(n) ;
    sort(q,q+m,compare) ;

    int curl = 0 , curr = 0 ;

    int cursum = 0 ;

    for(int i = 0 ; i < m ; ++i)
    {
        int l = q[i].l , r = q[i].r ;
        while(curl < l)
        {
            if(mp[a[curl]]==a[curl]) --cursum ;
            --mp[a[curl]] ;
            if(mp[a[curl]]==a[curl]) ++cursum ;
            ++curl ;
        }
        while(curl > l)
        {
            --curl ;
            if(mp[a[curl]]==a[curl]) --cursum ;
            ++mp[a[curl]] ;
            if(mp[a[curl]]==a[curl]) ++cursum ;
        }
        while(curr<=r)
        {
            if(mp[a[curr]]==a[curr]) --cursum ;
            ++mp[a[curr]] ;
            if(mp[a[curr]]==a[curr]) ++cursum ;
            ++curr ;
        }
        while(curr>(r+1))
        {
            --curr ;
            if(mp[a[curr]]==a[curr]) --cursum ;
            --mp[a[curr]] ;
            if(mp[a[curr]]==a[curr]) ++cursum ;
        }

        ans[q[i].id] = cursum ;
    }
}

int main()
{
    int n , m ;
    scanf("%d %d",&n,&m) ;
    int a[n] ;
    query v[m] ;
    for(int i = 0 ; i < n ; ++i) scanf("%d",&a[i]) ;
    for(int i = 0 ; i < m ; ++i)
    {
        int l , r ;
        scanf("%d %d",&l,&r) ;
        v[i].l = l-1 , v[i].r = r-1 , v[i].id = i ;
    }
    result(a,v,n,m) ;
    for(int i = 0 ; i < m ; ++i) printf("%d\n",ans[i]) ;
    return 0 ;
}
