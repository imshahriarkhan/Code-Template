/*************************************************************************************
    Implicit segment tree with addition on the interval
    and getting the value of some element.
    Works on the intervals like [1..10^9].
    O(logN) on query, O(NlogN) of memory.
    Author: Bekzhan Kassenov.
    Based on problem 3327 from informatics.mccme.ru
    http://informatics.mccme.ru/moodle/mod/statements/view.php?chapterid=3327
*************************************************************************************/

#include<bits/stdc++.h>
using namespace std ;

typedef long long ll

struct Node{
    ll sum ;
    Node *l , *r ;
    Node() : sum(0) , l(NULL) , r(NULL) {}
};

void add(Node *v, int l , int r , int q_l , int q_r , ll val)
{
    if(l > r || q_r < l || q_l > r) return ;
    if(q_l <= l && r <= q_r)
    {
        v -> sum += val ;
        return ;
    }

    int mid = (l+r)>>1 ;

    if(v -> l == NULL) v -> l = new Node() ;
    if(v -> r == NULL) v -> r = new Node() ;

    add(v -> l , l , mid , q_l , q_r , val) ;
    add(v -> r , r , mid + 1 , r , q_l , q_r , val) ;
}

ll get(Node *v , int l , int r , int pos)
{
    if(!v || l > r || pos < l || pos > r) return 0 ;
    if(l==r) return v -> sum ;
    int mid = (l+r)>>1 ;
    return v -> sum + get(v -> l , l , mid , pos) + get(v -> r , mid + 1 , r , pos) ;
}

int n , m , t , x , y , val ;
char c ;

int main()
{
    Node *root = new Node() ;
    scanf("%d ",&n) ;
    for(int i = 0 ; i < n ; ++i)
    {
        scanf("%d",&x) ;
        add(root,0,n-1,i,i,x) ;
    }
    //now just pass root everywhere instead of 1.. It will work in the same way..
    //we are just creating nodes only when we are receiving them..
    //so it won't take too much time...
    //we can also use coordinate compression
    //but it will be O(log(n)*log(n)) which may be slower..
}
