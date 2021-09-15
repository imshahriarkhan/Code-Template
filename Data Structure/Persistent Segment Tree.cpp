#include<bits/stdc++.h>
using namespace std ;

//For each modification of the Segment Tree we will receive a new root vertex.
//To quickly jump between two different versions of the Segment Tree, we need to store this roots in an array.
//To use a specific version of the Segment Tree we simply call the query using the appropriate root vertex.

const int MX = 1e5 + 5 ;

struct Node
{
    int val ;
    Node *left , *right ;

    Node(int v) : val(v) , left(nullptr) , right(nullptr) {}

    Node(Node *l_left, Node *r_right) : val(0) , left(l_left) , right(r_right) {}
};

int n , a[MX] ;

Node* roots[MX] ;

Node* build(int low , int high)
{
    if(low==high) return new Node(a[low]) ;
    int mid = (low+high)>>1 ;
    return new Node(build(low,mid),build(mid+1,high)) ;
}

Node* update(Node* node , int low , int high , int ind , int val)
{
    if(low==high) return new Node(val) ;
    int mid = (low+high)>>1 ;
    if(ind>mid) return new Node(node->left,update(node->right,mid+1,high,ind,val)) ;
    else return new Node(update(node->left,low,mid,ind,val),node->right) ;
}

int query(Node* node , int low , int high , int l , int r)
{
    if(l>r) return 0 ;
    if((l>high) || (r<low)) return 0 ;
    if((l<=low) && (high<=r))
    {
        return node -> val ;
    }
    int mid = (low+high)>>1 ;
    return query(node->left,low,mid,l,r) + query(node->right,mid+1,high,l,r) ;
}

void update_item(int ind , int val , int prev_time , int cur_time)
{
    roots[cur_time] = update(roots[prev_time],1,n,ind,val) ;
}

void init(int nn , int* in)
{
    n = nn ;
    for(int i = 0 ; i < n ; ++i)
    {
        a[i] = in[i] ;
    }
    roots[0] = build(1,n) ;
}
