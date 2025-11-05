#include"bits/stdc++.h"
using namespace std;
using ll=long long;
#define endl '\n'
const ll INF=1e18;
const ll NINF=-1e18;
struct STBeats {
private:
    struct node{
        ll max1;                // max value
        ll max2;                // second max value
        int max_cnt;            // cnt of the largest value
        ll min1;                // min value
        ll min2;                // second min value
        int min_cnt;            // cnt of the smallest value
        ll sum;                 // sum of the range 
        int len;                // length of the range 
        ll lazy_add;            // lazy teg
        ll lazy_set;
        bool lazy_neg;
        node() : max1(NINF),max2(NINF),max_cnt(0),
                min1(INF),min2(INF),min_cnt(0),sum(0),len(0),
                lazy_add(0),lazy_set(INF),lazy_neg(false) {}
    };

    int n;
    vector<node> tree;
    inline node merge(const node& left, const node& right) {       // O(1)
        node res;
        res.sum=left.sum+right.sum;
        res.len=left.len+right.len;
        res.lazy_add=0;
        res.lazy_set=INF;
        res.lazy_neg=false;
        if(left.max1>right.max1) { // merging max data for chmin
            res.max1=left.max1;
            res.max2=max(left.max2,right.max1);
            res.max_cnt=left.max_cnt;
        }else if(left.max1<right.max1) {
            res.max1=right.max1;
            res.max2=max(left.max1,right.max2);
            res.max_cnt=right.max_cnt;
        }else if(left.max1==right.max1) {
            res.max1=left.max1;
            res.max2=max(left.max2,right.max2);
            res.max_cnt=left.max_cnt+right.max_cnt;
        }

        if(left.min1<right.min1) {  // margin min data for chmax     
            res.min1=left.min1;
            res.min2=min(left.min2,right.min1);
            res.min_cnt=left.min_cnt;
        }else if(left.min1>right.min1) {
            res.min1=right.min1;
            res.min2=min(left.min1,right.min2);
            res.min_cnt=right.min_cnt;
        }else if(left.min1==right.min1) {
            res.min1=left.min1;
            res.min2=min(left.min2,right.min2);
            res.min_cnt=left.min_cnt+right.min_cnt;
        }
        return res;
    }
    inline void apply_negative(int v) {
        swap(tree[v].max1,tree[v].min1);
        swap(tree[v].max2,tree[v].min2);
        swap(tree[v].max_cnt,tree[v].min_cnt);
        tree[v].max1*=-1;
        if(tree[v].max2!=NINF) tree[v].max2*=-1;
        tree[v].min1*=-1;
        if(tree[v].min2!=INF) tree[v].min2*=-1;
        tree[v].sum*=-1;
        if(tree[v].lazy_set!=INF) tree[v].lazy_set*=-1;
        else tree[v].lazy_add*=-1;
        tree[v].lazy_neg^=1;
    }
    inline void apply_add(int v,ll x) {             // O(1)
        if(!x) return;
        tree[v].sum+=tree[v].len*x;
        tree[v].max1+=x;
        if(tree[v].max2!=NINF) tree[v].max2+=x;
        tree[v].min1+=x;
        if(tree[v].min2!=INF) tree[v].min2+=x;

        if(tree[v].lazy_set!=INF) tree[v].lazy_set+=x;
        else tree[v].lazy_add+=x;
    }

    inline void apply_set(int v,ll x) {
        tree[v].max1=x;
        tree[v].max2=NINF;
        tree[v].max_cnt=tree[v].len;
        tree[v].min1=x;
        tree[v].min2=INF;
        tree[v].min_cnt=tree[v].len;
        tree[v].sum=tree[v].len*x;
        tree[v].lazy_add=0;
        tree[v].lazy_set=x;
        tree[v].lazy_neg=false;
    }
    inline void apply_chmin(int v,ll x) {          // O(1)
        if(x>=tree[v].max1) return;
        tree[v].sum-=tree[v].max_cnt*(tree[v].max1-x);
        if(tree[v].min1==tree[v].max1) tree[v].min1=x;
        if(tree[v].min2==tree[v].max1) tree[v].min2=x;
        tree[v].max1=x;

        if(tree[v].lazy_set !=INF) 
            tree[v].lazy_set=min(tree[v].lazy_set,x);
    }

    inline void apply_chmax(int v,ll x) {          // O(1)
        if(x<=tree[v].min1) return;
        tree[v].sum+=tree[v].min_cnt*(x-tree[v].min1);
        if(tree[v].max1==tree[v].min1) tree[v].max1=x;
        if(tree[v].max2==tree[v].min1) tree[v].max2=x;
        tree[v].min1=x;

        if(tree[v].lazy_set !=INF) 
            tree[v].lazy_set=max(tree[v].lazy_set,x);
    }

