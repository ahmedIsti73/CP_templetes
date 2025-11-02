#include"bits/stdc++.h"
using namespace std;
#define endl '\n'
#define PB push_back
using ll = long long;
class SparseSegTree {

private:
    struct node {
        ll freq=0;
        ll lazy=0;
        int left=0;
        int right=0;
        bool lazy_flag=false;
    };
    vector<node> tree;
    const ll n;
    int timer=1;
    // int comb(int a,int b) { return a+b; }

    void apply(int cur,ll l,ll r,ll val) { // check here
        tree[cur].lazy=val;
        tree[cur].lazy_flag=true;
        tree[cur].freq=(r-l+1)*val;
    }

    void push_down(int cur,ll l,ll r){
        if(!tree[cur].left){
            tree[cur].left= ++timer;
            tree.PB(node());
        }
        if(!tree[cur].right){
            tree[cur].right= ++timer;
            tree.PB(node());
        }
        if(!tree[cur].lazy_flag) return;
        ll mid=(l+r)>>1;
        apply(tree[cur].left,l,mid,tree[cur].lazy);
        apply(tree[cur].right,mid+1,r,tree[cur].lazy);
        tree[cur].lazy_flag=false;
        tree[cur].lazy=0;
    }

    void upd(int cur,ll l,ll r,ll ql,ll qr,ll val) {
        if(qr<l || ql>r) return;
        if(ql<=l && r<=qr) apply(cur,l,r,val);
        else {
            push_down(cur,l,r);
            ll mid=(l+r)>>1;
            upd(tree[cur].left,l,mid,ql,qr,val);
            upd(tree[cur].right,mid+1,r,ql,qr,val);
            tree[cur].freq=
                tree[tree[cur].left].freq + tree[tree[cur].right].freq; // check here
        }
    }

    ll query(int cur,ll l,ll r,ll ql,ll qr) {
        if(qr<l || ql>r || !cur) return 0;
        if(ql<=l && r<=qr) return tree[cur].freq;
        push_down(cur,l,r);
        ll mid=(l+r)>>1;
        return query(tree[cur].left,l,mid,ql,qr) + 
               query(tree[cur].right,mid+1,r,ql,qr); // check here
    }

public:
    SparseSegTree(ll n,int q=0) : n(n) {
        if(q>0) { tree.reserve(2*q*__lg(n)); }
        tree.PB(node()); tree.PB(node());
    }
    void upd(ll ql,ll qr,ll val) { upd(1,1,n,ql,qr,val); }
    int query(ll ql,ll qr) {return query(1,1,n,ql,qr); }
};
int32_t main(){
    int q; cin>>q;
    cin>>q;
    const int range_size=1e9;
    SparseSegTree st(range_size+1,q); // pass n+q if there is n given
}
