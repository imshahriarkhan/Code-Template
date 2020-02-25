#include<bits/stdc++.h>
using namespace std ;

const int mx = 1e5 + 1 ;

int tree[4*mx] ;

bool marked[mx] ;

void build(int a[] , int node , int low , int high)
{
    if(low==high) tree[node] = a[low] ;
    else
    {
        int mid = (low+high)>>1 ;
        build(a,node<<1,low,mid) ;
        build(a,(node<<1)|1,mid+1,high) ;
        tree[node] = 0 ;
    }
}

void push(int v)
{
    if(marked[v])
    {
        int left = v<<1 , right = left|1 ;
        tree[left] = tree[right] = tree[v] ;
        marked[left] = marked[right] = true ;
        marked[v] = false ;
    }
}

void update(int node , int low , int high , int l , int r , int val)
{
    if(l>r) return ;
    if(l==low && high==r)
    {
        tree[node] = val ;
        marked[node] = true ;
    }
    else
    {
        push(node) ;
        int mid = (low+high)>>1 , left = node<<1 , right = left|1 ;
        update(left,low,mid,l,min(r,mid),val) ;
        update(right,mid+1,high,max(l,mid+1),r,val) ;
    }
}

int query(int node , int low , int high , int ind)
{
    if(low==high) return tree[node] ;
    push(node) ;
    int mid = (low+high)>>1 ;
    if(ind<=mid) return query(node<<1 , low , mid , ind) ;
    else return query((node<<1)|1 , mid + 1 , high , ind) ;
}

int main()
{

}
