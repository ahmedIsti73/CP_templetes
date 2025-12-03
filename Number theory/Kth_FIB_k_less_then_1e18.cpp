/*
 * Note : If MOD is constant then use (const int mod=Given mod)
 * and remove mod from function variable declare it will make it 
 * 5-10X faster if no need __int128 then remove it from mul more fast
 * For prefix sum f(n+2)-(a+b)
 * sum of f(0)^2+f(1)^2+..+f(n)^2 = f(n)*f(n+1)
 * gcd(f(n),f(m)) = f(gcd(n,m))
 * odd index sum = f(2n)
 * evne index sum f(2n+1)-1
 * THEOREM: Every positive integer N can be uniquely represented as the sum 
    of non-consecutive Fibonacci numbers. (i.e., If you use F[i], you cannot use F[i-1] or F[i+1]).

 2. SEQUENCE: Uses Fib starting 1, 2, 3, 5, 8... (Index: F[0]=1, F[1]=2...)
 3. EXAMPLE: N = 100
    - Largest Fib <= 100 is 89. (Rem = 11)
    - Largest Fib <= 11 is 8.   (Rem = 3)
    - Largest Fib <= 3 is 3.    (Rem = 0)
    -> 100 = 89 + 8 + 3
*/
const int mod=1e8+7;
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
