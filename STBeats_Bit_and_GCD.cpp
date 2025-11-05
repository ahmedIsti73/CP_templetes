#include"bits/stdc++.h"
using namespace std;
using ll=long long;
#define endl '\n'
const ll INF=1e18;
const ll NINF=-1e18;

struct STBeats_Bit {
private:
    struct node {
        ll sum;
        int len;
        ll all_and;
        ll all_or;
        ll max_val;
        ll min_val;
        ll lazy_set;

        node() : sum(0),len(0),all_and(~0LL),all_or(0LL),
                 max_val(NINF),min_val(INF),lazy_set(INF) {}
    };
    int n;
    vector<node> tree;
    node merge(const node& left,const node& right) {
        node res;
        res.sum=left.sum+right.sum;
        res.len=left.len+right.len;
        res.all_and=left.all_and & right.all_and;
        res.all_or=left.all_or | right.all_or;
        res.max_val=max(left.max_val,right.max_val);
        res.min_val=min(left.min_val,right.min_val);
        res.lazy_set=INF;
        return res;
    }
    void apply_set(int v,ll x) {
        tree[v].sum=tree[v].len*x;
        tree[v].all_and=x;
        tree[v].all_or=x;
        tree[v].max_val=x;
        tree[v].min_val=x;
        tree[v].lazy_set=x;
    }
    void push_down(int v,int tl,int tr) {
        if(tl==tr || tree[v].lazy_set==INF) return;
        apply_set(2*v,tree[v].lazy_set);
        apply_set(2*v+1,tree[v].lazy_set);
        tree[v].lazy_set=INF;
    }
    void build_(int v,int tl,int tr,const vector<ll>& a) {
        if(tl==tr) {
            tree[v].len=1;
            tree[v].sum=a[tl];
            tree[v].all_and=a[tl];
            tree[v].all_or=a[tl];
            tree[v].max_val=a[tl];
            tree[v].min_val=a[tl];
        }else {
            int mid=(tl+tr)>>1;
            build_(2*v,tl,mid,a);
            build_(2*v+1,mid+1,tr,a);
            tree[v]=merge(tree[2*v],tree[2*v+1]);
        }
    }
    void upd_or_(int v,int tl,int tr,int ql,int qr,ll x) {
        push_down(v,tl,tr);
        if(qr<tl || tr<ql) return;
        if((tree[v].all_and & x)==x) return;
        if(tl==tr) {
            apply_set(v,tree[v].sum | x);
            return;
        }
        int mid=(tl+tr)>>1;
        upd_or_(2*v,tl,mid,ql,qr,x);
        upd_or_(2*v+1,mid+1,tr,ql,qr,x);
        tree[v]=merge(tree[2*v],tree[2*v+1]);
    }
    void upd_and_(int v,int tl,int tr,int ql,int qr,ll x) {
        push_down(v,tl,tr);
        if(qr<tl || tr<ql) return;
        if((tree[v].all_or | x)==x) return;
        if(tl==tr) {
            apply_set(v,tree[v].sum & x);
            return;
        }
        int mid=(tl+tr)>>1;
        upd_and_(2*v,tl,mid,ql,qr,x);
        upd_and_(2*v+1,mid+1,tr,ql,qr,x);
        tree[v]=merge(tree[2*v],tree[2*v+1]);
    }
    void upd_set_(int v,int tl,int tr,int ql,int qr,ll x) {
        push_down(v,tl,tr);
        if(qr<tl || tr<ql) return;
        if(ql<=tl && tr<=qr) {
            apply_set(v,x);
            return;
        }
        int mid=(tl+tr)>>1;
        upd_set_(2*v,tl,mid,ql,qr,x);
        upd_set_(2*v+1,mid+1,tr,ql,qr,x);
        tree[v]=merge(tree[2*v],tree[2*v+1]);
    }
    ll query_sum_(int v,int tl,int tr,int ql,int qr) {
        if(qr<tl || tr<ql) return 0;
        push_down(v,tl,tr);
        if(ql<=tl && tr<=qr) return tree[v].sum;
        int mid=(tl+tr)>>1;
        return query_sum_(2*v,tl,mid,ql,qr) +
                query_sum_(2*v+1,mid+1,tr,ql,qr);
    }
    ll query_and_(int v,int tl,int tr,int ql,int qr) {
        if(qr<tl || tr<ql) return ~0LL;
        push_down(v,tl,tr);
        if(ql<=tl && tr<=qr) return tree[v].all_and;
        int mid=(tl+tr)>>1;
        return query_and_(2*v,tl,mid,ql,qr) &
                query_and_(2*v+1,mid+1,tr,ql,qr);
    }
    ll query_or_(int v,int tl,int tr,int ql,int qr) {
        if(qr<tl || tr<ql) return 0LL;
        push_down(v,tl,tr);
        if(ql<=tl && tr<=qr) return tree[v].all_or;
        int mid=(tl+tr)>>1;
        return query_or_(2*v,tl,mid,ql,qr) |
                query_or_(2*v+1,mid+1,tr,ql,qr);
    }
    ll query_max_(int v,int tl,int tr,int ql,int qr) {
        if(qr<tl || tr<ql) return NINF;
        push_down(v,tl,tr);
        if(ql<=tl && tr<=qr) return tree[v].max_val;
        int mid=(tl+tr)>>1;
        return max(query_max_(2*v,tl,mid,ql,qr) ,
                query_max_(2*v+1,mid+1,tr,ql,qr));
    }
    ll query_min_(int v,int tl,int tr,int ql,int qr) {
        if(qr<tl || tr<ql) return INF;
        push_down(v,tl,tr);
        if(ql<=tl && tr<=qr) return tree[v].min_val;
        int mid=(tl+tr)>>1;
        return min(query_min_(2*v,tl,mid,ql,qr) ,
                query_min_(2*v+1,mid+1,tr,ql,qr));
    }

public:
    STBeats_Bit(int n) : n(n) { tree.resize(4*n+4); }
    void build(const vector<ll>& a) { build_(1,1,n,a); }
    void upd_or(int ql,int qr,ll x) { upd_or_(1,1,n,ql,qr,x); }
    void upd_and(int ql,int qr,ll x) { upd_and_(1,1,n,ql,qr,x); }
    void upd_set(int ql,int qr,ll x) { upd_set_(1,1,n,ql,qr,x); }
    ll query_sum(int ql,int qr) { return query_sum_(1,1,n,ql,qr); }
    ll query_and(int ql,int qr) { return query_and_(1,1,n,ql,qr); }
    ll query_or(int ql,int qr) { return query_or_(1,1,n,ql,qr); }
    ll query_max(int ql,int qr) { return query_max_(1,1,n,ql,qr); }
    ll query_min(int ql,int qr) { return query_min_(1,1,n,ql,qr); }
};
int32_t main() {
    ios_base :: sync_with_stdio(0); cin.tie(0);

    int n,q; cin>>n>>q;
    vector<ll> a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    STBeats_Bit t(n);
    t.build(a);
}

