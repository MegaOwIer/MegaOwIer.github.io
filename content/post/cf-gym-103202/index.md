---
title: 2020 ICPC 沈阳站 (Gym 103202) 训练记录
slug: cf-gym-103202
date: 2023-02-03

tags:
  - Constructive Problems
  - DP
  - Greedy
  - Maths
categories:
  - ICPC

description: 莫名其妙被迫单挑了一场例行训练
draft: false

image: pixiv-65927362.jpg
lastmod: 2023-02-04
---

## 训练记录

### G. The Witchwood

签到题。排序之后求最大的 $k$ 个数之和即可。

### F. Kobolds and Catacombs

签到题。等价于求这个序列有多少个前缀满足其中的数恰好为整个序列中最小的几个。

视写法不同，可能需要额外处理相同权值的边界情况。

### D. Journey to Un'Goro

对序列做前缀异或和，得到一个长度为 $n + 1$ 的新序列（第一个位置补 $0$）。显然为了最大化所求的对数需要让前缀和序列中 $0$ 和 $1$ 各自占一半。

由于只需要输出字典序最小的 $100$ 个，直接暴力 dfs 即可。

{{< highlight-content file="D.cpp" lang="cpp" >}}

### I. Rise of Shadows

实际上是在求

$$
| (H - 1) x \bmod HM | \leq A
$$

的解数。这里 $\bmod$ 取最小绝对剩余。

我们熟知对于给定的 $r$，同余方程
$$
(H - 1) x \equiv r \pmod {HM}
$$
有解的充要条件是 $\gcd(H - 1, HM) | r$，且有解时解数为 $\gcd(H - 1, HM)$，由此可知答案为
$$
d \cdot \left( 2 \left\lfloor \frac{A}{d} \right\rfloor + 1 \right)
$$
其中 $d = \gcd(H - 1, HM) = \gcd(H - 1, M)$。注意特判 $2A = HM$ 的情形。

{{< highlight-content file="I.cpp" lang="cpp" >}}

### K. Scholomance Academy

阅读理解题。注意到 AUC 的被积函数间断点取值一定为 negative 样本的估值，直接排序后暴力即可。

{{< highlight-content file="K.cpp" lang="cpp" >}}

### H. The Boomsday Project

注意到租借的总次数并不是很多，可以考虑用 $f_k$ 表示处理完时间最早的前 $k$ 次租借需要的最小花费。

转移就是枚举会员卡的类型，然后判断在满足次数和天数两个限制下最多能跳到哪一次。这一步需要二分。

时间复杂度 $O(n \log m \sum q)$，看上去卡满了铁 T，但不知道为就这么过了。

{{< highlight-content file="H.cpp" lang="cpp" >}}

### M. United in Stormwind

题目里要求 $n$ 个人中答案不同的无序对至少有 $k$ 个，这等价于答案相同的有序对至多 $n^2 - 2k$ 个。

由于每道题的选项只有两种，不妨把 `A` 看作 $0$，`B` 看作 $1$，那么对于两个答案分别为 $x$ 和 $y$ 的人来说，其答案相同的题目集为
$$
x \odot y
$$
其中 $\odot$ 表示二进制同或（XNOR）运算。

记全体题目的集合为 $P$，我们可以统计每个人的答案，将其写成集合幂级数
$$
F(x) = \sum_{n \subset P} a_n x^n
$$
那么 $F$ 和自身做同或卷积
$$
(F * F) (x) = \sum_{m, n \subset P} a_m a_n x^{m \odot n}
$$
所得的结果的系数 $[x^s](F * F)$ 就是答案相同的问题集合恰好为 $s$ 的有序对的个数，而我们要求的实际上就是有多少个集合 $S \subset P$ 满足
$$
\sum_{S \subset T \subset P} [x^T](F * F) \leq n^2 - 2k
$$

同或卷积可以由 FWT 求出，而后半部分的对超集求和可以通过逐元素枚举求出。两部分的时间复杂度均为 $O(m 2^m)$。

对于同或卷积，乃至于更加一般的二元运算的 FWT 变换矩阵的构造，可以参考 [LOJ 548](https://loj.ac/p/548) 的[官方题解](https://loj.ac/d/247)。

{{< highlight-content file="M.cpp" lang="cpp" >}}

### C. Mean Streets of Gadgetzan

由于每一个推断的条件都是正向的，所以当没有任何强制赋值的情况下全赋 `False` 显然是合法的。

我们可以通过 BFS 确定所有可确定的赋值，然后对其他的全部赋 `False`。

{{< highlight-content file="C.cpp" lang="cpp" >}}

---

年后的第一次训练。开场 10min 不到队友 A 急性胃病发作去了医院，随后队友 B 也因为近期心态不好在和我一同做出 F 写过之后选择开摆。

只剩我一人也得硬着头皮打，没办法只能跟榜。所幸一路跟下来 DIKH 全是简单题，读完题就会做的那种，M 也是正好装在我技能歪脖子树上的 FWT。就这么莫名其妙三个半小时（几乎）单挑过了 7 题。

过了 M 之后打算继续做 C，又过了 10min 队友 A 从医院回来了，大致合计出做法之后我有点累就把代码扔给他写睡觉去了。

打完一看，8 题 1045 罚时，场内榜第八。这 tm 还是我几乎全程单挑的结果。~~只能说要不是当年一心想着死磕上海站说不定两年前我们就能去 WF 了（~~

---

## 补题记录

咕
