#include <bits/stdc++.h>
using namespace std;
#define optimize()                 \
    ios_base ::sync_with_stdio(0); \
    cin.tie(0);                    \
    cout.tie(0);
#define fraction() cout.unsetf(ios::floatfield);cout.precision(10);cout.setf(ios::fixed,ios::floatfield);
void file(){
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}
#define endl '\n'
#define ll long long int
#define ha cout << "YES" << endl
#define na cout << "NO" << endl
#define na1 cout << "-1" << endl;
#define lup(z, n) for (int i = z; i < n; ++i)
#define lup_1(z, n) for (int i = z; i <= n; ++i)
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
#define prr pair<ll,ll>
#define rt(v,l) rotate(v.begin(),v.begin()+l,v.end()); // arr = 1,2,3,4,5,6 dile amra index 3 input dile ans arr= 4,5,6,1,2,3 dibe
ll lcm(ll a, ll b)
{
    ll g = __gcd(a, b);
    return (a * b) / g;
}
//----------policy base data structure ---------
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef tree< ll, null_type, less_equal<ll>, rb_tree_tag, tree_order_statistics_node_update > pbds; 
/// cout<<*X.find_by_order(1)<<endl; // eta index input dile oi index er value print korbe
/// cout<<X.order_of_key(-5)<<endl;  // input value theke koto gula small value ase setar count print korbe
//-----------PBDS tamplate end------------------
//------------------ seive -----------------------------
// to show prime numbers
const ll mx=1e8;
bitset<mx> prime;
vector<ll> prime_show;
void seive(ll n){prime[1]=1;for(int i=3;i*i<=n;i+=2){
if(!prime[i]){for(int j=i*i;j<=n;j+=(i*2)){prime[j]=1;}}}
prime_show.PB(2);
for(int i=3;i<=n;i+=2){if(!prime[i]) prime_show.PB(i);}
}
//----------------segment seive-------------------------
vector<ll>segsiv;
void segmentedSieve(ll L, ll R)
{
 bool isPrime[R-L+1];
 for(int i=0 ; i<=R-L+1 ; i++) isPrime[i]=true;
    
 if(L==1) isPrime[0]=false;
    
 for(int i=0 ; prime_show[i]*prime_show[i]<=R ; i++){
    ll curPrime=prime_show[i];
    ll base=curPrime*curPrime;
    if(base<L){base=((L+curPrime-1)/curPrime)*curPrime;}
    for(ll j=base ; j<=R ; j+=curPrime) isPrime[j-L]=false;
 }
 for(int i=0 ; i<=R-L ; i++){if(isPrime[i]==true) segsiv.PB(L+i);}
}
//---------------- seive end ---------------------------
vector<ll> prime_factorization(ll n){ // n number take kon kon prime numer dara vag jai
vector<ll> fector;
for(auto u : prime_show){if(1LL*u*u > n) break;if(!(n%u)){while(!(n%u)){fector.PB(u);n/=u;}}}if(n>1) fector.PB(n);
return fector;
}
ll NOD(ll n){ // number of divisiors of a number ?Time : O(n * (sqrt n)/ln n)
ll nod=1;
for(auto u:prime_show){if(1LL*u*u>n) break;if(!(n%u)){ll cnt=0;while(!(n%u)){n/=u;cnt++;}cnt++;nod*=cnt;}}
if(n>1){nod*=2;}return nod;
}
ll DSF(ll n){ // sum of number of divisors of a given number (1 to n) // DFS: divisor summetory function.. ?time: O(sqrt n)
    ll x=sqrt(n),sum=0;lup_1(1,x) sum+=(n/i)-i;sum*=2; sum+=x;
    return sum;
}
ll SOD(ll n) {// Sum of devisors of an number 
    ll sod=1;
    for(auto u:prime_show){if(1LL*u*u>n) break;
        if(!(n%u)){ll sum=1,a=1;while(!(n%u)){a*=u;sum+=a;n/=u;}sod*=sum;}}
    if(n>1){sod*=(n+1);}
    return sod;
}
ll eulerphi(ll n){ // n er asthe 1 theke n obdi emon koto gulo songkha ase jar sathe n er GCD 1 gcd(n,x)=1 or calculate the numbe of co prime
    ll phi = n; for(auto u:prime_show){if(1LL*u*u>n) break;  // time complexity O(sqrt(n)/ln(sqrt n))
        if(!(n%u)){while(!(n%u)){n/=u;}phi/=u;phi*=(u-1);}}if(n>1){phi/=n;phi*=(n-1);} return phi;
}
const  ll p=5e6+123;
unsigned long long phi[p],ans[p];
void eulerphi_using_harmonic(ll x){
    for(int i=1;i<=x;i++) phi[i]=i;
    for(auto u:prime_show){
    for(int i=u;i<=x;i+=u){phi[i]/=u;phi[i]*=(u-1);}}
}
// summetion of coprimes of a singel given number is (phi[n]*n)/2
void lcm_sum(ll x){
    for(int i=1;i<=x;i++){
        for(int j=i;j<=x;j+=i){
            ans[j]+=(phi[i]*i);
        }
    }
}
ll pow(ll x, ll n) // optimize power function log(n) // power of x
{
    ll result = 1;
    while (n > 0) {
        if (n & 1LL == 1) // y is odd
        {
            result = (result * x);
        }
        x = (x * x);
        n = n >> 1LL; // y=y/2;
    }
    return result;
}
// comparator for sort
bool cmp(const pair<int,int> &p1 ,const pair<int ,int> &p2)
{
    if(p1.first>p2.first) return true;
    else if(p1.first==p2.first) return (p1.second<p2.second);
    return false;
}
int32_t main()
{
    file();
    optimize();
    ll x=1e7;
    seive(x);
    // for(int  i=0;i<segsiv.size();i++) cout<<segsiv[i]<<' '; cout<<endl;
    // while(1){
    //     ll n;
    //     cin>>n;
    //     if(n==0) break;
    //     if(n==1) cout<<0<<endl;
    //     else cout<<eulerphi(n)<<endl;
    // }
    /* lcm sum code
    ll n;
        cin>>n;
        ll sum=ans[n]+1;
        sum*=n;
        sum/=2;
        cout<<sum<<endl;
    */
    // ll q=1e6;
    // seive(q);
    // vector<ll> fec=prime_factorization(12);
    // for(auto u:fec) cout<<u<<' ';
    /*
    vector <pair<int,int>> v;
    sort(v.begin(),v.end(),cmp);
    */
    // int t;
    // cin >> t;
    // while (t--)

    // {

    // }
}
// lembda function 

