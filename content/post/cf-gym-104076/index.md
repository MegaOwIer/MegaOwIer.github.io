---
title: 2022 ICPC 济南站 (Gym 104076) 训练记录
slug: cf-gym-104076
date: 2023-02-07

tags:
  - DP
  - Maths
categories:
  - ICPC

description: EC-Final 2022 赛前例行训练
draft: false

image: pixiv-66825543.jpg
lastmod: 2023-02-08
---

## 正式训练

### K. Stack Sort

每个栈里存的数字对应到原序列应该位置单调且权值连续递减。直接求出每个数字的位置之后暴力统计即可。

### E. Identical Parity

不难发现相距为 $k$ 的两个数必定有相同的奇偶性。由此可以把整个序列拆分成 $n \bmod k$ 个长度为 $\left\lfloor \dfrac{n}{k} \right\rfloor + 1$ 的链和 $k - (n \bmod k)$ 个长度为 $\left\lfloor \dfrac{n}{k} \right\rfloor$ 的链，而我们要做的就是求不定方程
$$
x \cdot \left( \left\lfloor \frac{n}{k} \right\rfloor + 1 \right) + y \cdot \left\lfloor \frac{n}{k} \right\rfloor = \left\lfloor \frac{n}{2} \right\rfloor
$$
是否有解满足 $0 \leq x \leq n \bmod k$ 且 $0 \leq y \leq k - (n \bmod k)$。

容易写出这个不定方程的通解为
$$
x = \left\lfloor \frac{n}{2} \right\rfloor - r \cdot \left\lfloor \frac{n}{k} \right\rfloor \qquad
y = -\left\lfloor \frac{n}{2} \right\rfloor + r \cdot \left( \left\lfloor \frac{n}{k} \right\rfloor + 1 \right)
$$
直接判断即可。

{{< highlight-content file="E.cpp" lang="cpp" >}}

---

这场由于种种原因打得只有中杯水平。

开场半小时签完 MKE 之后两位队友琢磨出了 A 的做法，但因为细节过多用了将近一个小时才最终过掉。剩下三个半小时基本都在开 D 和 C。D 是一个很直白的大模拟，队友在写的时候我就跑去想 C。C 题其实半个小时不到就想到了正确做法，抢占机时后写到一半突然以为到自己之前的复杂度算错了，然后就对着一个不存在的问题思考了好久，直到最后都没发现自己的 hack 是假的。

队友写 D 也并不轻松。这种大模拟通常整个代码会有很多需要注意的点，而他本来也很不擅长写这种中长篇幅的模拟，最终前前后后写了两个半小时才过掉。

最后不到一小时想着破罐子破摔写一下 C 题的代码，结果差 10min 没写完。

其实说到底应该还是赛中任务分配的决策出了问题。我当时大概应该自己写一遍 D，说不定换完脑子回来 C 就想明白了，和 C 题死磕到最后落得个长考出臭棋的结果。仔细想想 ICPC 打砸的四场里有两场（21 年澳门和 21 年 EC）都在赛时出现了极为致命的决策失误。希望今年 EC 不会再有。

---

## 补题记录

### C. DFS Order 2

我们发现实际上位置的差异完全由兄弟结点的先后顺序决定。我们可以在每个点挂一个形式幂级数 $P(x)$ 表示其兄弟结点给他贡献的偏移量，最后只需要求一遍树上前缀乘积就好了。

我们发现偏移实际上由子树大小和子树个数两个因素决定，因此形式变元应该有两个。用 $s_u$ 和 $c_u$ 分别表示以 $u$ 为根的子树的大小和 DFS 序个数，则结点 $u$ 对他的兄弟的贡献可以表示为
$$
c_u \left( 1 + x^{s_u} y \right)
$$
即如果 $u$ 在兄弟之前，则子树个数 $+1$，偏移量大小 $+ s_u$；否则二者变化量均为 $0$。但无论何种情况贡献的方案数都是 $c_u$，即当前子树 DFS 序的个数。

不妨设当前节点为 $u$，其兄弟节点为 $v_1, v_2, \cdots, v_k$，那么形式幂级数
$$
Q(x, y) = \prod_{i = 1}^{k} c_{v_i} \left( 1 + x^{s_{v_i}} y \right)
$$
的 $x^sy^t$ 项系数则表明当前有 $t$ 子树在 $u$ 之前，贡献了总计 $s$ 的偏移的方案数。

由于兄弟子树的不同顺序算作不同方案，而这在形式幂级数的乘法之中没有体现，故我们所要求的 $P$ 实际上应该是
$$
P(x) = \sum_{t} t! (k - t)! \cdot [y^t]Q(x, y)
$$
其中 $[y^t]Q(x, y)$ 表示 $Q(x, y)$ 视作 $\mathbb{F}_{998244353}\llbracket x \rrbracket$ 上的一元形式幂级数时 $y^t$ 项的系数。

考虑到 $Q$ 的形式，每次求的时候先求出所有儿子的乘积，枚举到对应儿子的时候再现场除掉即可。

最后树上求前缀乘积的部分由于是一元多项式复杂度显然是 $O(n^3)$。对前面求 $P$ 和 $Q$ 的部分，考虑到 $Q$ 的项数是 $O(n^2)$，但每次和 $Q$ 做乘除法的多项式都只有两项，因此单次乘法的复杂度是 $O(n^2)$，总复杂度也是 $O(n^3)$。

{{< highlight-content file="C.cpp" lang="cpp" >}}

其他题目暂咕，啥时候想起来补了再更新。
