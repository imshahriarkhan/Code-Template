#include<bits/stdc++.h>
using namespace std ;

const long long MX = 2e7 + 5 ;

int vis[MX] , lpf[MX] ;

long long dp[MX] , mul[MX] , ans ;

vector<int> primes ;

void calc()
{
    int siz = 0 ;
    for(int i = 2 ; i < MX ; ++i)
    {
        if(!lpf[i])
        {
            lpf[i] = i , primes.push_back(i) , ++siz ;
        }
        for(int k = 0 ; k < siz ; ++k)
        {
            int j = primes[k] ;
            if(j>lpf[i]) break ;
            if((i*1LL*j)>=MX) break ;
            lpf[i*1LL*j] = j ;
        }
    }
}

void add(int num)
{
    vector<int> factors = {1} , prime_fact ;
    while(num>1)
    {
        prime_fact.push_back(lpf[num]) ;
        num /= lpf[num] ;
    }
    vis[1] = 1 ;
    for(int i : prime_fact)
    {
        vector<int> temp ;
        for(int j : factors)
        {
            if(!vis[i*j])
            {
                temp.push_back(i*j) ;
                vis[i*j] = 1 ;
            }
        }
        for(int j : temp)
        {
            factors.push_back(j) ;
        }
    }
    for(int i : factors)
    {
        ++mul[i] ;
        vis[i] = 0 ;
    }
}

int main()
{
    calc() ;
    int n ;
    scanf("%d",&n) ;
    long long a[n+2] ;
    for(int i = 1 ; i <= n ; ++i)
    {
        scanf("%lld",&a[i]) ;
        add(a[i]) ;
    }
    for(int i = MX - 1 ; i >= 1 ; --i)
    {
        dp[i] = i*1LL*mul[i] ;
        for(int j : primes)
        {
            if((i*1LL*j)>=MX) break ;
            dp[i] = max(dp[i],dp[i*j] + ((mul[i]-mul[i*j])*i)) ;
        }
        ans = max(ans,dp[i]) ;
    }
    printf("%lld\n",ans) ;
    return 0 ;
}
