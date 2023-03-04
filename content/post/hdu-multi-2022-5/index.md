---
title: 2022 HDU 多校 Round 5 (HDU 7185-7196) 训练记录
slug: hdu-multi-2022-5
date: 2023-03-01

tags:
  - Constructive Problems
  - Data Structure
  - Maths
categories:
  - ICPC

description: EC-Final 2022 赛前例行训练
draft: false

# image: pixiv-65053285.jpg
lastmod: 2023-03-05
---

## A. Pandaemonium Asphodelos: The First Circle (Savage)

用一个 `map` 维护一下相同 `attribute` 的极长段对整个区间的划分，单独记录每个 `attribute` 的基础权值，用一个线段树维护每个位置相对基础权值的偏差。

在执行修改 `attribute` 的操作时，注意对线段树上对应区间进行更新即可。

由于不同的区间个数是 $O(q)$ 的，因此总时间复杂度是 $O(q \log q \log n)$。

{{< highlight-content file="A.cpp" lang="cpp" >}}

## B. Jo loves counting

不妨设 $n$ 分解素因子的结果是 $\prod p_i^{k_i}$，不难推出 $f(n) = \dfrac{n}{\prod k_i}$，而这显然是一个积性函数。

对于积性函数求和，我们往往会构造另一个积性函数 $g$ 使得其 Dirichlet 卷积 $f * g$ 好求和，然后通过记忆化搜索在 $O(n^{2/3})$ 时间内求得 $f$ 的前 $n$ 项和。但这一时间代价稍微有些高，大概率过不了。

题目期望的做法是把 $f$ 表示成卷积 $f = g * h$，这样有
$$
\sum_{i = 1}^{n} f(i) = \sum_{st \leq n} g(s)h(t) = \sum_{s = 1}^{n} g(s) \sum_{t = 1}^{n/s} h(t)
$$
如果 $g$ 和 $h$ 都可以 $O(1)$ 求出前缀和的话上式的时间效率是 $O(\sqrt{n})$。

可以取 $h(n) = n$，不难推出 $g$ 只在所有 $k_i \neq 1$ 的点处取值非零，显然这样的数只有 $O(\sqrt{n})$ 个，因此直接暴力预处理出 $g$ 在所有点处的取值即可。

{{< highlight-content file="B.cpp" lang="cpp" >}}

## C. Slipper

稍微绕了个弯的签到题。考察 Dijkstra 算法的执行过程，实际上 jump 操作只会在每个深度第一次被更新到时真正起作用，特判一下即可。

## G. Count Set

签到题。对于长为 $n$ 的环，选 $k$ 个互不相邻的位置的选法是
$$
\frac{n}{k} \binom{n - k - 1}{k - 1}
$$
预处理完直接乘起来即可。注意每次合并最短的两个多项式才能保证复杂度。

考场上没看到时限 8 秒，推了好久这玩意的母函数到底是什么形式。

## J. Bragging Dice

结论题。只有双方手里的骰子点数均两两不同时后手胜。因为其他情况下合法的断言集合是非空且有限的，故其中字典序最大的断言唯一。

## K. Kazuha's String

这个题实际上是在判断有 $a, b, c$ 三个文字的自由群在商掉题目中给出那几个串的生成子群之后得到的商群 $G$ 中两个字符串是否等价。

20 年参加字节冬令营的时候见过这个题，当时 jls 讲评的时候提了一嘴“这玩意就是个群，上手爆搜一下就好了”，我一直感觉有什么一般性算法能直接搜出这个群的结构。

考后冷静下来想想，从群表示论的角度出发会更好做一些。

题目中前三个限制表明 $a^2 = b^3 = c^4 = 1$，考虑构造一个单同态 $G \to S_n$。$a, b, c$ 的阶限制了其循环的长度，进而限制了 $n$ 的取值。

比如我们取 $n = 6$，这样 $b$ 只可能是 $3$ 循环或两个 $3$ 循环的积。手玩一下不难得到一组可行解
$$
b = (1 \ 3 \ 5)(2 \ 4 \ 6) \qquad c = (1 \ 2 \ 6 \ 3) (4 \ 5) \qquad a = bc
$$
直接对着模拟即可。

当然如果有限群记得比较多的话可以一下看出来 $S_4 = \langle a, b | a^2 = b^3 = (ab)^4 = 1 \rangle$，然后发现 $G$ 同构于 $S_4$。

{{< highlight-content file="K.cpp" lang="cpp" >}}

---

FJL 三道题是队友在场内解决了的，场内也发现了 H 是一个 OI 味道十分冲的数据结构缝合题。其他题暂咕，有缘再补。
