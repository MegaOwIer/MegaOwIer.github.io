#include <bits/stdc++.h>
using namespace std;

using LL = long long;

struct segTree {
    shared_ptr<segTree> lson, rson;
    LL tag;

    segTree() : tag(0) {};

    void update(int l, int r, LL val, int L, int R) {
        if(l <= L && R <= r) {
            tag += val;
            return;
        }
        int mid = (L + R) / 2;
        if(l <= mid) {
            if(!lson) lson = make_shared<segTree>();
            lson->update(l, r, val, L, mid);
        }
        if(r > mid) {
            if(!rson) rson = make_shared<segTree>();
            rson->update(l, r, val, mid + 1, R);
        }
    }

    LL query(int pos, int L, int R) {
        LL ans = tag;
        if(L != R) {
            int mid = (L + R) / 2;
            if(pos <= mid && lson) {
                ans += lson->query(pos, L, mid);
            }
            if(pos > mid && rson) {
                ans += rson->query(pos, mid + 1, R);
            }
        }
        return ans;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;

    int attr_id = 0, last = 0;
    map<int, pair<int, int>> LR {{0, {0, -1}}, {n, {1, 0}}, {n + 1, {n + 1, -1}}};

    function<int(int)> get_attr = [&] (int x) {
        return LR.lower_bound(x)->second.second;
    };

    vector<LL> value {0};
    shared_ptr<segTree> root = make_shared<segTree>();

    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            int x, c;
            cin >> x >> c;
            x = ((x - 1) ^ last) % n + 1;
            c = ((c - 1) ^ last) % ((n - 1) / 2) + 1;
            
            x = max(x, c + 1);
            x = min(x, n - c);
            int l = x - c, r = x + c;

            pair<int, pair<int, int>> tmp;
            for(auto it = LR.lower_bound(l); it->second.first <= r; it++) {
                int ll = it->second.first, rr = it->first;
                if(ll < l) {
                    tmp = {l - 1, make_pair(ll, it->second.second)};
                    ll = l;
                }
                if(rr > r) {
                    it->second.first = r + 1;
                    rr = r;
                }
                root->update(ll, rr, value[it->second.second], 1, n);
            }

            LR.erase(LR.lower_bound(l), LR.upper_bound(r));
            if(tmp.first) {
                LR.insert(tmp);
            }

            LR[r] = {l, ++attr_id};
            value.push_back(0);
        } else if(op == 2) {
            int x, y;
            cin >> x >> y;
            x = ((x - 1) ^ last) % n + 1;
            y = ((y - 1) ^ last) % n + 1;

            auto it = LR.lower_bound(y);
            int l = it->second.first, r = it->first;
            int attr_x = get_attr(x), attr_y = it->second.second;
            root->update(l, r, value[attr_y] - value[attr_x], 1, n);
            it->second.second = attr_x;

            // merge segment with same attr
            vector<int> del_key;
            if(prev(it)->second.second == attr_x) {
                it->second.first = prev(it)->second.first;
                del_key.push_back(prev(it)->first);
            }
            if(next(it)->second.second == attr_x) {
                next(it)->second.first = it->second.first;
                del_key.push_back(it->first);
            }
            for(int key : del_key) {
                LR.erase(key);
            }
        } else if(op == 3) {
            int x, v;
            cin >> x >> v;
            x = ((x - 1) ^ last) % n + 1;
            value[get_attr(x)] += v;
        } else {
            int x;
            cin >> x;
            x = ((x - 1) ^ last) % n + 1;
            LL ans = root->query(x, 1, n) + value[get_attr(x)];
            cout << ans << "\n";
            last = ans & 0x3FFFFFFF;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }

    return 0;
}
