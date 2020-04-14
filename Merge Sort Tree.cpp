#include<bits/stdc++.h>
using namespace std ;

#define all(v) v.begin(), v.end()

int lower_bs(vector<int> &a , int x)
{
    int l = 0 , h = a.size() ;
    while(l<h)
    {
        int mid = (l+h)>>1 ;
        if(x<=a[mid]) h = mid ;
        else l = mid + 1 ;
    }
    return l ;
}

struct merge_sort_tree
{
    vector<int> *t ;

    void init(int n)
    {
        t = new vector<int> [n] ;
    }

    void build(int a[] , int node , int l , int r)
    {
        if(l==r) t[node].push_back(a[l]) ;
        else
        {
            int mid = (l+r)>>1 , left = node<<1 , right = left|1 ;
            build(a,left,l,mid) ;
            build(a,right,mid+1,r) ;
            merge(all(t[left]),all(t[right]),back_inserter(t[node])) ;
        }
    }

    int query(int node , int l , int r , int i , int j , int k)
    {
        if(i>r || j<l) return 0 ;
        if(i<=l && j>=r) return lower_bs(t[node],k) ;

        int mid = (l+r)>>1 , left = node<<1 , right = left|1 ;
        return query(left,l,mid,i,j,k) + query(right,mid+1,r,i,j,k) ;
    }
} ;
