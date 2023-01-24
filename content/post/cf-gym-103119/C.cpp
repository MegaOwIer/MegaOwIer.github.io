#include <bits/stdc++.h>
using namespace std;

struct Trie {
    Trie *son[2];
    int siz;
    bool visited;
    vector<int> numbers, position;

    Trie() : siz(0), visited(false) {
        son[0] = son[1] = nullptr;
    }
    ~Trie() {
        for(auto u : son) {
            if(u) delete u;
        }
    }
};

void insert(Trie *&o, int val, int dep, int pos) {
    if(dep < 0) {
        return;
    }
    if(!o) o = new Trie;
    if(o->numbers.size() < 4) {
        o->numbers.push_back(val);
        o->position.push_back(pos);
    }
    o->siz += 1;
    insert(o->son[(val >> dep) & 1], val, dep - 1, pos);
}

int calc(vector<int> &arr, int S) {
    int res = numeric_limits<int>::max();
    for(size_t i = 0; i < arr.size(); i++) if((S >> i) & 1) {
        for(size_t j = 0; j < arr.size(); j++) if((S >> j) & 1) {
            if(i != j) {
                res = min(res, arr[i] ^ arr[j]);
            }
        }
    }
    return res;
}

bool dfs1(Trie *o, int &ans, string &result) {
    bool flag = true, is_leaf = true;
    for(Trie *v : o->son) if(v) {
        flag = dfs1(v, ans, result) && flag;
        is_leaf = false;
    }
    if(flag && o->siz >= 3) {
        o->visited = true;
        if(o->siz > 4) {
            ans = 0;
            return false;
        }
        int cur_res = -1;

        int S = (1 << o->siz) - 1;
        int max_S = 0;
        for(int k = S; k > 0; k = (k - 1) & S) {
            int r = S ^ k;
            int qwq = min(calc(o->numbers, k), calc(o->numbers, r));
            if(qwq > cur_res) {
                cur_res = qwq;
                max_S = k;
            }
        }
        for(int i = 0; i < o->siz; i++) if((max_S >> i) & 1) {
            result[o->position[i]] = '2';
        }

        ans = min(ans, cur_res);
    }
    return o->siz < 3;
}

bool dfs2(Trie *o, string &result) {
    if(o->visited) {
        return false;
    }
    
    bool flag = true;
    for(Trie *v : o->son) if(v) {
        flag = dfs2(v, result) && flag;
    }
    if(flag && o->siz == 2) {
        result[o->position.back()] = '2';
    }
    return o->siz < 2;
}

void solve() {
    int n;
    cin >> n;

    Trie *root = nullptr;
    for(int i = 0; i < n; i++) {
        int val;
        cin >> val;
        insert(root, val, 29, i);
    }

    int ans = numeric_limits<int>::max();
    string result(n, '1');
    dfs1(root, ans, result);
    dfs2(root, result);

    cout << ans << "\n" << result << "\n";
    delete root;
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
