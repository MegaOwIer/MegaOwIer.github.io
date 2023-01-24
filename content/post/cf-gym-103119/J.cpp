#include <bits/stdc++.h>
using namespace std;

using LL = long long;
using Points = vector<pair<int, int>>;

struct segTree {
    Points links;
    LL sum;
};

const int MX = 200005;

segTree tr[MX << 2];

vector<int> c, v;
set<int> positons[MX];

void merge(Points &o, const Points &l, const Points &r) {
    o.resize(l.size() + r.size());
    std::merge(l.begin(), l.end(), r.begin(), r.end(), o.begin(), [] (pair<int, int> u, pair<int, int> v) {
        return u.second == v.second ? u.first < v.first : u.second < v.second;
    });
    if(o.size() > 11) {
        o.resize(11);
    }
}

void maintain(int o) {
    int l = o * 2, r = o * 2 + 1;
    tr[o].sum = tr[l].sum + tr[r].sum;
    merge(tr[o].links, tr[l].links, tr[r].links);
}

void build(int l, int r, int id) {
    if(l == r) {
        tr[id].links = { make_pair(l, *positons[c[l]].upper_bound(l)) };
        tr[id].sum = v[l];
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, id * 2);
    build(mid + 1, r, id * 2 + 1);
    maintain(id);
}

void modify(int l, int r, int id, int pos, int nxt, int val) {
    if(l == r) {
        tr[id].sum = (val == -1) ? tr[id].sum : val;
        tr[id].links = { make_pair(pos, nxt) };
        return;
    }
    int mid = (l + r) / 2;
    if(pos <= mid) modify(l, mid, id * 2, pos, nxt, val);
    if(pos > mid) modify(mid + 1, r, id * 2 + 1, pos, nxt, val);
    maintain(id);
}

int get_Kth(const Points &pts, int k) {
    k = min<int>(k, pts.size());
    return pts[k - 1].second;
}

bool solve(int l, int r, int id, int L, int &R, LL &ans, Points &links, int K) {
    if(l >= L) {
        Points tmp;
        merge(tmp, links, tr[id].links);
        if(get_Kth(tmp, K + 1) - 1 >= r) {
            R = r;
            links = tmp;
            ans += tr[id].sum;
            return true;
        }
    }
    if(l == r) return false;
    int mid = (l + r) / 2;
    if(L <= mid) {
        return solve(l, mid, id * 2, L, R, ans, links, K) &&
               solve(mid + 1, r, id * 2 + 1, L, R, ans, links, K);
    } else {
        return solve(mid + 1, r, id * 2 + 1, L, R, ans, links, K);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    for(int i = 1; i <= n; i++) {
        positons[i].insert(n + 1);
    }

    c.resize(n + 1);
    v.resize(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> c[i] >> v[i];
        positons[c[i]].insert(i);
    }

    build(1, n, 1);

    while(m--) {
        int op;
        cin >> op;
        if(op == 1) {
            int x, new_c, new_v;
            cin >> x >> new_c >> new_v;

            int old_c = c[x];

            auto old_c_prev_pos = positons[old_c].find(x);
            auto old_c_next_pos = next(old_c_prev_pos);
            if(old_c_prev_pos != positons[old_c].begin()) {
                old_c_prev_pos = prev(old_c_prev_pos);
                modify(1, n, 1, *old_c_prev_pos, *old_c_next_pos, -1);
            }
            positons[old_c].erase(x);

            auto new_c_next_pos = positons[new_c].upper_bound(x);
            auto new_c_prev_pos = prev(new_c_next_pos);
            if(new_c_next_pos != positons[new_c].begin()) {
                modify(1, n, 1, *new_c_prev_pos, x, -1);
            }
            modify(1, n, 1, x, *new_c_next_pos, new_v);
            positons[new_c].insert(x);

            c[x] = new_c, v[x] = new_v;
        } else {
            int s, k;
            cin >> s >> k;

            Points cur_res;
            LL ans = 0;
            int R = s;
            solve(1, n, 1, s, R, ans, cur_res, k);

            map<int, int> value;
            set<int> vis;

            auto update = [&] (int pos) {
                if(vis.count(pos)) return;
                vis.insert(pos);

                int color = c[pos];
                value[color] = max(value[color], v[pos]);
                ans -= v[pos];
            };

            for(auto &[pos, nxt] : cur_res) {
                update(pos);
                if(nxt <= R) update(nxt);
            }

            for(auto &tmp : value) ans += tmp.second;
            cout << ans << "\n";
        }
    }

    return 0;
}
