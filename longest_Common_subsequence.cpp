#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization ("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define optimize()                 \
    ios_base ::sync_with_stdio(0); \
    cin.tie(0);                    \
    cout.tie(0);
#define fraction() cout.unsetf(ios::floatfield);cout.precision(2);cout.setf(ios::fixed,ios::floatfield);
void file(){
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}
#define endl '\n'
#define ll long long int
#define ld long double
#define ha cout << "YES" << endl
#define na cout << "NO" << endl
#define na1 cout << "-1" << endl
#define el cout<<endl;
#define lup(z, n) for (int i = z; i < n; ++i)
#define lup1(z, n) for (int i = z; i <= n; ++i)
#define MAX (ll)(1LL << 31) - 1
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define IS to_string
#define SI stoi
#define popcnt __builtin_popcountll
#define clz __builtin_clz
#define um unordered_map
#define mem(arr,x) memset(arr,x,sizeof arr)
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef tree< ll, null_type, less_equal<ll>, rb_tree_tag, tree_order_statistics_node_update > pbds; 
ll lcm(ll a, ll b) {ll g = __gcd(a, b);return (a * b) / g;}
ll pow(ll x, ll n){ll result = 1;while (n > 0) {if (n & 1LL == 1){result = (result * x);}x = (x * x);n = n >> 1LL;}return result;}
//:::::::::::::::::::::::::::::::::::::::GlitcH::::::::::::::::::::::::::::::::
string s1,s2;
ll dp[4000][4000];
int32_t main()
{
    file();
    optimize();
    // mem(dp,-1);
    cin>>s1>>s2;
    ll x=s1.size(),y=s2.size();
    // for(int i=0;i<=y;i++) dp[0][i]=0;
    // for(int i=0;i<=x;i++) dp[x][0]=0;
    for(int i=1;i<=x;i++){
        for(int j=1;j<=y;j++){
            if(s1[i-1]==s2[j-1]) dp[i][j]=1+dp[i-1][j-1];
            else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
        }
    }
    cout<<dp[x][y]<<endl;
} 