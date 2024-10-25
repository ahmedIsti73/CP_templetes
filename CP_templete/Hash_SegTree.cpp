#include<bits/stdc++.h>
using namespace std;
#define optimize()                 \
    ios_base ::sync_with_stdio(0); \
    cin.tie(0);                    \
    cout.tie(0);
#define endl '\n'
#define ll long long int
#define F               first
#define S               second
const ll p=137;
const ll N=2e5+10;
const pair<ll,ll> mod={127657753,987654319};
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

pair<ll,ll> pw[N+10],inv[N+10];
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
struct hashing {
    vector<pair<ll,ll>> t;
    string s;
    hashing(){}
    hashing(string _s){
        s=_s;
        ll n=s.size();
        t.resize(n*4);
    } 
    void build(int node,int l,int r){
        if(l==r){
            t[node].F=mult(pw[l].F,fn(s[l]),mod.F);
            t[node].S=mult(pw[l].S,fn(s[l]),mod.S);
            return;
        }
        ll mid=(l+r)>>1;
        build(node*2,l,mid);
        build(node*2+1,mid+1,r);
        t[node].F=add(t[node*2].F,t[node*2+1].F,mod.F);
        t[node].S=add(t[node*2].S,t[node*2+1].S,mod.S);
    }
    void upd(int node,int l,int r,int i,char value){
        if(l>i || r<i) return;
        if(l==i && r==i){
            t[node].F=mult(pw[i].F,fn(value),mod.F);
            t[node].S=mult(pw[i].S,fn(value),mod.S);
            return;
        }
        ll mid=(l+r)>>1;
        upd(node*2,l,mid,i,value);
        upd(node*2+1,mid+1,r,i,value);
        t[node].F=add(t[node*2].F,t[node*2+1].F,mod.F);
        t[node].S=add(t[node*2].S,t[node*2+1].S,mod.S);
    }
    pair<ll,ll> query(int node,int l,int r,int i,int j){
        if(l>j || r<i) return {0,0};           /// check here
        if(i<=l && r<=j) return t[node];
        ll mid=(l+r)>>1;
        pair<ll,ll> x=query(node*2,l,mid,i,j);
        pair<ll,ll> y=query(node*2+1,mid+1,r,i,j);
        return {add(x.F,y.F,mod.F),add(x.S,y.S,mod.S)};
    }
    pair<ll,ll> get_hash(int l,int r,int n){
        pair<ll,ll> ck=query(1,0,n-1,l,r);
        ck.F=mult(ck.F,inv[l].F,mod.F);
        ck.S=mult(ck.S,inv[l].S,mod.S);
        return ck;
    }
}a,b;
int main(){
	optimize();
	// randommod();
	precal();
    ll n,q; cin>>n>>q;
    string s; cin>>s;
    a = hashing(s);
    a.build(1,0,n-1);
    reverse(s.begin(),s.end());
    b= hashing(s);
    b.build(1,0,n-1);
    while(q--){
        ll i; cin>>i;
        if(i==1){
            ll ind; char c; cin>>ind>>c;
            --ind;
            a.upd(1,0,n-1,ind,c);
            b.upd(1,0,n-1,n-ind-1,c);
        }else{
            ll l,r; cin>>l>>r;
            --l,--r;
            if(a.get_hash(l,r,n)==b.get_hash(n-r-1,n-l-1,n))
            cout<<"YES"<<endl;
            else cout<<"NO"<<endl;
        }
    }
}
