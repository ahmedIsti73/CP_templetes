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
    ll t[N*3];
    ST(){
        memset(t,0,sizeof t);
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
int main(){
optimize();  
#ifndef ONLINE_JUDGE
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
#endif
    for(int i=1;i<=6;i++) cin>>arr[i];
    t.build(1,1,6);
    cout<<t.query(1,1,6,2,5)<<endl;
    t.upd(1,1,6,3,20);
    cout<<t.query(1,1,6,2,5)<<endl;
}