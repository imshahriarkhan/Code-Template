#include<bits/stdc++.h>
using namespace std ;

const int maxn = 1e5 + 10 ;

string s , t ;

int p[maxn] ;

void prefix()
{
    int now = p[0] = -1 ;
    int len = s.size() ;
    for(int i = 1 ; i < len ; ++i)
    {
        while(now!=-1 && s[now+1]!=s[i]) now = p[now] ;
        if(s[now+1]==s[i]) p[i] = ++now ;
        else p[i] = now = -1 ;
    }
}

int kmp()
{
    prefix() ;
    int cnt = 0 , now = -1 ;
    for(int i = 0 ; i < t.size() ; ++i)
    {
        while(now != -1 && s[now+1]!=t[i]) now = p[now] ;
        if(s[now+1]==t[i]) ++now ;
        else now = -1 ;
        if(now==s.size()-1) { now = p[now] ; ++cnt ; }
    }
    return cnt ;
}

int main()
{

}
