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
