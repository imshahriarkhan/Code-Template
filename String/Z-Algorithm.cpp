#include<bits/stdc++.h>
using namespace std ;

const int MX = 1e6 + 5 ;

int n , z[MX] , mx , ans ;

string s ;

void z_function()
{
    z[0] = 0 ;
    int l = 0 , r = 0 ;
    for(int i = 1 ; i < n ; ++i)
    {
        if(i<=r) z[i] = min(z[i-l],r-i+1) ;
        while(((i+z[i])<n) && (s[z[i]]==s[i+z[i]]))
        {
            ++z[i] ;
        }
        if((i+z[i]-1)>r)
        {
            l = i , r = i + z[i] - 1 ;
        }
    }
}

int main()
{
    cin>>s ;
    n = s.size() ;
    z_function() ;
    return 0 ;
}
