#include "bits/stdc++.h"
using namespace std;

struct LCA {
    int n;
    int LOG;
    vector<vector<int>> up;
    vector<int> depth;
    vector<vector<int>> adj;

    LCA(int n = 0) { init(n); }

    void init(int n_) {
        n = n_;
        LOG = 1;
        while ((1LL << LOG) <= n) ++LOG;
        up.assign(n, vector<int>(LOG, 0));
        depth.assign(n, 0);
        adj.assign(n, {});
    }
    void build(int a = 0) {
        if (n == 0) return;
        for(int b:adj[a]){
            depth[b]=depth[a]+1;
            up[b][0]=a; // a is parent of b
            for(int i=1;i<LOG;i++){
                up[b][i]=up[ up[b][i-1] ][i-1];
            }
            build(b);
        }
    }

    int lift(int v, int k) const { // it will return node
        if (v < 0 || v >= n) return -2;
        if(k>depth[v]) return -2;
        for (int j = 0; j < LOG && v != -1; ++j) {
            if (k & (1 << j)) v = up[v][j];
        }
        return v;
    }

    int lca (int a,int b) const { 
        if(depth[a]<depth[b]) swap(a,b);
        int k=depth[a]-depth[b];
        for(int i=LOG-1;i>=0;i--){
            if(k & (1<<i)) a=up[a][i];
        }

        if(a==b) return a;

        for(int i=LOG-1;i>=0;i--){
            if(up[a][i] != up[b][i]){
                a=up[a][i];
                b=up[b][i];
            }
        }

        return up[a][0];
    }

    // distance between nodes in tree (if connected)
    int dist(int a, int b) const {
        int c = lca(a, b);
        if (c == -1) return INT_MAX; 
        return depth[a] + depth[b] - 2 * depth[c];
    }

    int kth_ancestor(int v, int k) const {
        return lift(v, k);
    }
}t;

int32_t main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    // Always make nodes 0 base
}