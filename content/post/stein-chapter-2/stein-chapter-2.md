---
title: Stein Complex Analysis 复分析第二章复习提纲
slug: stein-chapter-2
date: 2022-12-27

tags:
  - Complex Analysis
categories:
  - Mathematics
  - RUC

description: 复变课的作业记录以及期末习题课的笔记
draft: false

lastmod: 2022-12-28
---

## Cauchy 积分公式的逆定理

这本书在 2.4 节介绍了 Cauchy 积分公式。事实上这一结论的逆定理也成立

> **定理**：设 $D$ 为复平面上的圆盘，$f$ 是 $C = \partial D$ 上的连续函数，则函数
>
> $$ F(z) = \frac{1}{2\pi i} \int_{C} \frac{f(\xi)}{\xi - z} \textrm{d}\xi $$
>
> 在 $D$ 上全纯。

取定 $z \in D$，我们有

$$
\begin{align*}
  F(z + h) - F(z)
  &= \frac{1}{2\pi i} \int_{C} \frac{f(\xi)}{\xi - (z + h)} \textrm{d}\xi - \int_{C} \frac{f(\xi)}{\xi - z} \textrm{d}\xi \newline
  &= \frac{1}{2\pi i} \int_{C} \frac{hf(\xi)}{(\xi - (z + h))(\xi - z)} \textrm{d}\xi
\end{align*}
$$

当 $|h|$ 充分小时，有

$$
\lim_{h \to 0} \frac{F(z + h) - F(z)}{h}
= \frac{1}{2\pi i} \int_{C} \frac{f(\xi)}{(\xi - z)^2} \textrm{d}\xi
$$

显然 $\dfrac{f(\xi)}{(\xi - z)^2}$ 连续，进而可积，由此 $F'(z)$ 存在。

