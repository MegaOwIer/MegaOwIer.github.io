---
title: Codeforces Gym 100002 (NEERC 2002) 简要题解
slug: legacy-2019-05-15
date: 2019-05-15
categories:
    - ICPC
description: 本文由原 CSDN 博客直接迁移而来，迁移时仅作最基础的格式修缮，不保证其内容格式与本站完全适配。
draft: false
lastmod: 2019-05-15
---

[提交链接（Codeforces::Gym）](https://codeforces.com/gym/100002)

[参考代码](https://github.com/MegaOwIer/CodeArchive/tree/master/Codeforces_Gym/100001-100200)

**前排提醒：本场比赛在 Codeforces::Gym 里是用的文件 IO。**

## A. Amusing Numbers

容易发现在 $K$ 确定的情况下 $Q_{N, K}$ 的值单调不减，于是二分答案即可。稍微脑补一下发现答案的一定小于 $T= 10^{18}$。

每次求 $Q_{N, K}$ 的时候记一下当前串是否为 $N$ 和 $M$ 的前缀，直接搜就行了。

时间复杂度：$O(\log^2 T)$

## B. Bricks

显然我们只需要取砖块面积最小的那个面尝试塞进去。

一种做法是枚举旋转角度，由对称性可知枚举 $\left[0, \frac{\pi} {2}\right]$ 即可。时间复杂度为 $O\left(\frac{\pi}{2S}\right)$，其中 $S$ 为枚举步长。

另一种做法是稍微观察一下单调性，找到旋转过程中长或宽的极值点，直接 $O(1)$ 判断。

实际比赛中考虑到时间关系建议使用第一种方法。参考代码中给出的是第二种方法。

## C. Cricket Field

枚举选出的正方形的左右界，显然只需要在有树的竖线中枚举，之后对中间的所有点求纵坐标差的最大值。数据范围很小随便暴力都能过。

时间复杂度：$O(n^3)$

## D. Decoding Task

按题意模拟。

## E. Evacuation Plan

费用流模板。

## F. Folding

区间 DP，中间顺便处理一下循环串折叠的情况即可。
时间复杂度：$O(n^3)$

## G. Ghost Busters

显然有用的射线只有指向所有球心的以及两两球的内公切线。枚举即可。注意两两球的公切线不一定在两球心以及坐标原点确定的平面内。

简单说一下第二种情况的推导过程：

不妨设两个球的球心分别为 $A, B$，所求的公切线为 $OP$，其在平面 $OAB$ 上的投影为 $OQ$。

写两边三垂线定理可以解出 $OP$ 和 $OQ$ 的夹角。

下面需要求出 $OQ$ 在 $OA, OB$ 方向上投影的长度。这个可以由正弦定理和平行四边形定则推出来。具体的结论看代码。

时间复杂度：$O(n + n^2) = O(n^2)$

## H. Heroes Of Might And Magic

总状态数不超过 $50 \times 10 \times 10 \times 10 \times 100 = 5000000$，每个状态的决策数不超过 $12$，直接爆搜即可。

## I. Inlay Cutters

显然每个点的度数不超过 $8$，暴力建图然后暴力数三元环即可。

时间复杂度：$O(k^3)$