/*
this code is for gcd and multiple update like cmax cmin add set 
*/

#include<bits/stdc++.h>

using namespace std;

const long long MX = 1e18;

struct node {
    long long max, max2, min, min2, sum, gcd, add = 0, set = 0, updmin = 0, updmax = 0;
    int cntmax, cntmin;
    node() {}
    node(long long x) {
        sum = max = min = x, cntmax = cntmin = 1;
        gcd = 0;
        max2 = -MX, min2 = MX;
    }
};

vector<node> t;
vector<long long> a;

void merge(node& res, node& a, node& b) {
    // max
    res.max = max(a.max, b.max);
    res.max2 = -MX;
    res.cntmax = 0;
    if (a.max == res.max) {
        res.cntmax += a.cntmax;
        res.max2 = max(res.max2, a.max2);
    } else {
        res.max2 = max(res.max2, a.max);
    }
    if (b.max == res.max) {
        res.cntmax += b.cntmax;
        res.max2 = max(res.max2, b.max2);
    } else {
        res.max2 = max(res.max2, b.max);
    }

    // min
    res.min = min(a.min, b.min);
    res.min2 = MX;
    res.cntmin = 0;
    if (a.min == res.min) {
        res.cntmin += a.cntmin;
        res.min2 = min(res.min2, a.min2);
    } else {
        res.min2 = min(res.min2, a.min);
    }
    if (b.min == res.min) {
        res.cntmin += b.cntmin;
        res.min2 = min(res.min2, b.min2);
    } else {
        res.min2 = min(res.min2, b.min);
    }

    //sum
    res.sum = a.sum + b.sum;

    //gcd
    res.gcd = __gcd(a.gcd, b.gcd);
    long long x = -1, y = -1;
    if (a.max2 != -MX && a.max2 != a.min) {
        x = a.max2;
    }
    if (b.max2 != -MX && b.max2 != b.min) {
        y = b.max2;
    }
    if (x != -1 && y != -1) {
        res.gcd = __gcd(res.gcd, abs(x - y));
    }
    for (long long z : {a.max, a.min, b.max, b.min}) {
        if (z == res.max) {
            continue;
        }
        if (z == res.min) {
            continue;
        }
        if (x != -1) {
            res.gcd = __gcd(res.gcd, abs(x - z));
        } else if (y != -1) {
            res.gcd = __gcd(res.gcd, abs(y - z));
        } else {
            x = z;
        }
    }
}

