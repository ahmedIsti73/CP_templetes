const int mod=1e8+7;
/*
 * Note : If MOD is constant then use (const int mod=Given mod)
 * and remove mod from function variable declare it will make it 
 * 5-10X faster if no need __int128 then remove it from mul more fast
*/
inline ll mul(ll a,ll b,ll mod) {
	return (__int128)a*b%mod;
}
// Works for any modulo m
pair<ll,ll> FIB(ll n,ll mod) {
	if(!n) return {0,1};
	ll a=0,b=1;
	for(int i=63-__builtin_clzll(n);i>=0;i--) {
		ll c=mul(a,(2*b%mod-a+mod)%mod,mod);	// F(2k) 
		ll d=(mul(a,a,mod)+mul(b,b,mod))%mod;	// F(2k+1) 
		if((n>>i)&1) {
			a=d;		 // F(2k+1)
			b=(c+d)%mod; // F(2k+2)
		}else {
			a=c;		// F(2k) 
			b=d;		// F(2k+1)
		}
	}
	return {a,b};
}
ll kth(ll a,ll b,ll n,ll mod) {
	if(mod==1) return 0;
	if(!n) return a%mod;
	if(n==1) return b%mod;
	pair<ll,ll> fibs=FIB(n-1,mod); // 
	return (mul(a,fibs.F,mod) + mul(b,fibs.S,mod))%mod;
}

void GLITCH_() {
	ll n; cin>>n;
	cout<<kth(0,1,n,mod)<<endl;
}
