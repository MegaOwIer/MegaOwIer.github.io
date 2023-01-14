---
title: 2022 ICPC 西安站 (Gym 104077) 训练记录
slug: cf-gym-104077
date: 2023-01-13

tags:
  - Binary Lifting
  - Constructive Problems
  - Flow Network
  - Greedy
  - Maths
categories:
  - ICPC

description: 为我的算法竞赛筹划一场尽量完美的告别仪式。
draft: false

image: pixiv-59808576.jpg
lastmod: 2023-01-15
---

## 正式训练

### E. Find Maximum

由于 $f$ 的表达式中屡次出现 $\bmod 3$，我们直接考虑将 $x$ 理解为三进制整数。这时候我们会发现使 $f$ 值加一的操作其实有两种，一种是在 $x$ 后面加一个 $0$，一种是在不进位的前提下给 $x$ 的最低为加一。

这就不难得出结论：$f(x)$ 是 $x$ 在三进制表示下的数码和 + 位数。

题目中又要求我们在 $x \in [l, r]$ 的限制下最大化 $f(x)$，我们自然希望求得的 $x$ 含有尽可能长的全 $2$ 后缀。但为了满足 $x \leq r$ 的限制，在这个后缀的前一位应当比 $x$ 小 $1$，再往前的位应该和 $r$ 相等。很凑巧的是这一构造十分契合 $x \geq l$ 的约束条件，因此直接枚举相等的前缀长度即可。

时间复杂度 $O(\log 10^{18})$。

```c++
#include <bits/stdc++.h>
using namespace std;
 
using LL = long long;
 
int solve() {
    LL x, y;
    cin >> x >> y;
 
    vector<int> a, b;
    while(x) {
        a.push_back(x % 3);
        x /= 3;
    }
    while(y) {
        b.push_back(y % 3);
        y /= 3;
    }
 
    while(a.size() < b.size()) {
        a.push_back(0);
    }
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
 
    int pref = 0;
    size_t i = 0;
    while(i < b.size() && a[i] == b[i]) {
        pref += b[i] + 1;
        i++;
    }
 
    int ans = 0;
    while(i < b.size()) {
        if(i == 0 && b[i] == 1) {
            ans = max<int>(ans, pref + 3 * (b.size() - i - 1));
        } else {
            ans = max<int>(ans, pref + b[i] + 3 * (b.size() - i - 1));
        }
        pref += b[i] + 1;
        i++;
    }
 
    return max(pref, ans);
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int t;
    cin >> t;
    while(t--) {
        cout << solve() << "\n";
    }
    return 0;
}

```

### L. Tree

为简便起见，记满足题目中两条性质的集合分别为 A 类集和 B 类集。显然 A 类集必然为树上某一条链的子集。

事实上不难发现任给一棵树，如果只用 B 类集对其划分，那么集合的个数一定等于深度（将深度相同的点放在一个集合里即可），而深度又对应了树上的最长链（即最大的 A 类集）。

我们可以每次从树上抽走一条最长的链（即使在 A 类集个数 +1 的情况下尽可能多地减少 B 类集的数量），统计整个过程中的最小集合数，直接输出即可。

时间复杂度可以做到 $O(n)$，训练时我图省事用 `std::set` 动态维护最小值，复杂度挂了个 $\log$。

```c++
#include <bits/stdc++.h>
using namespace std;
 
const int MX =  1000005;
 
vector<int> G[MX];
int dep[MX], son[MX];
bool vis[MX];
 
void dfs(int u) {
    int cur = 0, ss = -1;
    for(int v : G[u]) {
        dfs(v);
        if(dep[v] > cur) {
            cur = dep[v];
            ss = v;
        }
    }
    dep[u] = cur + 1;
    son[u] = ss;
}
 
int solve() {
    int n;
    cin >> n;
 
    for(int i = 1; i <= n; i++) {
        G[i].clear();
    }
    memset(vis + 1, false, sizeof(bool[n]));
 
    for(int i = 2; i <= n; i++) {
        int fa;
        cin >> fa;
        G[fa].push_back(i);
    }
 
    dfs(1);
 
    set<pair<int, int>, greater<pair<int, int>>> nodes;
    for(int i = 1; i <= n; i++) {
        nodes.emplace(dep[i], i);
    }
 
    int ans = dep[1], cnt = 0;
    while(!nodes.empty()) {
        int u = nodes.begin() -> second;
 
        while(u != -1) {
            nodes.erase(make_pair(dep[u], u));
            u = son[u];
        }
 
        cnt++;
        ans = min(ans, cnt + nodes.begin()->first);
    }
 
    return ans;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int t;
    cin >> t;
    while(t--) {
        cout << solve() << "\n";
    }
    return 0;
}

```