    void push_lazy(int v,int tl,int tr) {             // O(1)
        if(tl==tr) return;
        if(tree[v].lazy_set!=INF) {
            apply_set(2*v,tree[v].lazy_set);
            apply_set(2*v+1,tree[v].lazy_set);
            tree[v].lazy_set=INF;
            return;
        }
        if(tree[v].lazy_neg) {
            apply_negative(2*v);
            apply_negative(2*v+1);
            tree[v].lazy_neg=false;
        }
        if(tree[v].lazy_add!=0) {       // for lazy add
            apply_add(2*v,tree[v].lazy_add);
            apply_add(2*v+1,tree[v].lazy_add);
            tree[v].lazy_add=0;
        }
    }
    void push_beats(int v,int tl,int tr) {
        if(tl==tr) return;
        apply_chmin(2*v,tree[v].max1);
        apply_chmin(2*v+1,tree[v].max1);
        apply_chmax(2*v,tree[v].min1);
        apply_chmax(2*v+1,tree[v].min1);
    }

    void build_(int v,int tl,int tr,const vector<ll>& a) {       // O(n)
        if(tl==tr){
            tree[v].len=1;
            tree[v].sum=a[tl];
            tree[v].max1=a[tl];
            tree[v].max_cnt=1;
            tree[v].max2=NINF;
            tree[v].min1=a[tl];
            tree[v].min_cnt=1;
            tree[v].min2=INF;
            tree[v].lazy_add=0;
            tree[v].lazy_set=INF;
            tree[v].lazy_neg=false;
        }else{
            int mid=(tl+tr)>>1;
            build_(2*v,tl,mid,a);
            build_(2*v+1,mid+1,tr,a);
            tree[v]=merge(tree[2*v],tree[2*v+1]);
        }
    }

    void upd_min_(int v,int tl,int tr,int ql,int qr,ll x) {   // O(log^2 n)
        push_lazy(v,tl,tr);
        if(tree[v].max1<=x || qr<tl || tr<ql) return;
        if(ql<=tl && tr<=qr && tree[v].max2<x) {
            apply_chmin(v,x);
            return;
        }
        push_beats(v,tl,tr);
        int mid=(tl+tr)>>1;
        upd_min_(2*v,tl,mid,ql,qr,x);
        upd_min_(2*v+1,mid+1,tr,ql,qr,x);
        tree[v]=merge(tree[2*v],tree[2*v+1]);
    }

    void upd_max_(int v,int tl,int tr,int ql,int qr,ll x) {   // O(log^2 n)
        push_lazy(v,tl,tr);
        if(tree[v].min1>=x || qr<tl || tr<ql) return;
        if(ql<=tl && tr<=qr && tree[v].min2>x) {
            apply_chmax(v,x);
            return;
        }
        push_beats(v,tl,tr);
        int mid=(tl+tr)>>1;
        upd_max_(2*v,tl,mid,ql,qr,x);
        upd_max_(2*v+1,mid+1,tr,ql,qr,x);
        tree[v]=merge(tree[2*v],tree[2*v+1]);
    }

    void upd_add_(int v,int tl,int tr,int ql,int qr,ll x) {   // O(log n)
        if(qr<tl || tr<ql) return;
        if(ql<=tl && tr<=qr) {
            apply_add(v,x);
            return;
        }
        push_lazy(v,tl,tr);
        push_beats(v,tl,tr);
        int mid=(tl+tr)>>1;
        upd_add_(2*v,tl,mid,ql,qr,x);
        upd_add_(2*v+1,mid+1,tr,ql,qr,x);
        tree[v]=merge(tree[2*v],tree[2*v+1]);
    }

    void upd_set_(int v,int tl,int tr,int ql,int qr,ll x) {   // O(log n) range set
        if(qr<tl || tr<ql) return;
        if(ql<=tl && tr<=qr) {
            apply_set(v,x);
            return;
        }
        push_lazy(v,tl,tr);
        push_beats(v,tl,tr);
        int mid=(tl+tr)>>1;
        upd_set_(2*v,tl,mid,ql,qr,x);
        upd_set_(2*v+1,mid+1,tr,ql,qr,x);
        tree[v]=merge(tree[2*v],tree[2*v+1]);
    }

