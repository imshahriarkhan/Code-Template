#include<bits/stdc++.h>
using namespace std ;

const long long INF = 1e18 + 5 ;

const int MX = 505 ;

long long dp[MX][MX] ;

int main()
{
    int n , m , q ;
    scanf("%d%d%d",&n,&m,&q) ;
    for(int i = 0 ; i <= n ; ++i)
    {
        for(int j = 0 ; j <= n ; ++j)
        {
            dp[i][j] = INF ;
        }
        dp[i][i] = 0 ;
    }
    while(m--)
    {
        int a , b ;
        long long c ;
        scanf("%d%d%lld",&a,&b,&c) ;
        dp[a][b] = min(dp[a][b],c) ;
        dp[b][a] = min(dp[b][a],c) ;
    }
    for(int k = 0 ; k <= n ; ++k)
    {
        for(int i = 0 ; i <= n ; ++i)
        {
            if(dp[i][k]==INF) continue ;
            for(int j = 0 ; j <= n ; ++j)
            {
                if(dp[k][j]==INF) continue ;
                dp[i][j] = min(dp[i][j],dp[i][k] + dp[k][j]) ;
            }
        }
    }
    while(q--)
    {
        int a , b ;
        scanf("%d%d",&a,&b) ;
        if(dp[a][b]==INF) puts("-1") ;
        else printf("%lld\n",dp[a][b]) ;
    }
    return 0 ;
}
