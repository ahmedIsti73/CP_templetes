#define ll long long 
struct ST{
    int n;            
    vector<int> t,arr; 
    void init(int n) {
        this->n=n;
        t.assign(4 * n + 5, 0); 
        arr.assign(n+5,0);
    }
    inline void here(int node){
        t[node]=t[node*2]+t[node*2+1];  // check here
    }
    void build(int node,int l,int r){
        if(l==r){
            t[node]=arr[l];
            return;
        }
        ll mid=(l+r)>>1;
        build(node*2,l,mid);
        build(node*2+1,mid+1,r);
        here(node);
    }
    void upd(int node,int l,int r,int i,int value){
        if(l>i || r<i) return;
        if(l==i && r==i){
            t[node]+=value; // chack here
            return;
        }
        ll mid=(l+r)>>1;
        upd(node*2,l,mid,i,value);
        upd(node*2+1,mid+1,r,i,value);
        here(node);
    }
    ll query(int node,int l,int r,int i,int j){
        if(l>j || r<i) return 0;           /// check here
        if(i<=l && r<=j) return t[node];
        ll mid=(l+r)>>1;
        return query(node*2,l,mid,i,j)+query(node*2+1,mid+1,r,i,j); // check here
    }
}t;
