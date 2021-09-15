#include<bits/stdc++.h>
using namespace std ;

const int mx = 1e4 + 69 ;

vector<pair<int , pair<int,int> > > adj[mx] ;

int n , weight[mx] , heavy[mx] , index_node[mx] , parent[mx] , depth[mx] , root[mx] , pos[mx] , vx[mx] , cur_pos = 1 ;

int dfs(int u , int p)
{
    int siz = adj[u].size() , max_size = 0 , subtree_size = 1 ;
    parent[u] = p , depth[u] = depth[p] + 1 ;
    for(int i = 0 ; i < siz ; ++i)
    {
        int v = adj[u][i].first ;
        if(v==p) continue ;
        int cost = adj[u][i].second.first , index = adj[u][i].second.second , cur = dfs(v,u) ; ;
        if(cur>max_size)
        {
            max_size = cur ;
            heavy[u] = v ;
        }
        weight[v] = cost ;
        index_node[index] = v ;
        subtree_size += cur ;
    }
    return subtree_size ;
}

void hld()
{
    cur_pos = 1 ;
    for(int i = 1 ; i <= n ; ++i)
    {
        if(parent[i] == -1 || heavy[parent[i]]!=i)
        {
            for(int j = i ; j != -1 ; j = heavy[j])
            {
                root[j] = i ;
                vx[cur_pos] = weight[j] , pos[j] = cur_pos ;
                ++cur_pos ;
            }
        }
    }
}

struct segtree
{
    vector<int> t ;
    void init(int n , int a[])
    {
        t = vector<int> (4*n,0) ;
        build(1,1,n,a) ;
    }
    void build(int node , int l , int r , int a[])
    {
        if(l==r) t[node] = a[l] ;
        else
        {
            int mid = (l+r)>>1 , left = node<<1 , right = left|1 ;
            build(left,l,mid,a) , build(right,mid+1,r,a) ;
            t[node] = max(t[left],t[right]) ;
        }
    }
    void update(int node , int l , int r , int ind , int val)
    {
        if(l>ind || r<ind) return ;
        if(l==r && l==ind)
        {
            t[node] = val ;
            return ;
        }
        int mid = (l+r)>>1 , left = node<<1 , right = left|1 ;
        update(left,l,mid,ind,val) , update(right,mid+1,r,ind,val) ;
        t[node] = max(t[left],t[right]) ;
    }
    int query(int node , int low , int high , int l , int r)
    {
        if(r<l) return 0 ;
        if(low>r || high<l) return 0 ;
        if(low>=l && high<=r) return t[node] ;
        int mid = (low+high)>>1 , left = node<<1 , right = left | 1 ;
        return max(query(left,low,mid,l,r),query(right,mid+1,high,l,r)) ;
    }
} tree ;

int find_ans(int a , int b)
{
    int res = 0 ;
    while(root[a] != root[b])
    {
        if(depth[root[a]] < depth[root[b]]) swap(a,b) ;
        res = max(res,tree.query(1,1,n,pos[root[a]],pos[a])) ;
        a = parent[root[a]] ;
    }
    if(depth[a] > depth[b]) swap(a,b) ;
    res = max(res,tree.query(1,1,n,pos[a] + 1 , pos[b])) ;
    return res ;
}

int main()
{
    int t ;
    scanf("%d",&t) ;
    while(t--)
    {
        scanf("%d",&n) ;
        for(int i = 1 ; i < n ; ++i)
        {
            int a , b , c ;
            scanf("%d%d%d",&a,&b,&c) ;
            adj[a].push_back({b,{c,i}}) ;
            adj[b].push_back({a,{c,i}}) ;
        }
        for(int i = 0 ; i <= n ; ++i) heavy[i] = -1 ;
        weight[1] = 0 ;
        dfs(1,0) ;
        hld() ;
        tree.init(n,vx) ;
        while(1)
        {
            char s[10] ;
            scanf("%s",s) ;
            if(s[0] == 'D') break ;
            else if(s[0] == 'C')
            {
                int i , ti ;
                scanf("%d%d",&i,&ti) ;
                tree.update(1,1,n,pos[index_node[i]],ti) ;
            }
            else
            {
                int a , b ;
                scanf("%d%d",&a,&b) ;
                printf("%d\n",find_ans(a,b)) ;
            }
        }
        for(int i = 1 ; i <= n ; ++i) adj[i].clear() ;
    }
    return 0 ;
}
