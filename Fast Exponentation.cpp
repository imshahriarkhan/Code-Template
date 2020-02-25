#include<bits/stdc++.h>
using namespace std ;

int fast_exponentiation(int a , int n)
{
    long long res = 1 ;
    while(n)
    {
        if(n&1) res = (res*a)%mod ;
        a = (long long)(a * a) % mod ;
        n >> 1 ;
    }
    return res ;
}


int power(int a , int n)
{
    if(n==0) return 1 ;
    else if(n==1) return a ;
    else
    {
        int r = power(a,n/2) ;
        if(n%2==0) return r*r ;
        else return r*a*r ;
    }
}
