// Prime count fast
#include"bits/stdc++.h"
using namespace std;
#define endl '\n'
#define ll long long

const int N=3e5+9;
namespace pcf {
    #define MAXN 20000010
    #define MAX_PRIMES 2000010
    #define PHI_N 100000
    #define PHI_K 100
    int len=0; // number of prime gen by sieve
    int primes[MAX_PRIMES];
    int pref[MAXN]; // number of primes <=i
    int dp[PHI_N][PHI_K];
    bitset<MAXN> f;
    void sieve(int n) {
        f[1]=true;
        for(int i=4;i<=n;i+=2) f[i]=true;
        for(int i=3;i*i<=n;i+=2) {
            if(!f[i]) {
                for(int j=i*i;j<=n;j+=i<<1) f[j]=true;
            }
        }
        for(int i=1;i<=n;i++) {
            if(!f[i]) primes[len++]=i;
            pref[i]=len;
        }
    }
    void init() {
        sieve(MAXN-1);
        for(int n=0;n<PHI_N;n++) dp[n][0]=n;
        for(int k=1;k<PHI_K;k++) {
            for(int n=0;n<PHI_N;n++) {
                dp[n][k]=dp[n][k-1]-dp[n/primes[k-1]][k-1];
            }
        }
    }
    ll bro(ll n,int k) { // number of int <=n not div by first k primes
        if(n<PHI_N && k<PHI_K) return dp[n][k];
        if(k==1) return ((++n)>>1);
        if(primes[k-1]>=n) return 1;
        return bro(n,k-1)-bro(n/primes[k-1],k-1); 
    }
    ll lehmer(ll n) { // runs under 0.2s for n=1e12
        if(n<MAXN) return pref[n];
        ll w,res=0;
        int b=sqrt(n),c=lehmer(cbrt(n)),a=lehmer(sqrt(b));b=lehmer(b);
        res=bro(n,a)+((1LL*(b+a-2)*(b-a+1))>>1);
        for(int i=a;i<b;i++) {
            w=n/primes[i];
            int lim=lehmer(sqrt(w)); res-=lehmer(w);
            if(i<=c) {
                for(int j=i;j<lim;j++) {
                    res+=j;
                    res-=lehmer(w/primes[j]);
                }
            }
        }
        return res;
    }
}
int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    pcf::init();
    ll n; cin>>n;
    cout<<pcf::lehmer(n)<<endl;
}