void push_add(int v, long long x) {
    if (t[v].set != 0) {
        t[v].set += x;
    } else {
        if (t[v].updmin != 0) {
            t[v].updmin += x;
        }
        if (t[v].updmax != 0) {
            t[v].updmax += x;
        }
        t[v].add += x;
    }
}

void push_max(int v, long long x) {
    if (t[v].set != 0) {
        t[v].set = min(t[v].set, x);
    } else if (t[v].updmin == 0 || x > t[v].updmin) {
        if (t[v].updmax == 0) {
            t[v].updmax = x;
        } else {
            t[v].updmax = min(t[v].updmax, x);
        }
    } else {
        t[v].set = x;
    }
}

void push_min(int v, long long x) {
    if (t[v].set != 0) {
        t[v].set = max(t[v].set, x);
    } else if (t[v].updmax == 0 || t[v].updmax > x) {
        if (t[v].updmin == 0) {
            t[v].updmin = x;
        } else {
            t[v].updmin = max(t[v].updmin, x);
        }
    } else {
        t[v].set = x;
    }
}

void push(int v, int l, int r) {
    if (t[v].set != 0) {
        if (l + 1 != r) {
            t[v * 2 + 1].set = t[v * 2 + 2].set = t[v].set;
        }
        t[v].max = t[v].min = t[v].set;
        t[v].cntmax = t[v].cntmin = r - l;
        t[v].sum = t[v].set * (long long) (r - l);
        t[v].add = t[v].set = t[v].gcd = t[v].updmin = t[v].updmax = 0;
        t[v].max2 = -MX, t[v].min2 = MX;
    }
    if (t[v].add != 0) {
        if (l + 1 != r) {
            push_add(v * 2 + 1, t[v].add);
            push_add(v * 2 + 2, t[v].add);
        }
        t[v].max += t[v].add;
        t[v].min += t[v].add;
        if (t[v].max2 != -MX) {
            t[v].max2 += t[v].add;
        }
        if (t[v].min2 != MX) {
            t[v].min2 += t[v].add;
        }
        t[v].sum += t[v].add * (long long) (r - l);
        t[v].add = 0;
    }
    if (t[v].updmax != 0) {
        if (l + 1 != r) {
            push_max(v * 2 + 1, t[v].updmax);
            push_max(v * 2 + 2, t[v].updmax);
        }
        if (t[v].max == t[v].min) {
            if (t[v].updmax < t[v].max) {
                t[v].sum = t[v].updmax * (long long) (r - l);
                t[v].max = t[v].min = t[v].updmax;
            }
        } else {
            if (t[v].updmax < t[v].max) {
                t[v].sum -= (t[v].max - t[v].updmax) * (long long) t[v].cntmax;
                if (t[v].max == t[v].min2) {
                    t[v].min2 = t[v].updmax;
                }
                t[v].max = t[v].updmax;
            }
        }
        t[v].updmax = 0;
    }
    if (t[v].updmin != 0) {
        if (l + 1 != r) {
            push_min(v * 2 + 1, t[v].updmin);
            push_min(v * 2 + 2, t[v].updmin);
        }
        if (t[v].max == t[v].min) {
            if (t[v].updmin > t[v].min) {
                t[v].sum = t[v].updmin * (long long) (r - l);
                t[v].max = t[v].min = t[v].updmin;
            }
        } else {
            if (t[v].updmin > t[v].min) {
                t[v].sum += (t[v].updmin - t[v].min) * (long long) t[v].cntmin;
                if (t[v].min == t[v].max2) {
                    t[v].max2 = t[v].updmin;
                }
                t[v].min = t[v].updmin;
            }
        }
        t[v].updmin = 0;
    }
}

