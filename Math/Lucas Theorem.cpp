#include<bits/stdc++.h>
using namespace std ;

vector<int> represent(int n)
{
    vector<int> res ;
    while(n)
    {
        res.push_back(n%mod) ;
        n/=mod ;
    }
    return res ;
}

int binpow(int a , int n)
{
    long long res = 1 ;
    while(n)
    {
        if(n%2!=0) res = (res*a)%mod ;
        a = ((long long)a*a)%mod ;
        n/=2 ;
    }
    return (int)res ;
}

int c(int n , int k)
{
    if(k>n) return 0 ;
    return ((fact[n]*binpow(fact[n-k],mod-2))%mod) * binpow(fact[k],mod-2)  % mod ;
}

int main()
{
    vector<int> n = represent(n) , k = represent(k) ;
    long long res = 1 ;
    for(int i = 0 ; i < k.size() ; ++i)
    {
        res = (res*C(n,k)) ;
    }
}
