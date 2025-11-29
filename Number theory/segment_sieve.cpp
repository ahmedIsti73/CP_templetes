vector<ll> primes;
vector<int> spf;

void sieve(ll n) { // O(n)
    spf.assign(n + 1, 0);
    primes.clear();
    primes.reserve(n / 10);

    for (int i = 2; i <= n; ++i) {
        if (!spf[i]) {
            spf[i] = i;
            primes.push_back(i);
        }
        for (auto p : primes) {
            ll composite_num = 1LL * i * p;
            if (composite_num > n) break;
            spf[composite_num] = p;
            if (p == spf[i]) break;
        }
    }
}

vector<ll> segmentedSieve(ll L, ll R) {
    vector<bool> mark(R - L + 1, true);
    if (L == 1) mark[0] = false;
    for (auto p : primes) {
        if (1LL * p * p > R) break;
        ll base = max(p * p, ((L + p - 1) / p) * p);
        for (ll j = base; j <= R; j += p)
            mark[j - L] = false;
    }
    vector<ll> seg;
    for (ll i = 0; i <= R - L; i++)
        if (mark[i]) seg.push_back(L + i);
    return seg;
}

// SEGMENT FACTORIZATION 
vector<vector<ll>> segment_factor;
void segment_fact(ll L, ll R) {
    segment_factor.assign(R - L + 1, vector<ll>());
    vector<ll> range_primes(R - L + 1);
    for (ll i = 0; i <= R - L; i++) range_primes[i] = L + i;

    for (auto p : primes) {
        if (1LL * p * p > R) break;
        ll base = p * ((L + p - 1) / p);

        for (ll j = base; j <= R; j += p) {
            ll index = j - L;
            while (range_primes[index] % p == 0) {
                segment_factor[index].push_back(p);
                range_primes[index] /= p;
            }
        }
    }

    for (ll i = 0; i <= R - L; i++) {
        if (range_primes[i] > 1)
            segment_factor[i].push_back(range_primes[i]);
    }
}
