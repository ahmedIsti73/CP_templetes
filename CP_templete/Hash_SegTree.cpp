#include"bits/stdc++.h"
using namespace std;
using ll = long long; using pll = pair<ll,ll>;
#define F   first
#define S   second
const ll p=137;     const ll N=2e5+10; // check range
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
// ll fn(ll a[i]) return a[i]; //for integer hash

pair<ll,ll> pw[N+10],inv[N+10],inv_p_minus1;
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
    inv_p_minus1 = {
        powerr(p-1, mod.F-2, mod.F),
        powerr(p-1, mod.S-2, mod.S)
    };
}
struct hashing {
    vector<pair<ll,ll>> t;
    vector<char>lazy; // lazy of integer for integer hash 
    string s; // integer hash make vector<ll> a
    hashing(){}
    hashing(string _s){
        s=_s;
        ll n=s.size();
        t.resize(n*4);
        lazy.resize(n*4,'?');
    }
    inline void push(int node,int l,int r){
        if(lazy[node]=='?') return;
        ll len=(r-l+1);
        ll sum1 = mult(mult(substract(pw[len].F, 1, mod.F), inv_p_minus1.F, mod.F), pw[l].F, mod.F);
        ll sum2 = mult(mult(substract(pw[len].S, 1, mod.S), inv_p_minus1.S, mod.S), pw[l].S, mod.S);

        t[node].F = mult(sum1, fn(lazy[node]), mod.F);
        t[node].S = mult(sum2, fn(lazy[node]), mod.S);
        if(l!=r){
            lazy[node*2]=lazy[node*2+1]=lazy[node];
        }
        lazy[node]='?';
    }
    inline void here(int node){
        t[node].F=add(t[node*2].F,t[node*2+1].F,mod.F);
        t[node].S=add(t[node*2].S,t[node*2+1].S,mod.S);
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
        here(node);
    }
    void upd(int node,int l,int r,int i,int j,char value){
        push(node,l,r);
        if(l>j || r<i) return;
        if(i<=l && r<=j){
            lazy[node]=value;
            push(node,l,r);
            return;
        }
        ll mid=(l+r)>>1;
        upd(node*2,l,mid,i,j,value);
        upd(node*2+1,mid+1,r,i,j,value);
        here(node);
    }
    pair<ll,ll> query(int node,int l,int r,int i,int j){
        push(node,l,r);
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
}a;
int main(){
    ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	precal();
    ll n,m,x; cin>>n>>m>>x;
    ll q=m+x;
    string s; cin>>s;
    a = hashing(s);
    a.build(1,0,n-1);
    while(q--){
        ll i; cin>>i;
        if(i==1){
            ll l,r; char c; cin>>l>>r>>c; l--,r--;
            a.upd(1,0,n-1,l,r,c);
        }else{
            ll l,r,d; cin>>l>>r>>d;
            --l,--r;
            if(d==(r-l+1) || a.get_hash(l,r-d,n)==a.get_hash(l+d,r,n)) cout<<"YES"<<endl;
            else cout<<"NO"<<endl;
        }
    }
}
