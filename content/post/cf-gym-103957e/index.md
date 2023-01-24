---
title: "[Gym 103957E] Colorful Floor"
slug: cf-gym-103957e
date: 2023-01-25

tags:
  - Maths
categories:
  - ICPC

description: Burnside 引理的推广。
draft: false

lastmod: 2023-01-25
---

## 题目大意

我们需要对一个 $r \times c$ 的网格进行 $K$ 染色。记 $f(i, j)$ 表示 $(i, j)$ 格的颜色，要求存在 $0 \leq n < R$ 以及 $0 \leq m < C$ 使得
$$
f((i + n) \bmod r, (j + m) \bmod c) = p_{f(i, j)}
$$
其中 $p$ 是一个给定的颜色的排列。

两种染色方案相同当且仅当其中一个可以通过下标平移（模意义下）得到另一个。求不同的染色方案数。

$2 \leq K \leq 10^4$, $1 \leq r, c \leq 10^6$，需要处理 $100$ 组询问。

时间限制 $10$ 秒。

## 题解

记网格的行、列组成的集合分别为 $X$ 和 $Y$，颜色集为 $K$。

### Burnside 引理

首先考虑无视排列 $p$ 给出的限制，即 $p$ 是单位排列的特殊情况。

每一个染色方案实际上是格子 $X \times Y$ 到 $K$ 的映射，而循环同构的限制给出了一个变换群 $G$。群 $G$ 在集合 $K^{X \times Y}$ 上有一个自然的作用
$$
\begin{align*}
  G \times K^{X \times Y} &\longrightarrow K^{X \times Y} \newline
  (g, f)                  &\longmapsto     f \circ g
\end{align*}
$$
其中 $f \circ g$ 表示映射的复合 $t \mapsto f(g(t))$，其中 $t \in X \times Y$。

由 Burnside 引理，这个群作用的轨道（等价类）数量为
$$
|K^{X \times Y} / G| = \frac{1}{|G|} \sum_{g \in G} \\# \\{ f \in K^{X \times Y} : f \circ g = f \\}
$$

注意到 $G \cong C_r \oplus C_c$ 同构于两个循环群的直和，我们不难写出答案

$$
|K^{X \times Y} / G| = \frac{1}{rc} \sum_{i | r, j | c} \varphi(i) \varphi(j) |K|^{\frac{rc}{\operatorname{lcm}(i, j)}}
$$

### 额外限制

任取等价类 $\overline{f} \in K^{X \times Y} / G$，我们发现排列 $p$ 的限制实际上是在说
$$
f \circ g = p \circ f
$$
由此我们不难猜出所求答案应该是
$$
\frac{1}{|G|} \sum_{g \in G} \\# \\{ f \in K^{X \times Y} : f \circ g = p \circ f \\}
$$
我们先考虑这玩意怎么求，之后再来证明这个式子。

任取 $t \in X \times Y$，条件 $f \circ g = p \circ f$ 表明
$$
p_{f(t)} = f(g(t))
$$
即格子 $t$ 在置换 $g$ 作用下的像的颜色，一定是 $t$ 自身颜色在排列上的后续。不妨设 $g = (s, t) \in C_r \oplus C_c$，则格子 $t$ 在置换 $g$ 的不断作用下经过的轨道大小为 $l = \operatorname{lcm}\left( \dfrac{r}{\gcd(s, r)}, \dfrac{c}{\gcd(c, t)} \right)$，进而可知 $t$ 中只有长度为 $l$ 的因子的循环才能完成该轨道的染色。

分别枚举 $\gcd(s, r)$ 和 $\gcd(c, t)$ 可以得到最终结果为
$$
\frac{1}{cr} \sum_{i | r, j | c} \varphi(i) \varphi(j) K(\operatorname{lcm}(i, j))^{\frac{rc}{\operatorname{lcm}(i, j)}}
$$
其中 $K(x)$ 表示排列 $p^x$ 的不动点个数。

预处理一下排列的环长信息，直接暴力枚举即可。由于排列中不同的环长最多有 $O(\sqrt{K})$ 种，而 $10^6$ 范围内因子数 $d \leq 240$，故单次询问的时间复杂度是 $O(K + \sqrt{R} + d^2\sqrt{K})$。足以通过此题。

