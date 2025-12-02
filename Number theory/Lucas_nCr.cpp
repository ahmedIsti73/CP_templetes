ll power(ll base,ll exp,ll mod) {
	ll res=1;
	base%=mod;
	while(exp>0) {
		if(exp%2==1) res=(res*base)%mod;
		base=(base*base)%mod;
		exp/=2;
	}
	return res;
}
// Use this for simple primes like 3,5,7..
ll nCr(ll n,ll r,ll p) {
	if(r<0 || r>n) return 0;
	if(!r || r==n) return 1;
	if(r>n/2) r=n-r;
	ll num=1;
	ll den=1;
	for(ll i=1;i<=r;i++) {
		num=(num*(n-i+1))%p;
		den=(den*i)%p;
	}
	return (num*power(den,p-2,p))%p;
}
// Use this to calculate nCr % p when n & r is huge p is small 
ll lucas(ll n,ll r,ll p) {
	if(!r) return 1;
	return (lucas(n/p, r/p, p) * nCr(n%p, r%p, p)) %p;
}
//---> billow part use to calcuate nCr if mod is p^k
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
ll inverse_pk(ll n,ll mod) {
	ll x,y;
	extended_euclid(n,mod,x,y);
	return (x%mod+mod)%mod;
}
ll fact_no_p(ll n,ll p,ll pk) {
	if(!n) return 1;
	ll ans=1;
	for(ll i=1;i<=pk;i++) {
		if(i%p) ans=(ans*i)%pk;
	}	
	ans=power(ans,n/pk,pk);
	for(ll i=1;i<=n%pk;i++) {
		if(i%p) ans=(ans*i)%pk;
	}
	return (ans*fact_no_p(n/p,p,pk))%pk;
}
ll count_p(ll n,ll p) {
	ll ans=0;
	while(n) {
		ans+=n/p;
		n/=p;
	}
	return ans;
}
// nCr % p^k
// Use this for cases like 27 (3^3), 25 (5^2)....
// pk=p^k
ll nCr_pk(ll n,ll r,ll p,ll pk) {
	if(r<0 || r>n) return 0;
	ll num=fact_no_p(n,p,pk);
	ll den1=fact_no_p(r,p,pk);
	ll den2=fact_no_p(n-r,p,pk);
	ll ans=(num*inverse_pk(den1,pk))%pk;
	ans=(ans*inverse_pk(den2,pk))%pk;
	ll pow_p=count_p(n,p)-count_p(r,p)-count_p(n-r,p);
	ans=(ans*power(p,pow_p,pk))%pk;
	
	return ans;
}
