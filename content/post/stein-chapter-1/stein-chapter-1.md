---
title: Stein Complex Analysis 复分析第一章复习提纲
slug: stein-chapter-1
date: 2022-12-28

tags:
  - Complex Analysis
categories:
  - Mathematics
  - RUC

description: 复变课的作业记录以及期末习题课的笔记
draft: false

lastmod: 2022-12-28
---

## 复平面上的度量

这本书的 1.1 节通篇都在建立复平面 $\mathbb{C}$ 上的拓扑结构。这些讨论在任何一本点集拓扑的书中都有讨论，就不再重复。

复平面上的度量除了我们熟知的 $d(u, v) = |u - v|$ 以外，还有一个比较经典的例子。

考虑球极投影，它会将 $z = x + iy$ 映射到单位球面 $S^2$ 上的点

$$
\left( \frac{2 \operatorname{Re} z}{|z|^2 + 1}, \frac{2 \operatorname{Im} z}{|z|^2 + 1}, \frac{|z|^2 - 1}{|z|^2 + 1} \right)
= \left( \frac{z + \overline{z}}{|z|^2 + 1}, \frac{-i(z - \overline{z})}{|z|^2 + 1}, \frac{|z|^2 - 1}{|z|^2 + 1} \right)
$$

那么对于复平面上的点 $w_1$ 和 $w_2$，不妨设其在球面上的像分别为 $(x_1, y_1, z_1)$ 和 $(x_2, y_2, z_2)$，则两个像点之间的距离

$$
\begin{align*}
  d^2 &= (x_1 - x_2)^2 + (y_1 - y_2)^2 + (z_1 - z_2)^2 \newline
  &= (x_1^2 + y_1^2 + z_1^2) + (x_2^2 + y_2^2 + z_2^2) - 2(x_1x_2 + y_1y_2 + z_1z_2) \newline
  &= 2 - 2(x_1x_2 + y_1y_2 + z_1z_2)
\end{align*}
$$

先不计入分母 $(|w_1|^2 + 1)(|w_2|^2 + 1)$，上式中最后一项

$$
\begin{align*}
   & x_1x_2 + y_1y_2 + z_1z_2 \newline
  =& (w_1 + \overline{w_1})(w_2 + \overline{w_2}) - (w_1 - \overline{w_1})(w_2 - \overline{w_2}) + (|w_1|^2 - 1)(|w_2|^2 - 1) \newline
  =& 2(w_1 \overline{w_2} + w_2 \overline{w_1}) + (|w_1|^2 - 1)(|w_2|^2 - 1) \newline
  =& (|w_1|^2 + 1)(|w_2|^2 + 1) + 2(w_1 \overline{w_2} + w_2 \overline{w_1}) - 2(|w_1|^2 + |w_2|^2) \newline
  =& (|w_1|^2 + 1)(|w_2|^2 + 1) - 2(w_1 - w_2)(\overline{w_1} - \overline{w_2}) \newline
  =& (|w_1|^2 + 1)(|w_2|^2 + 1) - 2 |w_1 - w_2|^2
\end{align*}
$$

代入即得

$$
d(w_1, w_2) = \frac{2 |w_1 - w_2|}{\sqrt{|w_1|^2 + 1} \sqrt{|w_2|^2 + 1}}
$$

由于上述 $d$ 为复平面上的点经球极投影映射到单位球面的像在 $\mathbb{R}^3$ 中的欧氏距离，其必然为 $\mathbb{C}$ 上的度量。

## 关于复可导与全纯

根据这本书 1.2.2 节的定义，函数 $f$ 在 $z_0$ 点全纯（$f$ is holomorphic at the point $z_0$）的定义是极限

$$
\lim_{h \to 0} \frac{f(z_0 + h) - f(z_0)}{h}
$$

存在。但是根据后文的说明，对于闭集 $\Omega$，$f$ 在 $\Omega$ 上全纯需要 $f$ 在 $\Omega$ 的某个开邻域上全纯。

显然单点集是闭集，因此 $f$ 在 $z_0$ 点全纯的定义应该是存在 $z_0$ 的某个开邻域 $D$ 使得 $f$ 在 $D$ 上全纯，这一要求显然强于上面的极限存在。

