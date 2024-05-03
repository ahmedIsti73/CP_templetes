#include<bits/stdc++.h>
using namespace std;
#define optimize()                 \
    ios_base ::sync_with_stdio(0); \
    cin.tie(0);                    \
    cout.tie(0);
void file(){
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}
#define endl '\n'
#define ll long long int
#define ld long double
#define ha cout << "YES" << endl
#define na cout << "NO" << endl
#define na1 cout << "-1" << endl
#define el cout<<endl;
#define lup(z, n) for (int i = z; i < n; ++i)
#define lup1(z, n) for (int i = z; i <= n; ++i)
#define MAX (ll)(1LL << 31) - 1
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define IS to_string
#define SI stoi
#define popcnt __builtin_popcountll
#define clz __builtin_clz
#define um unordered_map
#define mem(arr,x) memset(arr,x,sizeof arr)    

const ll p=31;
const ll N=1e6+10;
const ll mod=1000000289;
ll powerr(ll a,ll b){
	ll r=1;
	while(b){
		if(b%2) r=((r%mod) *(a%mod))%mod;
		a=((a%mod)*(a%mod))%mod;
		b/=2;
	}
	return r;
}
ll add(ll a,ll b){return ((a%mod)+(b%mod)+mod)%mod;}
ll substract(ll a,ll b){return ((a%mod)-(b%mod)+mod)%mod;}
ll mult(ll a,ll b) {return ((a%mod)*(b%mod))%mod;}
ll fn(char ch){if(islower(ch)) return ch-'a'+1;if(isupper(ch)) return ch-'A'+1;return ch-'0'+1;}
vector<ll> pw(N+10),h(N+10),inv(N+10);
void precal(){
	pw[0]=1;
	for(int i=1;i<N;i++) pw[i]=mult(pw[i-1],p);
	ll pw_inv=powerr(p,mod-2);
	inv[0]=1;
	for(int i=1;i<N;i++) inv[i]=mult(inv[i-1],pw_inv);	
}
void build(string s){
	ll n=s.size();
	for(int i=0;i<n;i++){
		ll a=0,b;
		if(i) a=h[i-1];
		b=mult(pw[i],fn(s[i]));
		h[i]=add(a,b);
	}
}
ll gethash(ll l,ll r){
	ll res=h[r];
	if(l) res=substract(res,h[l-1]);
	res =mult(res,inv[l]);
	return res;
}
int main(){
	file();
	optimize();
	precal();
    ll tt;
    cin>>tt;
    for(int ttt=1;ttt<=tt;ttt++){
    string s,t;
	cin>>s>>t;
	ll n=s.size(),m=t.size();
	build(t);
	ll x=gethash(0,m-1);
	// cout<<x<<endl;
	build(s);
	vector<ll> ans;
	for(int i=0;i+m-1<n;i++){
        // cout<<gethash(i,i+m-1)<<endl;
		if(x==gethash(i,i+m-1)){
			ans.PB(i+1);
		}
	}
    if(ans.size()>0)
    {
        cout<<ans.size()<<endl;
    for(auto u:ans) cout<<u<<' '; cout<<endl;
    }else{
        cout<<"Not Found"<<endl;
    }
    }
}
