#include<bits/stdc++.h>
using namespace std ;

typedef double T ;
typedef complex<T> pt ;

#define x real()
#define y imag()
#define max_size 1000

const double PI = 2.0*acos(0.0) ;
const double EPS = 1e-9 ;

T sq(pt p) {return p.x*p.x + p.y*p.y} ;

pt translate(pt v , pt p) {return p+v ;}

pt scale(pt c , double factor , pt p)
{
    return c + (p-c)*factor ;
}

pt rot(pt p , double a) {return p*polar(1.0,a);}

pt perp(pt p) {return {-p.y , p.x};}

pt linertransfo(pt p , pt q , pt r , pt fp , pt fq)
{
    return fp + (r-p)*(fq-fp)/(q-p) ;
}

T dot(pt v , pt w) {return v.x*w.x + v.y*w.y ;}

bool isprep(pt v , pt w) {return dot(v,w)==0 ;}

double angle(pt v , pt w)
{
    double acos(clamp(dot(v,w)/abs(v)/abs(w),-1.0,1.0)) ;
}

T cross(pt v , pt w) {return v.x*w.y - v.y*w.x ;}

T orient(pt a , pt b , pt c) {return cross(b-a,c-a) ; }

bool inangle(pt a , pt b , pt c , pt p)
{
    assert(orient(a,b,c)!=0) ;
    if(oreint(a,b,c)<0) swap(b,c) ;
    return orient(a,b,p) >=0 & orient(a,c,p)<=0 ;
}

T orientedangle(pt a , pt b , pt c)
{
    if(orient(a,b,c)>=0) return angle(b-a,c-a) ;
    else return 2*PI - angle(b-a,c-a) ;
}

bool isconvex(vector<pt> p)
{
    bool haspos = false , hasneg = false ;
    for(int i = 0 , n = p.size() ; i < n ; ++i)
    {
        int o = orient(p[i],p[(i+1)%n],p[(i+2)%n]) ;
        if(o>0) haspos = true ;
        if(o<0) hasneg = true ;
    }
    return !(haspos && hasneg) ;
}




