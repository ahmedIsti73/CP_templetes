#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long int
#define F               first
#define S               second
const ll p=65;
const ll N=1e6+10;
pair<ll,ll> mod={1e9+7,1e9+9};
// ---------------------random mod generatior ------------------------
vector<ll>pr = {1000000007, 1000000009, 1000000021, 1000000033, 1000000087, 1000000093, 1000000097, 1000000103, 1000000123, 1000000181, 1000000207, 1000000223, 1000000241, 1000000271, 1000000289};

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
long long get_random(){
    return (long long)(rng());
}
long long get_random_in_range(long long L, long long R){
    long long rndm = get_random();
    return L + (rndm % (R - L + 1));
}
void randommod(){
    ll i = get_random_in_range(0, 14);
    mod.F = pr[i];
    pr.erase(pr.begin()+i);
    i = get_random_in_range(0, 13);
    mod.S = pr[i];
}
//------------------------------end-----------------------------------
ll powerr(ll a,ll b,ll mod){
	ll r=1;
	while(b){
		if(b%2) r=((r%mod) *(a%mod))%mod;
		a=((a%mod)*(a%mod))%mod;
		b/=2;
	}
	return r;
}
ll add(ll a,ll b,ll mod){return ((a%mod)+(b%mod)+mod)%mod;}
ll substract(ll a,ll b,ll mod){return ((a%mod)-(b%mod)+mod)%mod;}
ll mult(ll a,ll b,ll mod) {return ((a%mod)*(b%mod))%mod;}
ll fn(char ch){if(islower(ch)) return ch-'a'+1;if(isupper(ch)) return ch-'A'+1;return ch-'0'+1;}

pair<ll,ll> pw[N+10],h[N+10],inv[N+10];
void precal(){
	pw[0].F=pw[0].S=1;
	for(int i=1;i<N;i++){
		pw[i].F=mult(pw[i-1].F,p,mod.F);
		pw[i].S=mult(pw[i-1].S,p,mod.S);
	} 
	ll pw_inv1=powerr(p,mod.F-2,mod.F);
	ll pw_inv2=powerr(p,mod.S-2,mod.S);
	inv[0].F=inv[0].S=1;
	for(int i=1;i<N;i++){
		inv[i].F=mult(inv[i-1].F,pw_inv1,mod.F);
		inv[i].S=mult(inv[i-1].S,pw_inv2,mod.S);
	}	
}
void build(string s){
	ll n=s.size();
	for(int i=0;i<n;i++){
		ll a1=0,b1,a2=0,b2;
		if(i){
			a1=h[i-1].F;
			a2=h[i-1].S;
		}
		b1=mult(pw[i].F,fn(s[i]),mod.F);
		b2=mult(pw[i].S,fn(s[i]),mod.S);
		h[i].F=add(a1,b1,mod.F);
		h[i].S=add(a2,b2,mod.S);
	}
}
pair<ll,ll> gethash(ll l,ll r){
	ll res1=h[r].F;
	ll res2=h[r].S;
	if(l){
		res1=substract(res1,h[l-1].F,mod.F);
		res2=substract(res2,h[l-1].S,mod.S);
	}
	res1 =mult(res1,inv[l].F,mod.F);
	res2 =mult(res2,inv[l].S,mod.S);
	return {res1,res2};
}

int main(){
	// randommod();
	precal();

    string s,t;
	cin>>s>>t;
	ll k; cin>>k;
	ll n=s.size(),m=t.size();
	ll mp[28]={};
	for(int i=0;i<m;i++){
		if(t[i]=='0'){
			mp[i]=1;
		}
	}
	ll pre[n+2]={};
	if(mp[s[0]-'a']==1) pre[0]=1;
	for(int i=1;i<n;i++){
		pre[i]=pre[i-1]+mp[s[i]-'a'];
	}
	// for(int i=0;i<n;i++) cout<<pre[i]<<' '; cout<<endl;
	build(s);
	set<pair<ll,ll>>temp;
	ll cnt=0;
	for(int i=0;i<n;i++){
		for(int j=i;j<n;j++){
			ll q=pre[j];
			if(i)q-=pre[i-1];
			if(q<=k){
				pair<ll,ll> x=gethash(i,j);
				// for(int a=j;a<=j+i-1;a++) cout<<s[a]; cout<<endl;
				temp.insert(x);
			}
		}
	}
	cout<<temp.size()<<endl;
}
