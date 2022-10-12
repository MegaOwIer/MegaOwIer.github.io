---
title: 2020 ICPC Macau Regional (Gym 103119) 训练记录
slug: gym-103119
date: 2022-03-27T03:35:00+08:00
lastmod: 2022-05-02T21:48:56+08:00

tags:
  - Constructive Problems
  - Data Structure
  - Maths
categories:
  - ICPC

description: 澳门站打星参赛前的临阵磨枪
draft: false
---

上周澳门站确定线上之后第一时间找我们队长要了一个澳门的打星名额，好巧不巧最后还真就申下来了。那正巧趁着打比赛之前做套题找找手感 ~~，结果被按在地上摩擦~~。

## A. Accelerator

> 简要题意：给定一个序列 $\\{a_i\\}_{i=1}^{n}$，求其所有排列的前缀乘积之和的平均值。

开幕雷击的一个多项式模板。不难看出所有大小为 $r$ 的子集乘积之和为

$$
\prod_{i=1}^{n} (1 + a_i x)
$$

的 $r$ 次项系数，其对答案的贡献需要乘上 $\binom{n}{r}^{-1}$。

## D. Artifacts

一看题面第一行有一个 Genshin Impact 和 Mihoyo 就不怎么想做，再一看样例数据好家伙是字符串处理，直接扔给队友做。

在指指点点的过程中也得到了一个冷知识：Python 的 `float()` 并不能转换形如 `'1.1%'` 这样的百分数。

## F. Fixing Networks

> 简要题意：构造一个 $d-$正则无向图，使之恰好有 $n$ 个点和 $c$ 个连通块。

首先特判掉平凡的 $nd$ 为奇数的情况。对于 $d < 2$ 的情况由于 $c$ 定死了所以也是平凡的。

注意到每个点度数为 $d$，于是每个连通块至少有 $d+1$ 个点，进而 $c(d+1) > n$ 的情况显然无解。

不妨设 $c = 1$。（否则我们可以先构造出 $c-1$ 个完全图 $K_{d+1}$，然后考虑用剩下的点数构造一个连通的 $d-$ 无向图。）

若 $d$ 为偶数，可以考虑将 $n$ 个点排成一个圈，然后每个点向其左右各 $\frac{d}{2}$ 个点连边。

若 $d$ 为奇数，此时 $n$ 必为偶数。将点集划分为 $A = \left\\{ 1, 2, \cdots, \frac{n}{2} \right\\}$ 和 $B = \left\\{ \frac{n}{2} + 1, \cdots, n \right\\}$ 两组。我们的想法是用一个长为 $d$ 的滑动窗口扫描 $A$，并让 $B$ 中的每个顶点和一个窗口连线，显然这样可以得到一个连通的 $d-$正则图。

但当 $d > \frac{n}{2}$ 时这个方法就行不通了。好在正则图的补图仍然正则，且此时有 $n-1-d < \frac{n}{2}$，这样问题又回到了上面的情形。

做题的时候因为没想到 $d > \frac{n}{2}$ 的情况被罚了几发罚时，感觉有点亏。


---

比赛中队友还切掉了 G 和 L，那些题我开都没开就不乱云了。

这时比赛时间还有两个小时，剩下的时间内我们基本在双线程推 C 和 L。

我在和 fpd 迅速构建完 L 的思路后试图让他 50min 内把代码写出来，自己润去和另一个队友讨论 C 的做法。半小时后 C 有了明确做法且云下来编码难度明显低于 L，问了 fpd 发现他没怎么写之后就 15min 写了个 C。结果 WA，而且毫无眉目。这是还剩下 50min，我让队友帮忙静态调错之后试图去 rush 出 L 的代码。

然后 L 没写完，C 也完全不知道错在哪，就这样五个小时到了（

---

## C. Club Assignment

> 简要题意：给出一组数 $A = \\{ a_1, a_2, \cdots, a_n \\}$，求最大的整数 $k$ 使得可以将 $A$ 划分为两个集合，且这同一集合中任意两个不同元素的异或不小于 $k$。

很容易发现一旦有三个数相同，那么答案一定是 $0$。换言之，如果有三个数除低 $k$ 位外完全相同，那么答案一定不会超过 $2^k-1$。

于是我们可以把这组数扔到一棵 Trie 上，检查所有深度极大的 size 不低于 $3$ 的点，枚举其内部划分并算出其对答案的贡献。

这里我们有三个断言：

1. 所有被枚举的点的 size 不超过 $4$（其子节点大小均不超过 $2$）。
2. 被枚举的点所代表的区间两两不相交。
3. 所有未被枚举到的点可以任意选择被分到的集合（在不同子树中的两数异或不会低于相同子树中两数的异或）。

考场上的代码基于上述三个断言，很不幸寄掉了。考后冷静分析才发现上述断言 1 和 3 均是伪命题。

1 的反例由 size 足够大的叶节点给出。上面提到的推理仅对非叶子节点成立，但题目中并没有排除相同权值，故叶节点的 size 可以是任意的。

3 的反例则比较微妙。等以后有时间了配几张图展开说说。

这里给出一个参考代码实现。

```c++
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
```

## J. Jewel Grab

一个很平凡的线段树上二分的题。十分好想且十分难写。这里先给出代码实现，之后也许会专门写一篇文章说说这类问题。

```c++
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
```
