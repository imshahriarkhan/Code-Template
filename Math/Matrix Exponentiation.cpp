#include<bits/stdc++.h>
using namespace std ;

//Magic Gems : https://codeforces.com/problemset/problem/1117/D

const long long mod = 1e9 + 7 , mx = 105 ;

struct Matrix{
    long long mat[mx][mx] ;
    Matrix operator*(const Matrix &b)
    {
        long long res[mx][mx] ;
        for(int i = 0 ; i < mx ; ++i)
        {
            for(int j = 0 ; j < mx ; ++j)
            {
                res[i][j] = 0 ;
                for(int k = 0 ; k < mx ; ++k)
                {
                    res[i][j] += (mat[i][k]*b.mat[k][j])%mod ;
                    res[i][j] %= mod ;
                }
            }
        }
        Matrix X ;
        swap(X.mat,res) ;
        return X ;
    }
    Matrix binpow(Matrix a , long long k)
    {
        Matrix res ;
        for(int i = 0 ; i < mx ; ++i)
        {
            res.mat[i][i] = 1 ;
        }
        while(k>0)
        {
            if(k&1) res = (res*a) ;
            k >>= 1 , a = (a*a) ;
        }
        return res ;
    }
};

int main()
{
    long long n , m ;
    scanf("%lld%lld",&n,&m) ;
    if(n<m)
    {
        puts("1") ;
        return 0 ;
    }
    Matrix s ;
    s.mat[m-1][0] = s.mat[m-1][m-1] = 1 ;
    for(int i = 0 ; i < (m-1) ; ++i)
    {
        s.mat[i][i+1] = 1 ;
    }
    s = s.binpow(s,n-m+1) ;
    long long ans = 0LL ;
    for(int i = 0 ; i < m ; ++i)
    {
        ans += s.mat[m-1][i] ; // (s.mat[m-1][i] || s.mat[i][m-1])
        ans %= mod ;
    }
    printf("%lld\n",ans) ;
    return 0 ;
}
