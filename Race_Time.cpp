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
    cout.precision(6);            \
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
ld func(ld t,vector<prr>&vp){
    ld mx=0,mn=MAX;
    for(int i=0;i<vp.size();i++){
        mx=max(mx,(vp[i].F*t*1LL)+vp[i].S);
        mn=min(mn,(vp[i].F*t*1LL)+vp[i].S);
    }
    return (mx-mn);
}
int32_t main()
{
    optimize();
    int t = 1;
    // cin >> t;
    while (t--)
    {
        ld n,tm;
        cin>>n>>tm;
        vector<prr> vp;
        lup(0,n){
            ld speed,pos;
            cin>>speed>>pos;
            vp.PB({speed,pos});
        }
        ld l=0,r=tm;
        ld ans=1e12;
         while(r-l>=1e-12){
            ld t1=l+(r-l)/3;
            ld t2=r-(r-l)/3;
            ld x=func(t1,vp);
            ld y=func(t2,vp);
            if(x>=y){
                l=t1;
            }else {
                r=t2;
            }
            ans=min(ans,min(x,y));
         }
         fraction();
         cout<<ans<<endl;
    }
}
