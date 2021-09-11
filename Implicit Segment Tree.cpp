#include<bits/stdc++.h>
using namespace std ;

//implcit segment tree with lazy propagation

const int MX = 15000005 ;

int ptr = 1 ;

struct Node{
    short int lazy ;
    int sum , left , right ;
    Node() {lazy = -1 , sum = left = right = 0 ;}
} T[MX] ;

inline void push(int node , int low , int high)
{
    if(T[node].lazy < 0) return ;

    if(T[node].left==0)  T[node].left = ++ptr ;
    if(T[node].right==0) T[node].right = ++ptr ;

    int mid = (low+high)>>1 ;

    T[T[node].left].sum = (T[node].lazy*(mid-low+1)) ;
    T[T[node].left].lazy = T[node].lazy ;

    T[T[node].right].sum = (T[node].lazy*(high-mid)) ;
    T[T[node].right].lazy = T[node].lazy ;

    T[node].lazy = -1 ;
}

void update(int node , int low , int high , int l , int r , int val)
{
    if(l>r) return ;
    if((high<l) || (low>r)) return ;
    if((l<=low) && (high<=r))
    {
        T[node].sum = ((high-low+1)*val) ;
        T[node].lazy = val ;
        return ;
    }
    push(node,low,high) ;

    int mid = (low+high)>>1 ;

    if(T[node].left == 0) T[node].left = ++ptr ;
    if(T[node].right == 0) T[node].right = ++ptr ;

    update(T[node].left , low , mid , l , r , val) ;
    update(T[node].right , mid + 1 , high , l , r , val) ;

    T[node].sum = T[T[node].left].sum + T[T[node].right].sum ;
}

int main()
{
    int n ;
    scanf("%d",&n) ;
    update(1,1,n,1,n,1) ;
    int q ;
    scanf("%d",&q) ;
    while(q--)
    {
        int l , r , k ;
        scanf("%d%d%d",&l,&r,&k) ;
        if(k==1) update(1,1,n,l,r,0) ;
        else update(1,1,n,l,r,1) ;
        printf("%d\n",T[1].sum) ;
    }
    return 0 ;
}
