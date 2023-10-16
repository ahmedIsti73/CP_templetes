#include <bits/stdc++.h>
using namespace std;
#define optimize()                 \
    ios_base ::sync_with_stdio(0); \
    cin.tie(0);                    \
    cout.tie(0);
#define endl '\n'
#define ll long long int
#define ha cout << "YES" << endl
#define na cout << "NO" << endl
#define na1 cout << "-1" << endl;
#define lup(z, n) for (int i = z; i < n; ++i)
#define lup_1(z, n) for (int i = z; i <= n; ++i)
#define MAX (ll)(1LL << 31) - 1
const int mx = 2e5 + 123;
int a[mx];
void marge(int l, int mid, int r)
{
    int p = l;
    int q = mid + 1;
    int temp[r - l + 1];
    int k = 0;
    while (p <= mid && q <= r)
    {
        if (a[p] <= a[q])
        {
            temp[k] = a[p];
            k++;
            p++;
        }
        else
        {
            temp[k] = a[q];
            k++;
            q++;
        }
    }
    while (p <= mid)
    {
        temp[k] = a[p];
        p++;
        k++;
    }
    while (q <= r)
    {
        temp[k] = a[q];
        q++;
        k++;
    }
    k = 0;
    for (int i = l; i <= r; i++)
    {
        a[i] = temp[k];
        k++;
    }
}
void margesort(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) / 2;
    margesort(l, mid);
    margesort(mid + 1, r);
    cout<<l<<' '<<mid<<' '<<r<<endl;
    marge(l, mid, r);
}

//:::::::::::::::::::::::::::::::::::::::GlitcH::::::::::::::::::::::::::::::::
int32_t main()
{
#ifndef ONLINE_JUDGE
    // for getting input from input.txt
    freopen("input.txt", "r", stdin);
    // for writing output to output.txt
    freopen("output.txt", "w", stdout);
#endif
    optimize();
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    margesort(1, n);
    for (int i = 1; i <= n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}