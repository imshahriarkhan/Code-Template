#include<bits/stdc++.h>
using namespace std ;

struct Point{
    double x, y ;
};

bool compare(Point a, Point b)
{
    return a.x<b.x || (a.x==b.x && a.y<b.y) ;
}

double cross(const Point &O , const Point &A, cont Point &B)
{
    return (A.x-O.x)*(B.y-O.y) - (A.y-O.y)*(B.x-O.x) ;
}

vector<Point> convex_hull(vector<Point> p)
{
    int n = p.size() , k = 0 ;
    vctor<Point> H(2*n) ;
    sort(p.begin(),p.end(),compare) ;
    for(int i = 0 ; i < n ; ++i)
    {
        while(k>=2 && cross(H[k-2],H[k-1],p[i])<=0) --k ;
        H[++k] = p[i] ;
    }
    for(int i = n-2 , t = k + 1 ; i >= 0 ; --i)
    {
        while(k>=t && cross(H[k-2],H[k-1],p[i])<=0) --k ;
        H[++k] = p[i] ;
    }
    H.resize(k-1) ;
    return H ;
}

int main()
{

}
