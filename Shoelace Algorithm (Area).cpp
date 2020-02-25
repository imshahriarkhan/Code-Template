#include<bits/stdc++.h>
using namespace std ;

int main()
{
    int sum1 = 0 , sum2 = 0 ;
    for(int i = 0 ; i < n ; ++i)
    {
        sum1 += x[i]*y[(i+1)%n] ;
        sum2 += y[i]*x[(i+1)%n] ;
    }
    double area = (abs(sum1-sum2))/2 ;
}
