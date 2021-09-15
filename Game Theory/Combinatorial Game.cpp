#include<bits/stdc++.h>
using namespace std ;

int main()
{
    int n , k ;
    scanf("%d%d",&n,&k) ;
    int a[n] ;
    for(int i = 0 ; i < n ; ++i) scanf("%d",&a[i]) ;
    sort(a,a+n) ;
    int dp[k+1] = {0} ;
    for(int i = 1 ; i <= k ; ++i)
    {
        for(int j = 0 ; j < n ; ++j)
        {
            if(a[j]<=i && dp[i-a[j]]==0) dp[i] = 1 ;
        }
    }
    if(dp[k]) puts("First") ;
    else puts("Second") ;
}