    void upd_mod_(int v,int tl,int tr,int ql,int qr,ll x) {   // O(log^2 n)
        push_lazy(v,tl,tr);
        if(tree[v].max1<x || qr<tl || tr<ql) return;
        if(tl==tr) {
            apply_set(v,tree[v].sum%x);
            return;
        }
        push_beats(v,tl,tr);
        int mid=(tl+tr)>>1;
        upd_mod_(2*v,tl,mid,ql,qr,x);
        upd_mod_(2*v+1,mid+1,tr,ql,qr,x);
        tree[v]=merge(tree[2*v],tree[2*v+1]);
    }
    ll floor_div(ll a,ll b) {
        if(b<0) { a=-a,b=-b; }
        ll d=a/b;
        ll r=a%b;
        if(r<0) return d-1;
        return d;
    }
    void upd_negative_(int v,int tl,int tr,int ql,int qr) {
        if(qr<tl || tr<ql) return;
        if(ql<=tl && tr<=qr) {
            apply_negative(v);
            return;
        }
        push_lazy(v,tl,tr);
        push_beats(v,tl,tr);
        int mid=(tl+tr)>>1;
        upd_negative_(2*v,tl,mid,ql,qr);
        upd_negative_(2*v+1,mid+1,tr,ql,qr);
        tree[v]=merge(tree[2*v],tree[2*v+1]);
    }
    void upd_divide_(int v,int tl,int tr,int ql,int qr,ll x) {    // O(log^2 n)
        if(x==1) return;
        if(x==-1){
            upd_negative_(v,tl,tr,ql,qr);
            return;
        }
        if(qr<tl || tr<ql || !x) return;
        push_lazy(v,tl,tr);
        ll new_min=floor_div(tree[v].min1,x);
        ll new_max=floor_div(tree[v].max1,x);
        if(ql<=tl && tr<=qr && new_min==new_max){
            apply_set(v,new_min);
            return;
        }
        if(tl==tr) {
            ll val=floor_div(tree[v].sum,x);
            apply_set(v,val);
            return;
        }
        push_beats(v,tl,tr);
        int mid=(tl+tr)>>1;
        upd_divide_(2*v,tl,mid,ql,qr,x);
        upd_divide_(2*v+1,mid+1,tr,ql,qr,x);
        tree[v]=merge(tree[2*v],tree[2*v+1]);
    }

    ll query_sum_(int v,int tl,int tr,int ql,int qr) { // O(log n)
        if(qr<tl || tr<ql) return 0;
        if(ql<=tl && tr<=qr) return tree[v].sum;
        push_lazy(v,tl,tr);
        push_beats(v,tl,tr);
        int mid=(tl+tr)>>1;
        return query_sum_(2*v,tl,mid,ql,qr) + query_sum_(2*v+1,mid+1,tr,ql,qr);
    }
    ll query_max_(int v,int tl,int tr,int ql,int qr) { // O(log n)
        if(qr<tl || tr<ql) return NINF;
        if(ql<=tl && tr<=qr) return tree[v].max1;
        push_lazy(v,tl,tr);
        push_beats(v,tl,tr);
        int mid=(tl+tr)>>1;
        return max(query_max_(2*v,tl,mid,ql,qr) , query_max_(2*v+1,mid+1,tr,ql,qr));
    }
    ll query_min_(int v,int tl,int tr,int ql,int qr) { // O(log n)
        if(qr<tl || tr<ql) return INF;
        if(ql<=tl && tr<=qr) return tree[v].min1;
        push_lazy(v,tl,tr);
        push_beats(v,tl,tr);
        int mid=(tl+tr)>>1;
        return min(query_min_(2*v,tl,mid,ql,qr) , query_min_(2*v+1,mid+1,tr,ql,qr));
    }
    
public:
    STBeats(int n_val) : n(n_val) { tree.resize(4*n+4); }
    void build(const vector<ll>& a) { build_(1,1,n,a); }
    void upd_min(int ql,int qr,ll x) { upd_min_(1,1,n,ql,qr,x); }
    void upd_max(int ql,int qr,ll x) { upd_max_(1,1,n,ql,qr,x); }
    void upd_add(int ql,int qr,ll x) { upd_add_(1,1,n,ql,qr,x); }
    void upd_set(int ql,int qr,ll x) { upd_set_(1,1,n,ql,qr,x); }
    void upd_mod(int ql,int qr,ll x) { upd_mod_(1,1,n,ql,qr,x); }
    void upd_divide(int ql,int qr,ll x) { upd_divide_(1,1,n,ql,qr,x); }
    ll query_sum(int ql,int qr) { return query_sum_(1,1,n,ql,qr); }
    ll query_max(int ql,int qr) { return query_max_(1,1,n,ql,qr); }
    ll query_min(int ql,int qr) { return query_min_(1,1,n,ql,qr); }
};
int32_t main(){
    ios_base :: sync_with_stdio(0); cin.tie(0);
    int t=1; 
    // cin>>t;
    while(t--){
      int n; cin>>n;
      int q; cin>>q;
      STBeats t(n);
      vector<ll> v(n+1);
      for(int i=1;i<=n;i++) cin>>v[i];
      t.build(v);
      while(q--){
        int type,l,r; cin>>type>>l>>r;
        if(type==1) {
          ll val; cin>>val;
          t.upd_divide(l,r,val);
        }else if(type==2){
          ll val; cin>>val;
          t.upd_set(l,r,val);
        }else cout<<t.query_sum(l,r)<<endl;
      }
    }
}

