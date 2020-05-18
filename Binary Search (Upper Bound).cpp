#include<bits/stdc++.h>
using namespace std ;

int upper_bs(int a[] , int n , int x)
{
    int l = 0 , h = n ;
    while(l<h)
    {
        int mid = l + (h-l)/2 ;
        if(x>=a[mid]) l = mid + 1 ;
        else h = mid ;
    }
    return l ;
}
