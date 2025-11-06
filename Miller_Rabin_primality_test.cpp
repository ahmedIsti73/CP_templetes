// Miller Rabin 
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
