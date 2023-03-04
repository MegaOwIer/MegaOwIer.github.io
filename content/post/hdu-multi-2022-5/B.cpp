#include <bits/stdc++.h>
using namespace std;

using LL = long long;
using LLL = __int128_t;
const LL mod = 4179340454199820289;
const int MX = 1000000, MXLG = 45;

vector<int> primes;
int d[MX + 5];
LL F[MXLG], Finv[MXLG];
vector<pair<LL, LL>> G;

void dfs(size_t id, LL x, LL val) {
    static const LL MXVAL = 1000000000000;
    if(id == primes.size() || x * primes[id] > MXVAL || x * primes[id] * primes[id] > MXVAL) {
        G.emplace_back(x, (LLL)x * val % mod);
        return;
    }
    LL cur = x;
    for(int i = 0; cur <= MXVAL; i++, cur *= primes[id]) {
        if(i == 1) {
            continue;
        }
        dfs(id + 1, cur, (LLL)val * Finv[i] % mod);
    }
}

LLL get_inv(LL u) {
    return u == 1 ? 1 : (mod - mod / u) * get_inv(mod % u) % mod;
}

int main() {
    F[0] = 1, F[1] = 1;
    for(int i = 2; i < MXLG; i++) {
        F[i] = LLL(mod - mod / i) * F[mod % i] % mod;
    }

    Finv[0] = 1;
    for(int i = 2; i < MXLG; i++) {
        LLL tmp = accumulate(Finv, Finv + i, (LLL)0);
        Finv[i] = (F[i] + mod - tmp % mod) % mod;
    }

    for(int i = 2; i <= MX; i++) {
        if(!d[i]) {
            primes.push_back(i);
            d[i] = i;
        }
        for(int pr : primes) {
            int cur = i * pr;
            if(cur > MX) {
                break;
            }
            d[cur] = pr;
            if(d[i] == pr) {
                break;
            }
        }
    }

    dfs(0, 1, 1);
    G.emplace_back(0, 0);
    sort(G.begin(), G.end());
    partial_sum(G.begin(), G.end(), G.begin(), [&] (pair<LL, LL> x, pair<LL, LL> y) {
        return make_pair(y.first, (x.second + y.second) % mod);
    });

    auto query = [&] (LL l, LL r) {
        auto i = lower_bound(G.begin(), G.end(), make_pair(l, -1LL));
        auto j = lower_bound(G.begin(), G.end(), make_pair(r + 1, -1LL));
        return (prev(j)->second + mod - prev(i)->second) % mod;
    };

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--) {
        LL n, ans = 0;
        cin >> n;
        for(LL i = 1, j; i <= n; i = j + 1) {
            LLL tmp = n / i;
            j = n / tmp;
            ans = (ans + (tmp * (tmp + 1) / 2 % mod) * query(i, j)) % mod;
        }
        cout << static_cast<LL>(get_inv(n) * ans % mod) << "\n";
    }

    return 0;
}
