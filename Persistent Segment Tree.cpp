#include<bits/stdc++.h>
using namespace std ;

//For each modification of the Segment Tree we will receive a new root vertex.
//To quickly jump between two different versions of the Segment Tree, we need to store this roots in an array.
//To use a specific version of the Segment Tree we simply call the query using the appropriate root vertex.

struct Vertex{
    Vertex *l , *r ;
    int sum ;
    Vertex(int val) : l(nullptr) , r(nullptr) , sum(val) {}
    Vertex(Vertex *l , Vertex *r) : l(l) , r(r) , sum(0){
        if(l) sum += l -> sum ;
        if(r) sum += r -> sum ;
    }
};

Vertex* build(int a[] , int tl , int tr)
{
    if(tl==tr) return new Vertex(a[tl]) ;
    int tm = (tl + tr)>>1 ;
    return new Vertex(build(a,tl,tm),build(a,tm+1,tr)) ;
}

int get_sum(Vertex* v , int tl , int tr , int l , int r)
{
    if(l>r) return 0 ;
    if(l==tl && tr==r) return v->sum ;
    int tm = (tl + tr)>>1 ;
    return get_sum(v->l , tl , tm , l , min(r,tm)) + get_sum(v->r,tm+1,tr,max(l,tm+1),r) ;
}

Vertex* update(Vertex* v , int tl , int tr , int pos , int new_val)
{
    if(tl==tr) return new Vertex(new_val) ;
    int tm = (tl + tr)>>1 ;
    if(pos <= tm) return new Vertex(update(v->l,tl,tm,pos,new_val),v->r) ;
    else return new Vertex(v->l,update(v->r,tm+1,tr,pos,new_val)) ;
}
