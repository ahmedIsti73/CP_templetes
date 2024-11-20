#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod=1e9+7;
ll fact[69];
ll poW(ll x, ll n){
    ll result = 1;
    while (n > 0){
        if (n & 1LL == 1){
            result = (result * x)%mod;
        }
        x = (x * x)%mod;
        n = n >> 1LL;
    }
    return result%mod;
}
ll nCr(ll n,ll r){
    return (fact[n] * poW((fact[r]*fact[n-r])%mod,mod-2)) % mod;
}
ll nPr(ll n,ll r){
    return (fact[n] * poW(fact[n-r]%mod,mod-2)) % mod;
}
int32_t main(){
    ios_base ::sync_with_stdio(0);
    cin.tie(0);                   
    cout.tie(0);
    fact[0]=1;
    for(int i=1;i<=60;i++){
        fact[i]=(fact[i-1]*i*1LL)%mod;
    }
}
