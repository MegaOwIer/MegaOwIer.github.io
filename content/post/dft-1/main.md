---
title: 重识 DFT（一）
slug: dft-1
date: 2026-01-13
tags:
  - DFT
  - Maths
  - Algebra
categories:
  - ICPC
  - Mathematics
description: 离散 Fourier 变换与内积
draft: false
lastmod: 2026-01-13
---

## Fourier 级数

在数学分析中有如下结论：任意以 $2\pi$ 为周期的函数 $f(x)$ 若在 $[-\pi, \pi]$ 上有二阶连续导数，则可以表示为

$$
f(x) = \frac{a_0}{2} + \sum_{n=1}^{\infty} \left( a_n \cos nx + b_n \sin nx \right)
$$

其中

$$
a_n = \frac{1}{\pi} \int_{-\pi}^{\pi} f(x) \cos nx \text{d}x \qquad
b_n = \frac{1}{\pi} \int_{-\pi}^{\pi} f(x) \sin nx \text{d}x
$$

这一结论称为 Fourier 级数。在泛函分析中我们可以在线性空间上定义内积，进而我们可以引入类似 $\mathbb{R}^n$ 中坐标系的结构。对于 Fourier 级数，我们可以在 $L^2[-\pi, \pi]$ 空间内定义内积

$$
\langle f, g \rangle = \int_{[-\pi, \pi]} f(x)g(x) \text{d}x
$$

进而以下函数

$$
\left\{ \frac{1}{\sqrt{\pi}}\cos nx, \frac{1}{\sqrt{\pi}}\sin nx : n \in \mathbb{N}_+ \right\}
$$

和常数函数 $\dfrac{1}{\sqrt{2\pi}}$ 一起构成了一组规范正交系（两两正交且范数均为 1）。这时再看 Fourier 级数中系数 $a_n, b_n$ 的计算方式就会发现其实就是用 $f$ 和坐标轴上的单位向量求了一下内积，这正是“求一个向量在某坐标轴上的坐标”的算法。

## 离散 Fourier 变换

既然 DFT 名字里也带一个 Fourier，那么它是否也可以理解为某个内积空间下的“求坐标”？

记 $\omega$ 为 $n$ 次复单位根，我们知道 DFT 做的事情实际上是将一个低于 $n$ 次的多项式变换为长度为 $n$ 的复数列

$$
f(x) = \sum_{k=0}^{n-1} a_k x^k \mapsto \left\{ f(\omega^t) \right\}_{t=0}^{n-1}
$$

我们所寻求的“坐标轴”，就是一组低于 $n$ 次的多项式 $\{ L_t \}$，满足

$$
f(x) = \sum_{t=0}^{n-1} f(\omega^t) L_t(x)
$$

并且这些多项式还需要在某种内积下形成规范正交系。

上面这个式子是一个恒等式。我们分别将 $\omega^t \ (t = 0, 1, \cdots, n-1)$ 代入，即可得到 $\{ L_t \}$ 应该满足：对于任意 $0 \leq p, q \leq n - 1$，有

$$
L_p(\omega^q) = \begin{cases}
1, & p=q \\
0, & p \neq q
\end{cases}
$$

至此我们可以借助 Lagrange 插值确定出全体 $\{ L_t \}$。此处略去。

确定了坐标轴，我们就可以构造出如下内积

$$
\langle f, g \rangle _{\omega} = \sum_{t=0}^{n-1} f(\omega^t) \overline{g(\omega^t)}
$$

不难验证：$\langle f, g \rangle _{\omega}$ 是一个合法的内积，且 $\{ L_t \}$ 是这个内积下的规范正交系。

综上，DFT 在代数上可以被理解为：在由全体低于 $n$ 次的复系数多项式构成，并且定义了前述内积 $\langle f, g \rangle _{\omega}$ 的内积空间内，对给定的多项式 $f$ 求其在规范正交系 $\{ L_t \}$ 下的坐标。

当然我们对 DFT 的探索不会止步于此——如果它只是一个线性变换，那也太无聊了。后面我们会看到，卷积定理会为这个结构引入什么新的乐趣。