### B. Cells Coloring

假设我们已经知道了颜色数 $k$ 的取值，那么最小的未染色格子数量 $z$ 可以由最大流直接求出。

同时我们知道最大流是凸的，即 $z$ 对 $k$ 的二阶导数非负（有点类似于边际效用递减，证明很显然），由此可知 $ck + dz$ 的二阶导同样非负，那么对这个函数的最小化问题就可以用三分法求解。

时间复杂度大概是 $O(n^3 \log n)$。

```c++
#include <bits/stdc++.h>
using namespace std;

template<typename flow_t = int>
struct MaxFlow_ISAP {
    const flow_t MAX_VAL = numeric_limits<flow_t>::max();

    struct edge_t {
        int to, rev;
        flow_t f;
        edge_t() {}
        edge_t(int _t, int _r, flow_t _f) : to(_t), rev(_r), f(_f) {}
    };

    vector<vector<edge_t>> G;
    vector<typename vector<edge_t>::iterator> cur;
    int V;
    vector<int> gap, dep;

    MaxFlow_ISAP(int v) : G(v + 1), cur(v + 1), V(v) {}

    void add_edge(int u, int v, flow_t f) {
        G[u].emplace_back(v, G[v].size(), f);
        G[v].emplace_back(u, G[u].size() - 1, 0);
    }

    void BFS(int T) {
        gap.assign(V + 2, 0);
        dep.assign(V + 1, 0);
        queue<int> Q;
        Q.push(T), ++gap[dep[T] = 1];
        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for(edge_t &e : G[u]) {
                int v = e.to;
                if(dep[v]) continue;
                Q.push(v), ++gap[dep[v] = dep[u] + 1];
            }
        }
    }

    flow_t dfs(int u, flow_t flow, const int S, const int T) {
        if(u == T || !flow) return flow;
        flow_t w, used = 0;
        for(auto &i = cur[u]; i != G[u].end(); i++) {
            if(i -> f && dep[i -> to] == dep[u] - 1) {
                w = dfs(i -> to, min(flow - used, i -> f), S, T);
                i -> f -= w, G[i -> to][i -> rev].f += w;
                used += w;
            }
            if(used == flow) return flow;
        }
        if(!--gap[dep[u]]) dep[S] = V + 1;
        if(dep[u] <= V) ++dep[u];
        ++gap[dep[u]], cur[u] = G[u].begin();
        return used;
    }

    flow_t operator() (int S, int T) {
        flow_t ans = 0;
        BFS(T);
        while(dep[S] <= V) {
            for(int i = 1; i <= V; i++) cur[i] = G[i].begin();
            ans += dfs(S, MAX_VAL, S, T);
        }
        return ans;
    }
};

using LL = long long;

LL solve() {
    int n, m, c, d;
    cin >> n >> m >> c >> d;

    if(c == 0 || d == 0) {
        return 0;
    }

    vector<pair<int, int>> edges;
    vector<int> cntr(n), cntc(m);
    for(int i = 0; i < n; i++) {
        string qwq;
        cin >> qwq;
        for(int j = 0; j < m; j++) {
            if(qwq[j] == '.') {
                edges.emplace_back(i + 1, j + 1);
                cntr[i]++;
                cntc[j]++;
            }
        }
    }

    int L = 0, R = 0;
    R = max(R, *max_element(cntr.begin(), cntr.end()));
    R = max(R, *max_element(cntc.begin(), cntc.end()));

    vector<LL> cache;
    cache.assign(R + 2, -1);

    auto get_ans = [&] (int x) {
        if(cache[x] != -1) {
            return cache[x];
        }
        
        int S = n + m + 1, T = S + 1;
        MaxFlow_ISAP sol(n + m + 2);
        for(auto [l, r] : edges) {
            sol.add_edge(l, n + r, 1);
        }
        for(int i = 1; i <= n; i++) {
            sol.add_edge(S, i, x);
        }
        for(int i = 1; i <= m; i++) {
            sol.add_edge(n + i, T, x);
        }

        LL ans = sol(S, T);
        return cache[x] = (LL)c * x + d * (edges.size() - ans);
    };

    while(L <= R) {
        int mid = (L + R) / 2;

        LL cur_l = get_ans(mid);
        LL cur_r = get_ans(mid + 1);

        if(cur_l > cur_r) {
            L = mid + 1;
        } else {
            R = mid - 1;
        }
    }

    LL ans = numeric_limits<LL>::max();
    for(LL val : cache) {
        if(val != -1) {
            ans = min(ans, val);
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << solve() << "\n";
    return 0;
}

```

