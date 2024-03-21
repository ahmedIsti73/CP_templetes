#include<bits/stdc++.h>
using namespace std;
#define optimize()             \
ios_base ::sync_with_stdio(0); \
cin.tie(0);                    \
cout.tie(0);
#define ll long long 
const int N=2e5+123;
ll arr[N];
struct ST{
    ll t[N*3],lazy[N*3];
    ST(){
        memset(t,0,sizeof t);
        memset(lazy,0,sizeof lazy);
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
int main(){
optimize();  
#ifndef ONLINE_JUDGE
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
#endif
    for(int i=1;i<=6;i++) cin>>arr[i];
    t.build(1,1,6);
    cout<<t.query(1,1,6,2,5)<<endl;
    t.upd(1,1,6,3,4,10);
    cout<<t.query(1,1,6,2,5)<<endl;
}