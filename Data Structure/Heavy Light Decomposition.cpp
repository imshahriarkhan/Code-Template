//USACO : Cow Land
//Link : http://www.usaco.org/current/index.php?page=viewproblem2&cpid=921

#include<bits/stdc++.h>
using namespace std ;

struct tree
{
    vector<int> T ;
    void init(int N , int e[])
    {
        T = vector<int> (4*N + 4 , 0) ;
        build(e,1,1,N) ;
    }
    void build(int e[] , int node , int low , int high)
    {
        if(low==high)
        {
            T[node] = e[low] ;
            return ;
        }
        int mid = (low+high)>>1 , left = node<<1 , right = left|1 ;
        build(e,left,low,mid) , build(e,right,mid+1,high) ;
        T[node] = T[left]^T[right] ;
    }
    void update(int node , int low , int high , int idx , int val)
    {
        if((low>idx) || (high<idx)) return ;
        if(low==high)
        {
            T[node] = val ;
            return ;
        }
        int mid = (low+high)>>1 , left = node<<1 , right = left|1 ;
        update(left,low,mid,idx,val) , update(right,mid+1,high,idx,val) ;
        T[node] = T[left]^T[right] ;
    }
    int query(int node , int low , int high , int l , int r)
    {
        if((r<low) || (l>high)) return 0 ;
        if((l<=low) && (high<=r)) return T[node] ;
        int mid = (low+high)>>1 , left = node<<1 , right = left|1 ;
        return (query(left,low,mid,l,r)^query(right,mid+1,high,l,r)) ;
    }
} T ;

struct HLD
{
    int N , LG = 25 , timer = 0 , timer2 = 0 ;

    vector<vector<int> > up , adj ;

    vector<int> bigChild , sub , depth , chain , label , tin , tout , par ;

    void init(int n , vector<int> G[])
    {
        N = n ;
        bigChild = vector<int> (4*n + 4 , 0) ;
        sub = vector<int> (4*n + 4 , 0) ;
        depth = vector<int> (4*n + 4 , 0) ;
        chain = vector<int> (4*n + 4 , 0) ;
        label = vector<int> (4*n + 4 , 0) ;
        tin = vector<int> (4*n + 4 , 0) ;
        tout = vector<int> (4*n + 4 , 0) ;
        par = vector<int> (4*n + 4 , 0) ;
        up = vector<vector<int> > (4*n + 4 , vector<int>(LG , 0)) ;
        adj = vector<vector<int> > (4*n + 4) ;
        for(int i = 0 ; i <= n ; ++i)
        {
            for(int j : G[i])
            {
                adj[i].push_back(j) ;
            }
        }
    }

    void precomp(int s , int p)
    {
        depth[s] = depth[p] + 1 , sub[s] = 1 , par[s] = p ;
        int bigC = -1 , bigS = 0 ;
        for(int t : adj[s])
        {
            if(t==p) continue ;
            precomp(t,s) ;
            sub[s] += sub[t] ;
            if(sub[t]>=bigS)
            {
                bigS = sub[t] ;
                bigC = t ;
            }
        }
        bigChild[s] = bigC ;
    }

    void build_tree(int s , int p)
    {
        if(bigChild[p]==s) chain[s] = chain[p] ;
        else chain[s] = s ;
        label[s] = ++timer , tin[s] = ++timer2 , up[s][0] = p ;
        for(int i = 1 ; i < LG ; ++i)
        {
            up[s][i] = up[up[s][i-1]][i-1] ;
        }
        if(bigChild[s]!=(-1)) build_tree(bigChild[s],s) ;
        for(int t : adj[s])
        {
            if(t==p) continue ;
            if(t==bigChild[s]) continue ;
            build_tree(t,s) ;
        }
        tout[s] = ++timer2 ;
    }

    bool is_ancestor(int u , int v)
    {
        return ((tin[u]<=tin[v]) && (tout[u]>=tout[v])) ;
    }

    int find_lca(int u , int v)
    {
        if(is_ancestor(u,v)) return u ;
        if(is_ancestor(v,u)) return v ;
        for(int i = LG - 1 ; i >= 0 ; --i)
        {
            if(!is_ancestor(up[u][i],v))
            {
                u = up[u][i] ;
            }
        }
        return up[u][0] ;
    }

    int find_node(int u , int dist)
    {
        for(int i = LG - 1 ; i >= 0 ; --i)
        {
            if((1<<i)<=dist)
            {
                u = up[u][i] ;
                dist -= (1<<i) ;
            }
        }
        return u ;
    }

    int query_chain(int l , int r)
    {
        int ret = 0 ;
        while(depth[l]!=depth[r])
        {
            int top = chain[l] ;
            if(depth[top]<=depth[r])
            {
                int diff = depth[l] - depth[r] ;
                top = find_node(l,diff-1) ;
            }
            ret = (ret^T.query(1,1,N,label[top],label[l])) ;
            l = par[top] ;
        }
        return ret ;
    }

    int query(int l , int r)
    {
        int lca = find_lca(l,r) ;
        int ret = query_chain(l,lca)^query_chain(r,lca) ;
        return (ret^T.query(1,1,N,label[lca],label[lca])) ;
    }

    void update(int idx , int val)
    {
        T.update(1,1,N,label[idx],val) ;
    }

    void process(int n , int e[] , vector<int> adj[])
    {
        init(n,adj) ;
        precomp(1,1) ;
        build_tree(1,1) ;
        int f[n+2] = {0} ;
        for(int i = 1 ; i <= n ; ++i)
        {
            f[label[i]] = e[i] ;
        }
        T.init(n,f) ;
    }
};

int main()
{
    freopen("cowland.in","r",stdin) ;
    freopen("cowland.out","w",stdout) ;
    int n , q ;
    scanf("%d%d",&n,&q) ;
    vector<int> adj[n+2] ;
    int e[n+2] ;
    for(int i = 1 ; i <= n ; ++i)
    {
        scanf("%d",&e[i]) ;
    }
    for(int i = 1 ; i < n ; ++i)
    {
        int a , b ;
        scanf("%d%d",&a,&b) ;
        adj[a].push_back(b) ;
        adj[b].push_back(a) ;
    }
    HLD H ;
    H.process(n,e,adj) ;
    while(q--)
    {
        int type ;
        scanf("%d",&type) ;
        if(type==1)
        {
            int i , v ;
            scanf("%d%d",&i,&v) ;
            H.update(i,v) ;
        }
        else
        {
            int i , j ;
            scanf("%d%d",&i,&j) ;
            printf("%d\n",H.query(i,j)) ;
        }
    }
    return 0 ;
}
