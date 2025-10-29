#include"bits/stdc++.h"
using namespace std;
using ll = long long;

template<int MOD_T> struct mint {
	static const int mod = MOD_T;
	int v; explicit operator int() const { return v; }
	mint():v(0) {}
	mint(ll _v) { v = int((-MOD_T < _v && _v < MOD_T) ? _v : _v % MOD_T);
		if (v < 0) v += MOD_T; }
	
	mint& operator+=(const mint& o) { 
		if ((v += o.v) >= MOD_T) v -= MOD_T; 
		return *this; }
	mint& operator-=(const mint& o) { 
		if ((v -= o.v) < 0) v += MOD_T; 
		return *this; }
	mint& operator*=(const mint& o) { 
		v = int((ll)v*o.v%MOD_T); return *this; }
	mint& operator/=(const mint& o) { return (*this) *= inv(o); }
	friend mint pow(mint a, ll p) {
		mint ans = 1; assert(p >= 0);
		for (; p; p /= 2, a *= a) if (p&1) ans *= a;
		return ans; }
	friend mint inv(const mint& a) { assert(a.v != 0); 
		return pow(a,MOD_T-2); }
	friend mint operator+(mint a, const mint& b) { return a += b; }
	friend mint operator-(mint a, const mint& b) { return a -= b; }
	friend mint operator*(mint a, const mint& b) { return a *= b; }
	friend mint operator/(mint a, const mint& b) { return a /= b; }
    friend ostream& operator<<(ostream& os, const mint& a) {
        os << a.v;
        return os;
    }

	// --- METHOD 1: Factorial-based (O(N) pre-calc, O(1) query) ---
	static vector<mint> fact;
	static vector<mint> invFact;

	static void precompute(int n) {
		fact.resize(n + 1);
		invFact.resize(n + 1);
		fact[0] = 1;
		for (int i = 1; i <= n; i++) {
			fact[i] = fact[i - 1] * i;
		}
		invFact[n] = inv(fact[n]);
		for (int i = n - 1; i >= 0; i--) {
			invFact[i] = invFact[i + 1] * (i + 1);
		}
	}

	static mint nCr(int n, int k) {
		if (k < 0 || k > n) return 0;
		assert(n < fact.size()); 
		return fact[n] * invFact[k] * invFact[n - k];
	}

	static mint nPr(int n, int k) {
		if (k < 0 || k > n) return 0;
		assert(n < fact.size());
		return fact[n] * invFact[n - k];
	}

	// --- METHOD 2: Pascal's Triangle (O(N^2) pre-calc, O(1) query) ---
	static vector<vector<mint>> scmb; 

	static void genComb(int n) {
		scmb.assign(n + 1, vector<mint>(n + 1));
		scmb[0][0] = 1;
		for(int i = 1; i <= n; ++i) {
			for(int j = 0; j <= i; ++j) {
				scmb[i][j] = scmb[i-1][j] + (j ? scmb[i-1][j-1] : 0);
			}
		}
	}
};

// --- Define the static members outside the class ---
template<int MOD_T> vector<mint<MOD_T>> mint<MOD_T>::fact;
template<int MOD_T> vector<mint<MOD_T>> mint<MOD_T>::invFact;
template<int MOD_T> vector<vector<mint<MOD_T>>> mint<MOD_T>::scmb;

const int MOD = 1e9 + 7;
using mi = mint<MOD>;
/*
cout << "### Example 1: Basic Arithmetic ###" << endl;
mi a = 1'000'000'000; // 1 billion
mi b = 10;
cout << "a + b = " << (a + b) << endl; 
cout << "b - a = " << (b - a) << endl;
cout << "a * b = " << (a * b) << endl;

cout << "### Example 2: Division and Power ###" << endl;

// Calculate 2^100 % MOD
mi p = pow(mi(2), 100);
cout << "2^100 = " << p << endl;
// Calculate (2^100 / 2)
mi p_div_2 = p / mi(2);
cout << "2^100 / 2 = " << p_div_2 << endl;

cout << "### Example 3: O(N) Factorial Method ###" << endl;
// We must call precompute() first.
mi::precompute(1000); // Pre-calculate factorials up to 1000
cout << "10C3 (from nCr) = " << mi::nCr(10, 3) << endl;
cout << "10P3 (from nPr) = " << mi::nPr(10, 3) << endl;

cout << "### Example 4: O(N^2) genComb Method ###" << endl;
// We must call genComb() first.
mi::genComb(100); // Pre-calculate a 100x100 table
cout << "10C3 (from scmb) = " << mi::scmb[10][3] << endl;
cout << "50C25 (from scmb) = " << mi::scmb[50][25] << endl;
*/