//         function<ll(ll,ll)>dfs = [&] (ll i,ll p){
//         }; dfs(1,0);

// gp_hash_table<int,int> mp; // faster than unordered map


// ll xoR(ll n){
//     //xor of 0 to n 
//     ll x=n%4;
//     if(x==0) return n;
//     if(x==1) return 1;
//     if(x==2) return n+1;
//     if(x==3) return 0;
// }
// ll nCr(ll n,ll r){
//     r=min(r,n-r);
//     ll ret=1;
//     for(int i=1;i<=r;i++){
//         ret*=(n-i+1);
//         ret/=i;
//     }
//     return rat;
// }

// another way of comperator sort 
// sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
//         return a.arrivalTime < b.arrivalTime;
// });

  // string a; int b; cin >> a >> b; // divisibility of a large number 
  // int ans = 0;
  // for (int i = 0; i < a.size(); i++) {
  //   ans = (ans * 10LL % b + (a[i] - '0')) % b;
  // }
// vector<vector<vector<ll>>> dp(2, vector<vector<ll>>(n + 2, vector<ll>(n + 2, 0))); == dp[2][n][n]={};

// cout<<*next(ck.begin(),k-1)<<endl; kth value of a set

// ll powerr(ll a,ll b,ll mod){
//     ll r=1;
//     while(b){
//         if(b%2) r=((r%mod) *(a%mod))%mod;
//         a=((a%mod)*(a%mod))%mod;
//         b/=2;
//     }
//     return r;
// }
