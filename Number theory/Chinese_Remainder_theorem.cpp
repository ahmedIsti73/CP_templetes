#include "bits/stdc++.h"
using namespace std;

using ll=long long;

ll extended_euclid(ll a,ll b,ll &x,ll &y) { // ax+by=gcd(a,b)
	if(!b) {
		x=1,y=0;
		return a;
	}
	ll x1,y1;
	ll d=extended_euclid(b,a%b,x1,y1);
	x=y1;
	y=x1-y1*(a/b);
	
	return d;
}
/** Works for non-coprime moduli.
 Returns {-1,-1} if solution does not exist or input is invalid.
 Otherwise, returns {x,L}, where x is the solution unique to mod L
*/
pair<ll,ll> CRT(vector<ll>A, vector<ll>M) {
	if(A.size()!=M.size()) return {-1,-1};
	
	int n=A.size();
	ll a1=A[0];
	ll m1=M[0];
	
	for(int i=1;i<n;i++) {
		ll a2=A[i];
		ll m2=M[i];
		ll g=__gcd(m1,m2);
		if(a1%g != a2%g) return {-1,-1};
		// Marge two equation 
		ll p,q, d=extended_euclid(m1/g,m2/g,p,q);
		ll mod=m1/g*m2; // LCM of m1,m2
		ll x = ((__int128)a1 * (m2 / g) * q + (__int128)a2 * (m1 / g) * p) % mod;
		
		a1=(x+mod)%mod;
		m1=mod;
	}
	return {a1,m1};
}

int32_t main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	vector<ll> A,M;
	pair<ll,ll> ans=CRT(A,M);
}
