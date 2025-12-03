// baby step - giant step
// returns minimum integer x such that a^x = b (mod m)
ll discrete_log(ll a,ll b,ll m) {
	a%=m, b%=m;
	ll val=1%m;
	for(int i=0;i<100;i++) {
		if (val==b) {
            //if (!(a==0 && i==0)) // only delete this line if there is no special case like 0^0=0
				return i;
        }
        val=(val*(__int128)a)%m;
	}
	ll k=1,add=0,g;
	while((g=__gcd(a,m))>1) {
		if(b%g) return -1;
		b/=g, m/=g, ++add;
		k=(k*(__int128)a/g)%m;
	}
	// Solve k * a^x' = b (mod m)
	ll n=sqrt(m)+1;
	ll an=1;
	for(ll i=0;i<n;++i) {
		an=(an*(__int128)a)%m;
	}

	gp_hash_table<ll,ll> vals;
	// Baby Steps Store b * a^q
	for(ll q=0,cur=b;q<=n;++q) {
		vals[cur]=q;
		cur=(cur*(__int128)a)%m;
	}
	// Giant Steps Check k * (a^n)^p
	for(ll p=1,cur=k;p<=n;++p) {
		cur=(cur*(__int128)an)%m;
		if(vals.find(cur) != vals.end()) {
			ll ans=n*p-vals[cur]+add;
			return ans;
		}
	}
	return -1;
}