我们将采用后者为函数 $f$ 在 $z_0$ 点全纯的定义，而将仅在一点极限存在表述为复可导。

实际上这两个定义也是不等价的。记 $f(z) = z^2D(z)$，其中 $D(z)$ 在 $z$ 的实部和虚部均为有理数时取值为 $1$，否则取值为 $0$。考虑 $z = 0$，则有极限

$$
\lim_{h \to 0} \frac{f(0 + h) - f(0)}{h}
= \lim_{h \to 0} hD(h) = 0
$$

即 $f$ 在 $z = 0$ 复可导。另一方面，任取 $z \neq 0$ 但 $f(z) = 0$，则有

$$
\frac{f(z + h) - f(z)}{h}
= \frac{(z + h)^2 D(z + h)}{h}
$$

显然对任意 $\epsilon > 0$，总存在 $|h| < \epsilon$ 使得 $D(z + h) = 1$，因此上式在 $h \to 0$ 时不收敛，进而 $f$ 在 $z = 0$ 的任一开邻域内不全纯。

## 形式幂级数环的拓扑

根据形式幂级数定义，我们猜想形式幂级数环 $\mathbb{C}\llbracket T \rrbracket$ 与多项式环 $\mathbb{C}[T]$ 之间必然存在某种联系。

为了阐明这种关系，需要在 $\mathbb{C}\llbracket T \rrbracket$ 上建立拓扑结构。

> 对于非零的形式幂级数 $P = \displaystyle\sum_{n \geq 0} a_n T^n \in \mathbb{C}\llbracket T \rrbracket$，定义它的一个 $T$-进赋值为
>
> $$ v_T(P) = \inf \\{ k \in \mathbb{N} : a_k \neq 0 \\} $$
>
> 特别地，规定 $v_T(0) = +\infty$。

容易证明，$\\| P \\|_T = e^{-v_T(P)}$ 是 $\mathbb{C}\llbracket T \rrbracket$ 上的范数。显然，范数 $\\| \cdot \\|_T$ 的定义可以直接应用于多项式环 $\mathbb{C}[T]$。

我们的结论是，形式幂级数环 $\mathbb{C}\llbracket T \rrbracket$ 是多项式环 $\mathbb{C}[T]$ 在范数 $\\| \cdot \\|_T$ 下的完备化。

有了范数之后就可以进一步导出度量，进而 $\mathbb{C}\llbracket T \rrbracket$ 成为一个完备的度量空间。

## 补充题

### 例 1

> 对于不等于 $2k \pi$ 的实数 $m, m$，求 $\displaystyle \sum_{k=0}^{r} \cos(m + kn)$ 以及 $\displaystyle \sum_{k=0}^{r} \sin(m + kn)$

从高中学过三角恒等变换之后就开始不断出现的经典题目。除了高中常用的用和差化积构造裂项，还可以用复数法做。

考虑和式

$$
\sum_{k=0}^{r} e^{i(m + kn)} = e^{im} \cdot \frac{1 - e^{in(r + 1)}}{1 - e^{in}}
$$

将其分母通分为实数

$$
\frac{1 - e^{in(r + 1)}}{1 - e^{in}}
= \frac{(1 - e^{in(r + 1)})(1 - e^{-in})}{(1 - e^{in})(1 - e^{-in})}
= \frac{1 + e^{irn} - e^{in(r + 1)} - e^{-in}}{2 - 2 \cos n}
$$

分别计算前述和式的实部和虚部可知

$$
\begin{align*}
  \sum_{k=0}^{r} \cos(m + kn) &= \frac{\cos m + \cos (m + rn) - \cos (m + (r + 1)n) - \cos (m - n)}{2 - 2 \cos n} \newline
  \sum_{k=0}^{r} \sin(m + kn) &= \frac{\sin m + \sin (m + rn) - \sin (m + (r + 1)n) - \sin (m - n)}{2 - 2 \cos n}
\end{align*}
$$

---

最后提一嘴，其实这学期复变课除了前三章以外还讲了一点点第八章（共形映射）的内容。但是由于讲的确实太少了所以就不单独开新文章总结了。
