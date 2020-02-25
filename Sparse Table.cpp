#include<bits/stdc++.h>
using namespace std ;

const int maxn = 1e7 + 1 , K = 25 ;

int logx[maxn+1] , st[maxn][K] , N , a[maxn] ;

void precomplog()
{
    logx[1] = 0 ;
    for(int i = 2 ; i <= maxn ; ++i) logx[i] = logx[i/2] + 1 ;
}

void sparsetable()
{
    for(int i = 0 ; i < N ; ++i) st[i][0] = a[i] ;
    for(int j =1 ; j <= K ; ++j)
    {
        for(int i = 0 ; i + (1<<j) <= N ; ++i)
        {
            st[i][j] = min(st[i][j-1],st[i+(1<<(j-1))][j-1]) ;
        }
    }
}

int minquery(int l , int r)
{
    int j = logx[r-l+1] ;
    return min(st[l][j],st[r-(1<<j)+1][j]) ;
}

int main()
{

}