### A. Bridge

不难发现当一座桥架起来后桥之后的两道路永远不可能在上桥的那一侧被走到了。于是我们只需要维护 $n$ 条相互独立的链，而搭桥操作就是将这对应两条链的两个后缀交换。

可以用 $n$ 个独立的平衡树做到这件事情，即 LCT 所维护的链之间的连接信息是多余的。

为了实现方便可以提前离线下所有的询问来确定所有链上的标记点有哪些。时间复杂度 $O((n + q) \log n)$。

这题我只参与思路构筑，没有上手写，因此不贴代码。

---

训练开局我照常从头开始读题，发现 ABC 都很微妙地处于一种可做但不完全可做的状态。

这时候两个队友分别签完了 J 和 F，然后一个队友说要上机打 E 的表，并且给我简述了题意。我一听直接会做了，于是抢占了原计划用于打表的机时直接开始写 E，并让队友做一下 C。E 题代码本来没什么细节，但由于我好久没写这种类似数位 DP 的题导致手生了，足足写了 18min 才过。

在这 18min 里两位队友口胡出了 C 和 G 的做法，E 过了之后不到 5min 队友直接过了 C，然后换另一个队友上去写 G，我们两个没机时的一合计又在 G 过之前想出了 L 的做法。过了 G 之后我直接上机写 L，同样因为手生足足写了 19min。

这时是 81min。

此后 1h 我又想出了 B，两位队友则在搞 A。最终由于题意传达过程中出现了信息失真导致绕了很多弯路，270min 的时候才过 A。

最终本场训练以 0 dirt 8AC 的优秀成绩喜提 VP Au（）今年没选西安站感觉血亏（

其实过了 B 之后我们一直是 A 和 D 同时在想。不过 D 题我们几个都跑偏到最短路上去了死活压不下来复杂度，又发现 A 题意理解假了抓紧去修锅，只得作罢。赛后看了题解，一看见“倍增”俩字，我和一个队友直接会了......

## 赛后补题

### D. Contests

本来想的是答案不会比维数超过太多，但样例直接给了一组答案为 $n - 1$ 的，这个想法直接报废。

我们可以每一步都会走到某一场比赛上可到达的最靠前的位次，然后等跳到足够靠前了最后一步再直接在当前比赛中走到 $y$。可以记 $f_{i, j, k}$ 表示 $j$ 这个人跳 $2^i$ 步最多能到比赛 $k$ 的第几名。这玩意的预处理可以用倍增法在 $O(nm^2 \log n)$ 时间内求出。

考虑查询。类似倍增法 LCA 的查询，我们需要求出「在任何一场比赛中都跳不到 $y$ 及以前任意点的最大步数」。最后输出答案的时候需要 +2，分别对应跳到 y 之前的一步（最后一跳）以及在最后一跳落脚的比赛中跳到 $y$（最后一步）。单次查询的时间是 $O(m^2 \log n)$。

```c++
#include <bits/stdc++.h>
using namespace std;

const int MX = 100005;
const int MXLG = 17;
const int INF = 0x3F3F3F3F;

int rnklist[5][MX], rnk[5][MX];
int dp[MXLG + 1][MX][5];

void update(int &a, int b) {
    if(a == 0 || a > b) a = b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    for(int i = 0; i < m; i++) {
        for(int j = 1; j <= n; j++) {
            int val;
            cin >> val;
            rnklist[i][j] = val;
            rnk[i][val] = j;
        }
    }

    for(int i = 0; i < m; i++) {
        vector<bool> vised(n + 1);
        vector<int> iter(m, 1);
        for(int j = 1; j <= n; j++) {
            int cur = rnklist[i][j];
            for(int k = 0; k < m; k++) {
                update(dp[0][cur][k], iter[k]);
            }

            vised[cur] = true;
            for(int k = 0; k < m; k++) {
                while(iter[k] <= n && vised[rnklist[k][iter[k]]]) iter[k]++;
            }
        }
    }

    for(int i = 1; i <= MXLG; i++) {
        for(int j = 1; j <= n; j++) {
            for(int k = 0; k < m; k++) {
                int &cur = dp[i][j][k];
                cur = dp[i - 1][j][k];
                for(int l = 0; l < m; l++) {
                    int tmp = dp[i - 1][j][l];
                    if(tmp == n + 1) {
                        assert(false);
                    }
                    tmp = rnklist[l][tmp];
                    cur = min(cur, dp[i - 1][tmp][k]);
                }
            }
        }
    }

    function<int(int, int)> solve = [&] (int x, int y) {
        vector<int> point(m);
        for(int i = 0; i < m; i++) {
            if(rnk[i][x] < rnk[i][y]) {
                return 1;
            }
            point[i] = x;
        }

        int ans = 0;
        for(int i = MXLG; i >= 0; i--) {
            vector<int> tmp = point;
            for(int cur : point) {
                for(int j = 0; j < m; j++) {
                    int rk = dp[i][cur][j];
                    if(rk < rnk[j][tmp[j]]) {
                        tmp[j] = rnklist[j][rk];
                    }
                }
            }

            bool flag = false;
            for(int j = 0; j < m; j++) {
                if(rnk[j][tmp[j]] <= rnk[j][y]) {
                    flag = true;
                    break;
                }
            }

            if(!flag) {
                ans += 1 << i;
                point = tmp;
            }
        }

        return ans <= n ? ans + 2 : -1;
    };

    int q;
    cin >> q;
    while(q--) {
        int x, y;
        cin >> x >> y;
        cout << solve(x, y) << "\n";
    }

    return 0;
}

```