值得一提的是，由定理得到的 $F$ 在 $C$ 附近**并不一定**收敛到 $f$。与之相关的讨论可以参考 [A converse to Cauchy's integral formula](https://math.stackexchange.com/questions/3132035/a-converse-to-cauchys-integral-formula)。

---

需要注意的是，上面的命题中曲线 $C$ 是选定的，即与 $z$ 无关。如果曲线的选取与 $z$ 有关的话这个命题不一定成立。

> **命题**：若开集 $\Omega$ 上的函数满足：对任意 $z \in U$ 及以 $z$ 为圆心的圆圈 $C(z, r) \subset \Omega$ 有
>
> $$ f(z) = \int_{C(z, r)} \frac{f(\xi)}{\xi - z} \textrm{d}\xi $$
>
> 则 $f$ 不一定在 $\Omega$ 上全纯。

事实上，任意调和函数均满足上述条件（参考 3.7 节推论 7.3），但调和函数不必全纯。

## 全纯函数零点的孤立性

这本书在 2.4 节最后简要介绍了解析延拓及其唯一性，以及与之相关的一个性质是零点的孤立性。

实际上，利用零点的孤立性已经可以给出后面第三章极大模原理的证明。

> **定理（极大模原理）**：若 $\Omega$ 为 $\mathbb{C}$ 中的连通开集，$f$ 在 $\Omega$ 上全纯。若存在 $z_0 \in \Omega$ 使得 $|f|$ 在 $z_0$ 取到局部极大值，则 $f$ 在 $\Omega$ 上取常值。

若 $f$ 非常值，则 $f - f(z_0)$ 在 $\Omega$ 上不恒为 $0$，进而存在非零复数 $\alpha$ 使得在 $z_0$ 附近有

$$
f(z) = f(z_0) + \alpha (z - z_0)^k + O(|z - z_0|^{k+1})
$$

其中 $k$ 为 $z_0$ 作为函数 $f - f(z_0)$ 零点的阶。

若 $f(z_0) = 0$，则由 $z_0$ 是孤立零点可知在 $z_0$ 附近有 $f(z) \neq 0$，即

$$
|f(z)| > |f(z_0)| = 0, \qquad \forall z \neq z_0
$$

若 $f(z_0) \neq 0$，可以取复数 $\beta$ 使得 $\beta^k = \alpha^{-1}f(z_0)$，对足够小的 $t \in \mathbb{R}$ 有

$$
f(z_0 + t\beta) = f(z_0) \left( 1 + t^k + O(t^k) \right)
$$

易知 $|f(z_0)|$ 不可能为 $|f|$ 的极大值。

## 由积分构造全纯函数

这本书在 2.5.3 节证明了用积分构造全纯函数的可行性，即定理 5.4。实际上这个定理条件中对 $F$ 的连续性的要求可以进一步弱化

> **定理**：设 $X$ 是 $\mathbb{R}^m$ 中的可测子集，$\Omega$ 为 $\mathbb{C}$ 中开集，函数 $F : \Omega \times X \to \mathbb{C}$ 满足
> 
> 1. 对于任意 $t_0 \in X$，$F(z, t_0)$ 作为 $z$ 的函数在 $\Omega$ 上全纯；
> 2. 对于任意 $z_0 \in \Omega$，$F(z_0, t)$ 作为 $t$ 的函数是可测的，并且存在 $r_0 > 0$ 以及 $g_0 \in \mathscr{L}^1(X)$ 使得在 $D(z_0, r_0) \times X$ 上有 $|F(z, t)| \leq g_0(t)$，
>
> 则函数 $f(z) = \displaystyle\int_{X} F(z, t) \textrm{d}t$ 在 $\Omega$ 上全纯。

固定 $z_0 \in \Omega$，我们尝试证明 $f$ 在 $D(z_0, r_0)$（这里 $r_0$ 由定理条件 2 给出）上全纯。

由条件 1 可知对于 $D(z_0, r)$ 中的点 $z$ 有

$$
f(z) = \int_{X} F(z, t) \textrm{d}t
= \frac{1}{2\pi i} \int_{X} \int_{C(z_0, r_0)} \frac{F(\xi, t)}{\xi - z} \textrm{d}\xi \textrm{d}t
$$

注意到条件 2 中提供了一个控制函数 $g_0$，故在 $C(z_0, r_0) \times X$ 上有

$$
\left| \frac{F(\xi, t)}{\xi - z} \right|
\leq \frac{g_0(t)}{|(\xi - z_0) + (z_0 - z)|}
\leq \frac{g_0(t)}{r_0 - |z_0 - z|}
$$

注意到上式右端分母为常数，故其在 $C(z_0, r_0) \times X$ 上可积，于是可以利用 Fubini 定理对积分换序，即

$$
f(z)
= \frac{1}{2\pi i} \int_{C(z_0, r_0)} \frac{1}{\xi - z} \int_{X} F(\xi, t) \textrm{d}t \textrm{d}\xi
= \frac{1}{2\pi i} \int_{C(z_0, r_0)} \frac{f(\xi)}{\xi - z} \textrm{d}\xi
$$

进而由 Cauchy 积分公式的逆命题可知 $f$ 在 $D(z_0, r_0)$ 上全纯。

更进一步地，还可以得到

$$
f^{(k)}(z) = \int_{X} \left( \frac{\partial}{\partial z} \right)^k F(z, t) \textrm{d}t
$$

证明从略。

## 全纯函数与调和函数

> **引理**：任一实调和函数 $u(x, y)$ 在局部上为一个全纯函数 $f(x + iy)$ 的实部。

记 $ g(z) = \partial_x u - i \cdot \partial_y u = 2 \partial_z u $，容易验证 $g$ 满足 Cauchy-Riemann 方程，因此全纯，进而在 $z_0$ 附近有原函数 $f$。

不难验证上面构造的 $f$ 的实部与 $u$ 相差一个实数。

由此可知，和全纯函数一样，调和函数在区域边界的取值也可以决定其在区域内的取值。

## 补充题

### 例 1

> 设 $f$ 为在闭圆盘 $\overline{D} = \\{ z \in \mathbb{C} : |z| \leq R \\}$ 上的全纯函数，且在圆圈 $\partial D$ 上有上界 $M$，则
> $$ |f(z) - f(0)| \leq \frac{2M|z|}{R} $$

这个题用 Cauchy 积分公式进行放缩很容易放过，因此考虑极大模原理。

记 $g(z) = \dfrac{f(z) - f(0)}{z}$，由 $f$ 全纯可知 $z = 0$ 是 $g$ 的可去奇点，进而 $g$ 在 $D$ 上全纯。而 $g$ 在圆圈 $\partial D$ 上有上界

$$
|g(z)| = \frac{|f(z) - f(0)|}{R} \leq \frac{|f(z)| + |f(0)|}{R} \leq \frac{2M}{R}
$$

故由极大模原理可知在圆盘 $D$ 上有

$$
\frac{|f(z) - f(0)|}{|z|} \leq \frac{2M}{R}
$$

### 例 2

> 设函数 $f(t)$ 分段连续且在正实轴上一致有界，则积分
>
> $$ g(z) = \int_{0}^{+\infty} f(t)e^{-zt} \textrm{d}t $$
>
> 在右半平面 $\\{ z \in \mathbb{C} : \operatorname{Re}(z) > 0 \\}$ 上全纯。

直接套用上面的定理即可。

按理说应该也可以用含参变量积分那一套理论来证明，但貌似将积分的收敛性从内闭一致收敛推到收敛比较困难。
