#include<bits/stdc++.h>
using namespace std;
void file(){
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}
#define ll long long 
const ll mx=2e5+123;
ll arr[mx],prop[mx*3],vis[mx*3];
void shift(ll node){
	prop[node*2]+=prop[node];
	prop[node*2+1]+=prop[node];
	vis[node*2]=vis[node*2+1]=1;
	prop[node]=vis[node]=0;
}
void T(ll node,ll l,ll r){
	if(l==r){
		prop[node]=arr[l];
		return;
	}
	ll mid=(l+r)/2;
	T(node*2,l,mid);
	T(node*2+1,mid+1,r);
}
void update(ll node,ll l,ll r,ll i,ll j,ll val){
	if(i>r || j<l) return;
	if(l>=i && r<=j) {
		prop[node]+=val;
		vis[node]=1;
		return;
	}
	ll mid=(l+r)/2;
	update(node*2,l,mid,i,j,val);
	update(node*2+1,mid+1,r,i,j,val);
}
ll query(ll node,ll l,ll r,ll i){
	if(l>i || r<i) return 0;
	if(l==i && r==i) return prop[node];
	if(vis[node]) shift(node);
	ll mid=(l+r)/2;
	ll right=query(node*2,l,mid,i);
	ll left=query(node*2+1,mid+1,r,i);
	return right+left;
}
int main(){
	file();
	ll n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>arr[i];
		T(1,1,n);
		while(q--){
			ll qs;
			cin>>qs;
			if(qs==1){
				ll l,r,u;
				cin>>l>>r>>u;
				update(1,1,n,l,r,u);
			}else{
				ll u;
				cin>>u;
				cout<<query(1,1,n,u)<<endl;
			}
		}
}