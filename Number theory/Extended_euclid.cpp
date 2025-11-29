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
ll inverse(ll a,ll m) {
	ll x,y; 
	ll g=extended_euclid(a,m,x,y);
	if(g!=1) return -1;
	return (x%m+m)%m;
}
int main() {
	ll a,b; cin>>a>>b;
	ll x,y, gc=extended_euclid(a,b,x,y);
}
