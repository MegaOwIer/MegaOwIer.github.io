---
title: "[HDU 6758] Integral Calculus 的一种推式子方法"
slug: hdu-6785
date: 2021-08-25

tags:
  - Maths
  - Generating Function
categories:
  - ICPC

description: 一个有趣的生成函数推导问题
draft: false

# image: ./pixiv-65053285.jpg
lastmod: 2022-10-12
---

暑假总算是有时间来继续看看《具体数学》，发现提到了 $\zeta$ 函数，于是就想起去年多校有一道比较神仙但我并不是很会的题。今天在翻出来看看，貌似找到了一种相对自然的推导过程。

## 题目大意

给定 $N$，计算

$$
\dfrac{
    \displaystyle\int_{0}^{+\infty} \frac{\tau^{-4N-1}}{e^{1/\tau} - 1} \text{d}\tau
}{
    \left( \displaystyle\int_{0}^{+\infty} \frac{\tau^{-2N-1}}{e^{1/\tau} - 1} \text{d}\tau \right)^2
}
$$

的值。可以证明结果是一个有理数。

$1 \leq N \leq 10^5$，共 $10^5$ 组询问。

## 题解

前期的算式推导相对简单，直到得到这样一个式子

$$
\frac{\zeta(4N)(4N−1)!}{(\zeta(2N)(2N−1)!)^2}
$$

问题就集中在如何求 $\zeta(4N)$ 以及 $\zeta(2N)$ 上。

实际上 Riemann $\zeta$ 函数在奇数处的取值不是很妙，因此我们只考虑偶数部分的生成函数

$$
\begin{align*}
  G(z) &= \sum_{n \geq 1} \zeta(2n) z^{2n} 
    = \sum_{n \geq 1} \sum_{k \geq 1} \frac{1}{k^{2n}}z^{2n} \newline
    &= \sum_{k \geq 1} \frac{z^2}{k^2−z^2}
\end{align*}
$$

接下来是整个推导过程中最精彩的一段——

$$
\begin{align*}
  G(z) &= \sum_{k \geq 1} \frac{z^2}{k^2−z^2} \newline
    &= − \frac{1}{2} z \cdot \sum_{k \geq 1} \frac{2z}{z^2−k^2}
    = − \frac{1}{2} z \cdot \sum_{k \geq 1} \frac{\text{d}}{\text{d}x} \log (z^2−k^2) \newline
    &= − \frac{1}{2} z \cdot \frac{\text{d}}{\text{d}x} \log \left( \prod_{k \geq 1} (z^2−k^2) \right)
\end{align*}
$$

数学分析告诉我们 $\sin x = x \prod_{k \geq 1} (z^2−k^2\pi^2)$，这个乘积和上式就差了一个 $\pi^2$，同时常识告诉我们 $\zeta(2N)$ 一定是某个有理数乘上 $\pi^{2N}$ 的形式，因此不妨把 $G$ 的定义改为 $\zeta(2N)\pi^{-2N}$ 的生成函数。经过类似的推导过程，我们得到

$$
G(z) = \sum_{n \geq 1} \frac{\zeta(2n)}{\pi^{2n}}z^{2n} 
  = − \frac{1}{2} z \cdot \frac{\text{d}}{\text{d}z} \log \frac{\sin z}{z} 
  = \frac{1}{2} ( 1 − z \cot z )
$$

如果你写不出 $x\cot x$ 的 Taylor 展开式 ~~（实际上也不太可能写出来）~~，可以用 $\cos x$ 和 $x^{-1}\sin x$ 相除求出结果。一次求逆一次乘积，总复杂度 $\mathcal{O}(N \log N)$。

## 进一步探索

做到上边那一步其实已经可以算是完了。但我们还想继续推点东西出来。

复变函数告诉我们 $\cot z = i \cdot \frac{e^{2zi}+1}{e^{2zi}−1}$，因此

$$
z \cot z = zi \cdot \frac{e^{2zi}+1}{e^{2zi}−1} = zi + \frac{2zi}{e^{2zi}−1}
$$

后面那一项看起来很眼熟，因为它就是 Bernoulli 数的 EGF。注意到 Bernoulli 数仅在 1 一个奇数的取值非零，因此有

$$
  \frac{x}{e^x−1} = \sum_{n \geq 1} \frac{B_n}{n!}x^n
= B_1 x + \sum_{k \geq 1} \frac{B_{2k}}{(2k)!}x^{2k}
$$

将 $x=2zi$ 代入上式，得到

$$
\frac{2zi}{e^{2zi}−1} = −zi + \sum_{k \geq 1} \frac{B_{2k}}{(2k)!}(−4)^k z^{2k}
$$

一切都联系了起来。也就是说，我们最终的结论是

$$
1 − 2G(z) = z\cot z = \sum_{k \geq 1} \frac{B_{2k}}{(2k)!}(−4)^k z^{2k}
$$

对比两边 $z^{2k}$ 的系数，有

$$
\zeta(2k) = \frac{(−1)^{k+1}B_{2k} (2 \pi)^{2k}}{2(2k)!}
$$

至此，我们也可以通过预处理 Bernoulli 数计算结果。需要的操作仅剩一次求逆，但时间复杂度仍然是 $\mathcal{O}(N \log N)$。

## 后记

至于官方题解里里提到的

$$
  − \sum_{k \geq 1} \frac{x^k}{(2k)!}
= \left( \sum_{k \geq 0} \frac{x^k}{(2k+1)!} \right)
  \left( \sum_{k \geq 1} \frac{\zeta(2k)}{\pi^{2k}} \left( 1 − \frac{1}{2^{2k}} \right) (−x)^k \right)
$$

这个式子，确实也可以在 $\mathcal{O}(N \log N)$ 时间内做出答案，也不知道朝鲜那群出题人是怎么找到这个式子的......