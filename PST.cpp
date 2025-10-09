#include "bits/stdc++.h"
using namespace std;
using ll = long long;
#define PB push_back
class PST{
    private:
        struct node{
            ll sum=0;
            int lc=0,rc=0; // left child right child 
        };
    const int n;
    vector<node> tree;
    int timer=1;

    node join(int lc,int rc){
        return node{tree[lc].sum+tree[rc].sum,lc,rc}; // check here
    }
    
    int build_(int l,int r,const vector<int> &arr){
        int id=timer++;
        if(l==r){
            tree[id]={arr[l],0,0}; // check here
            return id;
        }
        int mid=(l+r)>>1;
        tree[id]=join(build_(l,mid,arr),build_(mid+1,r,arr));
        return id;
    }

    int upd_(int v,int l,int r,int pos,int val){
        int id=timer++;
        if(l==r){
            tree[id]={val,0,0}; // check here
            return id;
        }
        int mid=(l+r)>>1;
        if(pos<=mid) tree[id]=join(upd_(tree[v].lc,l,mid,pos,val),tree[v].rc);
        else tree[id]=join(tree[v].lc,upd_(tree[v].rc,mid+1,r,pos,val));
        return id;
    }

    ll query_(int v,int l,int r,int i,int j){
        if(l>j || r<i) return 0LL;           /// check here
        if(i<=l && r<=j) return tree[v].sum;
        int mid=(l+r)>>1;
        return query_(tree[v].lc,l,mid,i,j)+
               query_(tree[v].rc,mid+1,r,i,j); 
    }

    public:
    PST(int n,int mx_nodes) : n(n),tree(mx_nodes) {}
    int build(const vector<int> &arr) { return build_(1,n,arr); }
    int upd(int root,int pos,int val) { return upd_(root,1,n,pos,val); }
    ll query(int root,int l,int r) { return query_(root,1,n,l,r); }
    int add_copy(int root){
        tree[timer]=tree[root];
        return timer++;
    } 
};
int32_t main() {
    ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cout.unsetf(ios::floatfield); cout.precision(10);
    cout.setf(ios::fixed, ios::floatfield);
    // auto cl=clock();
    int n,q; cin>>n>>q;
    vector<int> a(n+1); // 1 base
    for(int i=1;i<=n;i++) cin>>a[i];
    const int mx_nodes=2*n+q*(2+__lg(n));
    PST t(n,mx_nodes);
    vector<int> roots = {t.build(a)};
    while(q--){
        int type,k; cin>>type>>k;
        k--;
        if(type==1){
            int pos,val; cin>>pos>>val;
            roots[k]=t.upd(roots[k],pos,val);
        }else if(type==2){
            int a,b; cin>>a>>b;
            cout<<t.query(roots[k],a,b)<<endl;
        }else{
            roots.PB(t.add_copy(roots[k]));
        }
    }
    // cerr<<1.0*(clock()-cl)/CLOCKS_PER_SEC<<endl;
}

// //:::::::::::::::::::::::::::::::::::::::GlitcH::::::::::::::::::::::::::::::::