void build(int v, int l, int r) {
    if (l + 1 == r) {
        t[v] = node(a[l]);
        return;
    }
    int m = (l + r) / 2;
    build(v * 2 + 1, l, m);
    build(v * 2 + 2, m, r);
    merge(t[v], t[v * 2 + 1], t[v * 2 + 2]);
}

void updatemin(int v, int l, int r, int l1, int r1, long long x) {
    push(v, l, r);
    if (l1 >= r || l >= r1 || t[v].max <= x) return;
    if (l1 <= l && r <= r1 && t[v].max2 < x) {
        t[v].updmax = x;
        push(v, l, r);
        return;
    }
    int m = (l + r) / 2;
    updatemin(v * 2 + 1, l, m, l1, r1, x);
    updatemin(v * 2 + 2, m, r, l1, r1, x);
    merge(t[v], t[v * 2 + 1], t[v * 2 + 2]);
}

void updatemax(int v, int l, int r, int l1, int r1, long long x) {
    push(v, l, r);
    if (l1 >= r || l >= r1 || t[v].min >= x) return;
    if (l1 <= l && r <= r1 && t[v].min2 > x) {
        t[v].updmin = x;
        push(v, l, r);
        return;
    }
    int m = (l + r) / 2;
    updatemax(v * 2 + 1, l, m, l1, r1, x);
    updatemax(v * 2 + 2, m, r, l1, r1, x);
    merge(t[v], t[v * 2 + 1], t[v * 2 + 2]);
}

void updateset(int v, int l, int r, int l1, int r1, long long x) {
    push(v, l, r);
    if (l1 >= r || l >= r1) return;
    if (l1 <= l && r <= r1) {
        t[v].set = x;
        push(v, l, r);
        return;
    }
    int m = (l + r) / 2;
    updateset(v * 2 + 1, l, m, l1, r1, x);
    updateset(v * 2 + 2, m, r, l1, r1, x);
    merge(t[v], t[v * 2 + 1], t[v * 2 + 2]);
}

void updateadd(int v, int l, int r, int l1, int r1, long long x) {
    push(v, l, r);
    if (l1 >= r || l >= r1) return;
    if (l1 <= l && r <= r1) {
        t[v].add = x;
        push(v, l, r);
        return;
    }
    int m = (l + r) / 2;
    updateadd(v * 2 + 1, l, m, l1, r1, x);
    updateadd(v * 2 + 2, m, r, l1, r1, x);
    merge(t[v], t[v * 2 + 1], t[v * 2 + 2]);
}

long long getsum(int v, int l, int r, int l1, int r1) {
    push(v, l, r);
    if (l1 >= r || l >= r1) return 0ll;
    if (l1 <= l && r <= r1) return t[v].sum;
    int m = (l + r) / 2;
    return getsum(v * 2 + 1, l, m, l1, r1) + getsum(v * 2 + 2, m, r, l1, r1);
}

long long getmin(int v, int l, int r, int l1, int r1) {
    push(v, l, r);
    if (l1 >= r || l >= r1) return MX;
    if (l1 <= l && r <= r1) return t[v].min;
    int m = (l + r) / 2;
    return min(getmin(v * 2 + 1, l, m, l1, r1), getmin(v * 2 + 2, m, r, l1, r1));
}

long long getmax(int v, int l, int r, int l1, int r1) {
    push(v, l, r);
    if (l1 >= r || l >= r1) return -MX;
    if (l1 <= l && r <= r1) return t[v].max;
    int m = (l + r) / 2;
    return max(getmax(v * 2 + 1, l, m, l1, r1), getmax(v * 2 + 2, m, r, l1, r1));
}

long long getgcd(int v, int l, int r, int l1, int r1) {
    push(v, l, r);
    if (l1 >= r || l >= r1) return 0ll;
    if (l1 <= l && r <= r1) {
        long long res = __gcd(t[v].max, t[v].min);
        if (t[v].max2 != t[v].min && t[v].max2 != -MX) {
            res = __gcd(res, t[v].gcd);
            res = __gcd(res, t[v].max2);
        }
        return res;
    }
    int m = (l + r) / 2;
    return __gcd(getgcd(v * 2 + 1, l, m, l1, r1), getgcd(v * 2 + 2, m, r, l1, r1));
}
