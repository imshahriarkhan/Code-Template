#include<bits/stdc++.h>
using namespace std ;

void printmax(int a[] , int n , int k)
{
    deque<int> q(k) ;
    for(int i = 0 ; i < k ; ++i)
    {
        while((!q.empty() && a[i]>=a[q.back()])) q.pop_back() ;
        q.push_back(i) ;
    }
    for(int i = k ; i < n ; ++i)
    {
        printf("%d\n",a[q.front()]) ;
        while((!q.empty() && q.front()<=(i-k))) q.pop_front() ;
        while((!q.empty() && a[i]>=a[q.back()])) q.pop_back() ;
        q.push_back(i) ;
    }
}
