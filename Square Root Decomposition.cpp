#include<bits/stdc++.h>
using namespace std ;

int n ;

void build()
{
    int block = (int)sqrt(n) ;
    int ara[block] ;
    for(int i = 0 ; i < n ; ++i) ara[i/block] += a[i] ;
}

void update(int ind , int val)
{
    old_val = a[ind] ;
    ara[ind/block] += (val-old_val) ;
    a[ind] = val ;
}

int query(int l , int r)
{
    int sum = 0 , st_block = l/block , ed_block = r/block ;
    for(int i = l ; i < (st_block*block) ; ++i) sum += a[i] ;
    for(int i = ed_block*block ; i < r ; ++i) sum += a[i] ;
    for(int i = st_block+1 ; i < ed_block ; ++i) sum +=  ara[i] ;
    return sum ;
}
