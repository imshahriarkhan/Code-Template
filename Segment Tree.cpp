#include<bits/stdc++.h>
using namespace std ;

const int mx = 1e5 + 1 ;

int n , tree[4*mx] ;

void build(int a[] , int low , int high , int node)
{
    if(low==high) tree[node] = a[low] ;
    else
    {
        int mid = (low+high)>>1 , left = node<<1 , right = left|1 ;
        build(a,low,mid,left) ;
        build(a,mid+1,high,right) ;
        tree[node] = tree[left] + tree[right] ;
    }
}

void update(int low , int high , int node , int ind , int val)
{
    if(low==high) tree[node] = val ;
    else
    {
        int mid = (low+high)>>1 , left = node<<1 , right = left|1 ;
        if(ind<=mid) update(low,mid,left,ind,val) ;
        else update(mid+1,high,right,ind,val) ;
        tree[node] = tree[left] + tree[right] ;
    }
}

int sum(int low , int high , int node , int l , int r)
{
    if(l>r) return 0 ;
    if(l==low && r==high) return tree[node] ;
    int mid = (low+high)>>1 , left = node<<1 , right = left|1 ;
    return sum(low,mid,left,l,r) + sum(mid+1,high,right,l,r) ;
}

int main()
{

}
