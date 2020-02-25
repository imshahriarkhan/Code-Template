#include<bits/stdc++.h>
using namespace std ;

int lower_bs(int a[] , int n , int x)
{
    int l = 0 , h = n ;
    while(l<h)
    {
        int mid = (l+h)>>1 ;
        if(x<=a[mid]) h = mid ;
        else l = mid + 1 ;
    }
    return l ;
}
