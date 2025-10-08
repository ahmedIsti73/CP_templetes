struct ST{
    int n;            
    vector<int> t,lazy,arr; 
    void init(int n) {
        this->n=n;
        t.assign(3*n+5,0); 
        lazy.assign(3*n+5,0);
        arr.assign(n+5,0);
    }
    inline void push(int node,int l,int r){
        if(!lazy[node]) return;
        t[node]+=lazy[node]*(r-l+1); // check here
        if(l!=r){
            lazy[node*2]+=lazy[node];
            lazy[node*2+1]+=lazy[node];
        }
        lazy[node]=0;
    }
    inline void here(int node){
        t[node]=t[node*2]+t[node*2+1];  // check here
    }
    void build(int node,int l,int r){
        lazy[node]=0;
        if(l==r){
            t[node]=arr[l];
            return;
        }
        ll mid=(l+r)>>1;
        build(node*2,l,mid);
        build(node*2+1,mid+1,r);
        here(node);
    }
    void upd(int node,int l,int r,int i,int j,int value){
        push(node,l,r);
        if(l>j || r<i) return;
        if(i<=l && r<=j){
            lazy[node]+=value; // check here
            push(node,l,r);
            return;
        }
        ll mid=(l+r)>>1;
        upd(node*2,l,mid,i,j,value);
        upd(node*2+1,mid+1,r,i,j,value);
        here(node);
    }
    ll query(int node,int l,int r,int i,int j){
        push(node,l,r);
        if(l>j || r<i) return 0;           /// check here
        if(i<=l && r<=j) return t[node];
        ll mid=(l+r)>>1;
        return query(node*2,l,mid,i,j)+query(node*2+1,mid+1,r,i,j); // check here
    }
}t;