### H. Power of Two

中心思想是先用大部分操作凑一个 $0$ 出来，然后用剩下的 or 和 xor 把尽可能多的位置 1。这里面有一车细节，赛场上谁写谁 tm 是五星秘术师（

先贴个代码，后面有时间补充分类讨论的过程。

```c++
#include <bits/stdc++.h>
using namespace std;

const int MX = 65536;

void solve() {
    int n, x, y, z;
    cin >> n >> x >> y >> z;

    map<int, int> cnt;
    for(int i = 1; i <= n; i++) {
        int val;
        cin >> val;
        cnt[val]++;
    }

    // statistics
    vector<int> odds, evens, gt1;
    for(auto [key, value] : cnt) {
        ((value & 1) ? odds : evens).push_back(key);
        if(value > 1) {
            gt1.push_back(key);
        }
    }

    string ans(n, '0'), op_array;
    vector<int> op_num;

    function<void(char, int)> update_answer = [&] (char c, int val) {
        op_array.push_back(c);
        op_num.push_back(val);
    };

    function<int()> pop_answer = [&] {
        int ret = op_num.back();
        op_array.pop_back();
        op_num.pop_back();
        return ret;
    };

    if(y + z <= cnt.size()) {       // or + xor <= #
        for(auto &[key, val] : cnt) {
            while(x > 0 && val > 1) {
                update_answer('&', key);
                val--, x--;
            }
        }
        for(auto &[key, val] : cnt) {
            if(x > 0) {
                update_answer('&', key);
                x--;
            } else if(y > 0) {
                update_answer('|', key);
                ans[key] = '1';
                y--;
            } else {
                update_answer('^', key);
                ans[key] = '1';
                z--;
            }
        }
    } else if(y >= cnt.size()) {    // or >= #
        for(auto &[key, val] : cnt) {
            while(x > 0 && val > 1) {
                update_answer('&', key);
                val--, x--;
            }
            while(z > 0 && val > 1) {
                update_answer('^', key);
                val--, z--;
            }
        }
        assert(x == 0 && z == 0);
        for(auto &[key, val] : cnt) {
            while(val--) {
                update_answer('|', key);
                ans[key] = '1';
            }
        }
    } else if(x == 0) {             // only or + xor
        while(y > 0 && !evens.empty()) {
            int key = evens.back(), &value = cnt[key];
            while(value > 1) {
                update_answer('^', key);
                value--;
            }
            update_answer('|', key);
            y--, value--;
            ans[key] = '1';
            evens.pop_back();
        }
        for(int i = 0; i < y; i++) {
            update_answer('|', odds[i]);
            ans[odds[i]] = '1';
            cnt[odds[i]]--;
        }

        for(auto [key, value] : cnt) {
            while(value--) {
                update_answer('^', key);
                ans[key] ^= 1;
            }
        }
    } else if(y == 0) {             // only and + xor
        z -= cnt.size();
        if(gt1.size() == 1) {
            if(z % 2 == 1) {
                update_answer('&', cnt.begin()->first);
                cnt.begin()->second--;
                x--;
            }

            int special = gt1.front();
            while(x > 0) {
                update_answer('&', special);
                x--, cnt[special]--;
            }

            for(auto &[key, value] : cnt) {
                while(value--) {
                    update_answer('^', key);
                    ans[key] ^= 1;
                }
            }
        } else if(x == 1) {
            bool flag = false;
            int special = gt1.front();
            for(int key : gt1) {
                if(cnt[key] % 2 == 0) {
                    special = key;
                    flag = true;
                    break;
                }
            }

            if(flag) {              // xor sum != 0
                cnt[special]--;
                for(int key : gt1) {
                    int &value = cnt[key];
                    while(value > 1) {
                        update_answer('^', key);
                        value--;
                    }
                }
                update_answer('&', special);
                for(auto [key, _] : cnt) {
                    update_answer('^', key);
                    ans[key] = '1';
                }
            } else {
                update_answer('&', cnt.begin()->first);
                cnt.begin()->second--;
                for(auto [key, value] : cnt) {
                    while(value--) {
                        update_answer('^', key);
                        ans[key] ^= 1;
                    }
                }
            }
        } else {
            cnt[gt1.front()]--;
            cnt[gt1.back()]--;
            x -= 2;

            for(int key : gt1) {
                int &value = cnt[key];
                while(value > 1) {
                    if(z > 0) {
                        update_answer('^', key);
                        z--;
                    } else {
                        update_answer('&', key);
                        x--;
                    }
                    value--;
                }
            }

            update_answer('&', gt1.front());
            update_answer('&', gt1.back());
            for(auto [key, _] : cnt) {
                update_answer('^', key);
                ans[key] = '1';
            }
        }
    } else {                        // or + xor > # && or < #
        z -= cnt.size() - y;
        if(y >= evens.size()) {     // or >= #evens
            sort(odds.begin(), odds.end(), [&] (int u, int v) {
                return cnt[u] > cnt[v];
            });
            
            for(int key : evens) {
                int &value = cnt[key];
                while(z > 0 && value > 1) {
                    update_answer('^', key);
                    z--, value--;
                }
            }

            y -= evens.size();
            for(int i = 0; i < y; i++) {
                int key = odds[i], &value = cnt[key];
                while(z > 0 && value > 1) {
                    update_answer('^', key);
                    z--, value--;
                }
            }

            if(z != 0) {                        // xor left
                if(z % 2 == 1) {
                    z++, cnt[pop_answer()]++;
                }
                for(int i = y; i < odds.size(); i++) {
                    int key = odds[i], &value = cnt[key];
                    while(value > 1 && z > 0) {
                        update_answer('^', key);
                        value--, z--;
                    }
                }
            }
            assert(z == 0);

            for(auto &[key, value] : cnt) {
                while(x > 0 && value > 1) {
                    update_answer('&', key);
                    x--, value--;
                }
            }
            assert(x == 0);

            for(int key : evens) {
                update_answer('|', key);
                ans[key] = '1';
            }
            for(int i = 0; i < odds.size(); i++) {
                update_answer(i < y ? '|' : '^', odds[i]);
                ans[odds[i]] = '1';
            }
        } else {                    // not too bad
            sort(evens.begin(), evens.end(), [&] (int u, int v) {
                return cnt[u] < cnt[v];
            });

            if(z % 2 == 1) {
                int key = evens.back();
                update_answer('^', key);
                cnt[key]--;
                z--;
            }

            for(int key : odds) {
                int &value = cnt[key];
                while(z > 0 && value > 1) {
                    update_answer('^', key);
                    z--, value--;
                }
            }

            y = evens.size() - y;
            for(int i = 0; i < evens.size(); i++) {
                int key = evens[i], &value = cnt[key];
                while(z > 0 && value > 1 + (i < y)) {
                    update_answer('^', key);
                    z--, value--;
                }
            }

            for(int i = 0; i < y; i++) {
                int key = evens[i], &value = cnt[key];
                while(z > 0 && value > 1) {
                    assert(value == 2);
                    update_answer('^', key);
                    z--, value--;
                }
            }

            for(auto &[key, value] : cnt) {
                while(x > 0 && value > 1) {
                    update_answer('&', key);
                    value--, x--;
                }
            }
            assert(x == 0);

            for(int key : odds) {
                update_answer('^', key);
                ans[key] = '1';
            }
            for(int i = 0; i < evens.size(); i++) {
                update_answer(i < y ? '^' : '|', evens[i]);
                ans[evens[i]] = '1';
            }
        }
    }

    reverse(ans.begin(), ans.end());
    cout << ans << "\n" << op_array << "\n";
    for(int val : op_num) {
        cout << val << ' ';
    }
    cout << "\n";
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

```

剩下的 I 和 K 等有缘再补吧（
