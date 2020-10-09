#include<bits/stdc++.h>
using namespace std ;

const int mx = 1e5 + 69 ;

vector<int> parent , depth , heavy , head , pos ;

int cur_pos ;

int dfs(int v , vector<vector<int> > const& adj)
{
    int siz = 1 , max_c_size = 0 ;
    for(int c : adj[v])
    {
        if(c!=parent[v])
        {
            parent[c] = v , depth[c] = depth[v] + 1 ;
            int c_size = dfs(c,adj) ;
            siz += c_size ;
            if(c_size > max_c_size)
            {
                max_c_size = c_size , heavy[v] = c ;
            }
        }
    }
    return siz ;
}

int decompose(int v , int h , vector<vector<int> > const& adj)
{
    head[v] = h , pos[v] = cur_pos++ ;
    if(heavy[v] != -1) decompose(heavy[v],h,adj) ;
    for(int c : adj[v])
    {
        if(c != parent[v] && c != heavy[v])
        {
            decompose(c,c,adj) ;
        }
    }
}

void init(vector<vector<int> > const& adj)
{
    int n = adj.size() ;
    parent = vector<int>(n+1) ;
    depth = vector<int>(n+1) ;
    heavy = vector<int>(n,-1) ;
    head = vector<int>(n) ;
    pos = vector<int>(n) ;
    cur_pos = 0 ;
    dfs(0,adj) ;
    decompose(0,0,adj) ;
}

int query(int a , int b)
{
    int res = 0 ;
    for(; head[a] != head[b] ; b = parent[head[b]])
    {
        if(depth[head[a]]>depth[head[b]]) swap(a,b) ;
        int cur_heavy_path_max = segtree_query(pos[head[b]],pos[b]) ;
        res = max(res,cur_heavy_path_max) ;
    }
    if(depth[a] > depth[b]) swap(a,b) ;
    res = max(res,segtree_query(pos[a],pos[b])) ;
    return res ;
}
