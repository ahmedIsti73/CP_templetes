// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx,avx2,fma")
// #pragma GCC optimization ("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define optimize()                 \
    ios_base ::sync_with_stdio(0); \
    cin.tie(0);                    \
    cout.tie(0);
#define fraction()                \
    cout.unsetf(ios::floatfield); \
    cout.precision(2);            \
    cout.setf(ios::fixed, ios::floatfield);
#define endl '\n'
#define ll long long int
#define ld long double
#define ha cout << "YES" << endl
#define na cout << "NO" << endl
#define na1 cout << "-1" << endl
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
#define mem(arr, x) memset(arr, x, sizeof arr)
#define prr pair<ll, ll>
#define rt(v, l) rotate(v.begin(), v.begin() + l, v.end());
#define all(q) (q.begin(), q.end())
#define bitsetTOint(bt) bt.to_ulong()
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef tree<ll, null_type, less_equal<ll>, rb_tree_tag, tree_order_statistics_node_update> pbds;
//:::::::::::::::::::::::::::::::::::::::GlitcH::::::::::::::::::::::::::::::::
int32_t main()
{
    optimize();
    int t = 1;
    // cin >> t;
    while (t--)
    {
        ll n,m;
        cin>>n>>m;
        vector<ll> v1,v2;
        ll bou=(n+1)/2;
        lup(0,n){
            ll x; cin>>x;
            if(n==1) v1.PB(x);
            else{
                if((ll)v1.size()<bou) v1.PB(x);
                else v2.PB(x);
            }
        }
        if(n==1) cout<<v1[0]%m<<endl;
        else{
            vector<ll> all;
            for(int musk=0;musk<(1LL<<v1.size());musk++){
                ll sum=0;
                for(int i=0;i<19;i++){
                    if((musk&(1LL<<i))) sum+=v1[i];
                }
                all.PB(sum%m);
            }
            sort(all.begin(),all.end());
            all.resize(unique(all.begin(),all.end())-all.begin());
            ll ans=0;
            for(int musk=0;musk<(1LL<<v2.size());musk++){
                ll sum=0;
                for(int i=0;i<19;i++){
                    if((musk&(1LL<<i))) sum+=v2[i];
                }
                ll x=(sum%m);
                ll y=((sum/m)+1)*m;
                y-=sum;
                y--;
                ll xy=upper_bound(all.begin(),all.end(),y)-all.begin();
                xy--;
                ans=max(ans,all[xy]+x);
            }
            cout<<ans<<endl;
        }
    }
}
