#include<bits/stdc++.h>
using namespace std ;

//to reduce time consumption don't do extra operations
//complexity is at least O(log(n)) because of gcd

struct fraction
{
    long long x , y ;
    fraction(long long x = 1 , long long y = 1) : x(x) , y(y) {}
    fraction reduce(const fraction &a) const
    {
        long long gcd = __gcd(a.x,a.y) ;
        return fraction(a.x/gcd,a.y/gcd) ;
    }
    fraction& operator=(const fraction &a)
    {
        x = a.x , y = a.y ;
        return *this ;
    }
    fraction operator+(const fraction &a) const
    {
        return reduce(fraction((x*a.y)+(a.x*y),(a.y*y))) ;
    }
    fraction operator-(const fraction &a) const
    {
        return reduce(fraction((x*a.y)-(a.x*y),(a.y*y))) ;
    }
    fraction operator*(const long long &a) const
    {
        return reduce(fraction(x*a,y)) ;
    }
    fraction operator/(const long long &a) const
    {
        return reduce(fraction(x,y*a)) ;
    }
    bool operator==(const fraction &a) const
    {
        return ((x==a.x) && (y==a.y)) ;
    }
};
