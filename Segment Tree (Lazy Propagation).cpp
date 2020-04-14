#include<bits/stdc++.h>
using namespace std ;

#define ll long long

struct lazy_tree
{
	vector<ll> t, lazy ;

	void init(int a[] , int low , int n)
	{
		t = vector<ll> (4 * n + 4 , 0) ;
		lazy = vector<ll> (4 * n + 4 , 0) ;
		build(a,1,low,n) ;
	}

	void build(int a[] , int node , int low , int high)
  	{
		if(low==high) t[node] = a[low] ;
		else
		{
		    int mid = (low+high)>>1 , left = node<<1 , right = left|1 ;
		    build(a,low,mid,left) ;
		    build(a,mid+1,high,right) ;
		    t[node] = t[left] + t[right] ;
		}
   	 }

	void upd(int node, int l, int r, ll v)
	{
		lazy[node] += v ;
		t[node] += (r - l + 1) * v ;
	}

	void shift(int node, int l, int r)
	{
		int m = (l + r)>>1 , L = node<<1 , R = L|1 ;
		upd(L, l, m, lazy[node]) ;
		upd(R, m + 1, r, lazy[node]) ;
		lazy[node] = 0 ;
	}

	void update(int node, int l, int r, int i, int j, ll v)
	{
		if(r < i || l > j) return ;
		if(i <= l && r <= j)
       		{
			upd(node, l, r, v) ;
			return;
		}

		shift(node, l, r);
		int m = (l + r)>>1, L = node<<1, R = L|1 ;
		update(L, l, m, i, j, v) ;
		update(R, m + 1, r, i, j, v) ;
		t[node] = t[L] + t[R] ;
	}

	ll query(int node, int l, int r, int i, int j)
	{
		if(r < i || l > j) return 0 ;
		if(i <= l && r <= j) return t[node] ;
		shift(node, l, r);
		int m = (l + r)>>1, L = node<<1 , R = L|1 ;
		return query(L, l, m, i, j) + query(R, m + 1, r, i, j) ;
	}
} ;