{{< highlight-content lang="c++" file="brute-force.cpp" args="hl_lines=60-69" >}}

### 证明

我们的结论可以归纳为

{{< quote >}}
**定理**：设 $A$, $B$ 为有限集，$G$ 是 $A$ 上的置换群。集合 $X \subset B^A$，且群 $G$ 在 $B^A$ 上的作用限制到 $X$ 上后是封闭的。给定 $B$ 的一个置换 $p$，称轨道（等价类） $\overline{f} \in X / G$ 是“好”的，当且仅当存在 $g \in G$ 使得
$$
f \circ g = p \circ f
$$
则“好”的等价类个数为
$$
\frac{1}{|G|} \sum_{g \in G} \\# \\{ f \in X : f \circ g = p \circ f \\}
$$
{{< / quote >}}

我们首先说明我们所定义的等价类是“好”的良定义（即与代表元选取无关）。

对处于同一条轨道中的两个映射 $f_1, f_2$ 必然存在 $g_0 \in G$ 使得 $f_1 = f_2 \circ g_0$，进而
$$
\begin{align*}
  f_1 \circ g = p \circ f_1
  &\iff (f_2 \circ g_0) \circ g = p \circ (f_2 \circ g_0) \newline
  &\iff f_2 \circ (g_0 \circ g \circ g_0^{-1}) = p \circ f_2 \newline
  &\iff f_2 \circ (g_0^{-1}gg_0) = p \circ f_2 \newline
\end{align*}
$$
上式中最后一步是群作用的定义。注意到 $g \mapsto g_0^{-1}gg_0$ 是双射，故对 $f_1$ 和 $f_2$ 而言符合要求的 $g$ 是一样多的。

回到原命题的证明。令
$$
G_{p}^{f} = \\{ g \in G : f \circ g = p \circ f \\}
$$
我们前面已经证明，当 $f_1$ 与 $f_2$ 在同一条轨道中时有 $|G_{p}^{f_1}| = |G_{p}^{f_2}|$。此外，我们断言：当 $G_{p}^{f}$ 非空时有 $|G_{p}^{f}| = |G^{f}|$。

由 $G_{p}^{f}$ 非空，不妨取 $g \in G_{p}^{f}$。对任意 $g_0 \in G^f$，有
$$
f \circ (gg_0) = (f \circ g_0) \circ g = f \circ g = p \circ f
$$
由此可知 $gG^f \subset G_{p}^{f}$。反之，对任意 $g_0 \in G_{p}^{f}$，有
$$
f \circ (g^{-1}g_0) = (f \circ g_0) \circ g^{-1} = (f \circ g) \circ g^{-1} = f
$$
故有 $gG^f \supset G_{p}^{f}$。综上有 $gG^f = G_{p}^{f}$，进而 $|G^f| = |G_{p}^{f}|$。

于是我们有
$$
\sum_{g \in G} \\# \\{ f \in X : f \circ g = p \circ f \\}
= \sum_{f \in X} |G_{p}^{f}|
= \sum_{\overline{f} \in X / G} |G_{p}^{f}| |G(f)|
$$
注意到 $|G_{p}^{f}|$ 的取值只可能为 $0$ 或 $|G^f|$，而 $|G^f||G(f)| = |G|$，由此命题得证。

## 效率优化

我们发现代码的性能瓶颈是 60-69 行的查询部分，中间那个 for 循环每次都会完整遍历整个 `map`。

同时不难发现，我们的查询实际上是计数序列和全 $1$ 序列的 Dirichlet 卷积。同时计数序列有一个很微妙的的性质：所有非零元只出现在下标是 $\operatorname{lcm}(r, c)$ 因子的位置。

这种情况下的 Dirichlet 卷积可以通过枚举 $\operatorname{lcm}(r, c)$ 的素因子进行。具体细节参考代码。

由于 $\operatorname{lcm}(r, c)$ 的因子数 $d_1 \leq 6720$，素因子个数 $\omega \leq 11$，故单次查询的时间复杂度降为 $O(K + R + d_1\omega + d^2 \log d_1)$。实际测试中运行效率显著提升。

{{< highlight-content lang="c++" file="optimize.cpp" args="linenostart=60" >}}
