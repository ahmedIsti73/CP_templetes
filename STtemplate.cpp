// bismillahir rahmanir rahim 
#include<bits/stdc++.h> 
using namespace std;
void file(){
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}
// segment tree
#define ll long long
const ll mx=3e5+123;
ll arr[mx],T[mx*3];
void ST(ll node,ll start,ll end){ // O(n log2 n)
	if(start==end){
		T[node]=arr[start];
		return;
	}
	ll mid=(start+end)/2;
	ST(node*2,start,mid);
	ST(node*2+1,mid+1,end);
	T[node]=T[node*2]+T[node*2+1];
}
void update(ll node,ll start,ll end,ll i,ll value){ // O(log n)
	if(start>i || end<i) return;
	if(start==i && end==i){
        T[node]=value;
        return;
    }
	ll mid=(start+end)/2;
	update(node*2,start,mid,i,value);
	update(node*2+1,mid+1,end,i,value);
	T[node]=T[node*2]+T[node*2+1];
}
ll query(ll node,ll start,ll end,ll i,ll j){ // O(log2 n)
	if(start>j || end<i) return 0;
	if(i<=start && end<=j) return T[node];
	ll mid=(start+end)/2;
	ll leftsum=query(node*2,start,mid,i,j);
	ll rightsum=query(node*2+1,mid+1,end,i,j);
	return leftsum+rightsum;
}
int main(){
	file();
	ll n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>arr[i];
		ST(1,1,8);
	for(int i=1;i<=15;i++) cout<<T[i]<<' '; cout<<endl;	
	update(1,1,8,3,11);
	for(int i=1;i<=15;i++) cout<<T[i]<<' '; cout<<endl;	
}