/*
 @ the bellow code is dedicated for range and range divide it is more faster divide then main struct 
 cause it is dedicated only for make divide very faster 
*/

struct STBeats_Light {
private:
    struct node {
        ll sum;
        ll min1;
        ll max1;
        ll lazy_add;
        node() : sum(0), min1(INF), max1(NINF), lazy_add(0) {}
    };
    int n;
    vector<node> tree;
    void pull(int v) {
        tree[v].sum = tree[2 * v].sum + tree[2 * v + 1].sum;
        tree[v].min1 = min(tree[2 * v].min1, tree[2 * v + 1].min1);
        tree[v].max1 = max(tree[2 * v].max1, tree[2 * v + 1].max1);
    }
    void apply_add(int v, int tl, int tr, ll x) {
        tree[v].sum += (tr - tl + 1) * x;
        tree[v].min1 += x;
        tree[v].max1 += x;
        tree[v].lazy_add += x;
    }
    void push(int v, int tl, int tr) {
        if (tree[v].lazy_add == 0) return;
        int mid = (tl + tr) >> 1;
        apply_add(2 * v, tl, mid, tree[v].lazy_add);
        apply_add(2 * v + 1, mid + 1, tr, tree[v].lazy_add);
        tree[v].lazy_add = 0;
    }
    void build_(int v, int tl, int tr, const vector<ll>& a) {
        // here write the build function from main STBeats
    }
    void upd_add_(int v, int tl, int tr, int ql, int qr, ll x) {
        if (qr < tl || tr < ql) return;
        if (ql <= tl && tr <= qr) {
            apply_add(v, tl, tr, x);
            return;
        }
        push(v, tl, tr);
        int mid = (tl + tr) >> 1;
        upd_add_(2 * v, tl, mid, ql, qr, x);
        upd_add_(2 * v + 1, mid + 1, tr, ql, qr, x);
        pull(v);
    }
    ll floor_div(ll a, ll b) {
        // here write the floor_div function from main STBeats   
    }
    void upd_divide_(int v, int tl, int tr, int ql, int qr, ll x) {
        if (qr < tl || tr < ql) return;
        if (ql <= tl && tr <= qr) {
            ll new_min = floor_div(tree[v].min1, x);
            ll new_max = floor_div(tree[v].max1, x);
            ll delta_min = new_min - tree[v].min1;
            ll delta_max = new_max - tree[v].max1;
            if (delta_min == delta_max) {
                apply_add(v, tl, tr, delta_min);
                return;
            }
        }
        if (tl == tr) {
            ll new_val = floor_div(tree[v].min1, x);
            tree[v].sum = tree[v].min1 = tree[v].max1 = new_val;
            return;
        }
        push(v, tl, tr);
        int mid = (tl + tr) >> 1;
        upd_divide_(2 * v, tl, mid, ql, qr, x);
        upd_divide_(2 * v + 1, mid + 1, tr, ql, qr, x);
        pull(v);
    }
    ll query_sum_(int v, int tl, int tr, int ql, int qr) {
        // here write the query_sum_ function from main STBeats
    }
    ll query_min_(int v, int tl, int tr, int ql, int qr) {
        // here write the query_min_ function from main STBeats
    }

public:
    STBeats_Light(int n_val) : n(n_val) { tree.resize(4 * n + 4); }
    void build(const vector<ll>& a) { build_(1, 1, n, a); }
    void upd_add(int ql, int qr, ll x) { upd_add_(1, 1, n, ql, qr, x); }
    void upd_divide(int ql, int qr, ll x) { upd_divide_(1, 1, n, ql, qr, x); }
    ll query_sum(int ql, int qr) { return query_sum_(1, 1, n, ql, qr); }
    ll query_min(int ql, int qr) { return query_min_(1, 1, n, ql, qr); }
};
