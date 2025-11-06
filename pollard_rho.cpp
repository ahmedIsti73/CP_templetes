// this is the topic to find prime fact of a big number 
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rand(ll n) { return rng() % (n - 2) + 1; }
ll modMul(ll a,ll b,ll mod) {
    return (__int128)a*b%mod;
}
ll modPower(ll base,ll exp,ll mod) {
    ll res=1;
    base%=mod;
    while(exp>0) {
        if(exp%2==1) res=modMul(res,base,mod);
        base=modMul(base,base,mod);
        exp/=2;
    }
    return res;
}
ll gcd(ll a,ll b) {
    while(b) {
        a%=b;
        swap(a,b);
    }
    return a;
}
const int MAX_SIEVE=1000001;
vector<int> spf(MAX_SIEVE);
void init_sieve() {
    vector<int> primes;
    for(int i=2;i<MAX_SIEVE;++i) {
        if(!spf[i]) {
            spf[i]=i;
            primes.PB(i);
        }
        for(int p:primes) {
            if(i*(ll)p>=MAX_SIEVE) break;
            spf[i*p]=p;
            if(!(i%p)) break;
        }
    }
}
bool MillerRabin(ll n,ll a,ll d,int s) {
    ll x=modPower(a,d,n);
    if(x==1 || x==n-1) return true;
    for(int r=1;r<s;r++) {
        x=modMul(x,x,n);
        if(x==1) return false;
        if(x==n-1) return true;
    }
    return false;
}
bool isPrime(ll n) {
    if(n<=1) return false;
    if(n<MAX_SIEVE) return spf[n]==n;
    if(n==2 || n==3) return true;
    if(!(n%2)) return false;
    ll d=n-1;
    int s=0;
    while(!(d%2)) {
        d/=2;
        s++;
    }
    vector<ll> witnesses={2,3,5,7,11,13,17,19,23,29,31,37};
    for(ll a:witnesses) {
        if(n==a) return true;
        if(!(MillerRabin(n,a,d,s))) return false;
    }
    return true;
}
ll pollard_rho(ll n) {
    auto f =[&](ll x,ll c) {
        return (modMul(x,x,n)+c)%n;
    };
    ll c=rand(n);
    ll tortoise=2,hare=2,d=1;
    ll product=1;
    const int BATCH_SIZE=128;
    int count=0;
    while(1) {
        tortoise=f(tortoise,c);
        hare=f(f(hare,c),c);
        if(tortoise==hare) {
            c=rand(n);
            tortoise=2; hare=2; product=1; count=0;
            continue;
        }
        ll prev_product=product;
        product=modMul(product,abs(tortoise-hare),n);
        if(!product) {
            d=gcd(prev_product,n);
            break;
        }
        count++;
        if(count==BATCH_SIZE) {
            d=gcd(product,n);
            if(d>1) break;
            count=0;
            product=1;
        }
    }
    if(d==n) return pollard_rho(n);
    return d;
}
vector<ll>factorize(ll n) {
    vector<ll> primeFactors;
    if(n<=1) return primeFactors;
    while(!(n%2)) {
        primeFactors.PB(2);
        n/=2;
    }
    if(n==1) return primeFactors;
    while(n>1 && n<MAX_SIEVE) {
        primeFactors.PB(spf[n]);
        n/=spf[n];
    }
    if(n==1) return primeFactors;
    if(isPrime(n)) {
        primeFactors.PB(n);
        return primeFactors;
    }
    ll d=pollard_rho(n);
    vector<ll> fd=factorize(d);
    vector<ll> fnd=factorize(n/d);
    primeFactors.insert(primeFactors.end(),fd.begin(),fd.end());
    primeFactors.insert(primeFactors.end(),fnd.begin(),fnd.end());
    return primeFactors;
}
void GLITCH_() {
    init_sieve(); // run it before testcase
    ll n; cin>>n;
    auto ans=factorize(n);
    sort(ans.begin(),ans.end());
    cout<<ans.size()<<' ';
    for(auto u:ans) cout<<u<<' '; cout<<endl;
}
