---
title: Stein Complex Analysis 复分析第三章复习提纲与习题（Exercises）解答
slug: stein-chapter-3
date: 2022-12-25

tags:
  - Complex Analysis
categories:
  - Mathematics
  - RUC

description: 复变课的作业记录以及期末习题课的笔记
draft: false

lastmod: 2022-12-26
---

## 用留数定理计算实积分

这本书只在 3.2 节举了几例说明可以用留数定理计算实积分。实际上计算积分还有很多“套路”，这里参照钟玉泉《复变函数论》的 6.3 节简单归纳一下。

### 三角函数相关积分

对于形如 $\displaystyle \int_{0}^{2\pi} R(\cos \theta, \sin \theta) \textrm{d} \theta$ 的积分，可以考虑通过换元 $z = e^{i \theta}$ 讲实积分转换回沿复平面上单位圆圈的积分。参照 Exercise 7 和 8。

此外，如果被积函数是 $f(z) \sin z$ 的形式，可以考虑对 $f(z) e^{iz}$ 求积分然后考察其虚部。

### 一些结论

> **引理 1**：设 $f(z)$ 在圆弧 $S_R : z = R e^{i \theta},(\theta_1 \leq \theta \leq \theta_2)$ 上连续，且
>
> $$ \lim_{R \to +\infty} z f(z) = \lambda $$
>
> 在 $S_R$ 上一致成立，则
>
> $$
> \lim_{R \to +\infty} \int_{S_R} f(z) \textrm{d}z = i \lambda (\theta_2 - \theta_1)
> $$

引理 1 表明，如果在圆弧 $S_R$ 上有 $|f(z)| = o(R^{-1})$，则 $f$ 在 $S_R$ 上的积分收敛至 $0$。

> **引理 2 (Jordan)**：设 $f(z)$ 在半圆周 $S_R : z = R e^{i \theta},(0 \leq \theta \leq \pi)$ 上连续，且
>
> $$ \lim_{R \to +\infty} f(z) = 0 $$
>
> 在 $S_R$ 上一致成立，则对任意 $m > 0$ 有
>
> $$
> \lim_{R \to +\infty} \int_{S_R} f(z) e^{imz} \textrm{d}z = 0
> $$

上述结论的证明直接放缩即可。证明过程中可能用到的一个结论是当 $0 \leq \theta \leq \dfrac{\pi}{2}$ 时有 $\dfrac{2\theta}{\pi} \leq \sin \theta \leq \theta$。

> **引理 3**：设 $f(z)$ 在圆弧 $S_r : z = a + r e^{i \theta},(\theta_1 \leq \theta \leq \theta_2)$ 上连续，且
>
> $$ \lim_{r \to 0} (z - a) f(z) = \lambda $$
>
> 在 $S_r$ 上一致成立，则
>
> $$
> \lim_{r \to 0} \int_{S_r} f(z) \textrm{d}z = i \lambda (\theta_2 - \theta_1)
> $$

引理 3 为构造积分路径过程中绕过路径上的奇点提供了便利。

### 有理函数相关的积分

计算形如 $\displaystyle \int_{-\infty}^{+\infty} \dfrac{P(x)}{Q(x)} \textrm{d} x$ 的积分时，可以考虑以上半圆周为辅助曲线，应用前述引理 1 解决。

计算形如 $\displaystyle \int_{-\infty}^{+\infty} \dfrac{P(x)}{Q(x)} e^{imx} \textrm{d} x$ 的积分时，可以考虑以上半圆周为辅助曲线，应用前述引理 2 解决。

## Picard 定理

这本书在 3.3 节的 Casorati-Weierstrass 定理之后提及了 Picard 的结论，这里对其进行补充：

**Picard 小定理**：非常值整函数 $f$ 的值域 $f(\mathbb{C})$ 只可能为 $\mathbb{C}$ 或 $\mathbb{C} - \\{ z_0 \\}$。

**Picard 大定理**：若 $f$ 为全纯函数，$\omega$ 为其本性奇点，则对 $\omega$ 的任意开邻域 $\Omega$，至多存在一个 $z_0 \in \mathbb{C}$ 使得 $f^{-1}(z_0) \cap \Omega$ 是有限集（或空集）。

例如，对于函数 $f(z) = e^{1/z}$ 而言 Picard 大定理中的 $z_0 = 0$。

## 含无穷远点的柯西积分公式

> **定理**：设 $C$ 是扩展复平面 $\overline{\mathbb{C}}$ 上一条不经过点 $\infty$ 的曲线，$D$ 是其包含无穷远点的一侧，$f$ 在 $D$ 上全纯且可连续延拓到 $C$ 上，则
>
> $$
> \begin{equation*}
>   \frac{1}{2\pi i} \int_{C^{-}} \frac{f(\xi)}{\xi - z} \textrm{d} \xi = \begin{cases}
>     f(z) - f(\infty), & z \in D \\
>     - f(\infty), & z \notin \overline{D}
>   \end{cases}
> \end{equation*}
> $$

利用上述结论可以简化一些积分的计算。

> **例**：求积分
> $$ \int_{C} \frac{\textrm{d}z}{(z - 1)(z - 3)\cdots(z - 2023)} $$
> 其中 $C$ 是以 $0$ 为圆心，$2022$ 为半径的正向圆周。

通常的求解方式是计算出被积函数在 $2k + 1$ 处的留数并求和，并通过观察发现这些留数可两两抵消以简化计算结果。

实际上，我们还可以取

$$
f(z) = \frac{1}{(z - 1)(z - 3)\cdots(z - 2021)}
$$

则由上述定理可知

$$
\frac{1}{2\pi i} \int_{C^{-}} \frac{f(\xi)}{\xi - 2023} \textrm{d} \xi
= f(2023) = \frac{1}{2022!!}
$$

从而所求积分

$$
\int_{C} \frac{\textrm{d}z}{(z - 1)(z - 3)\cdots(z - 2023)}
= - \int_{C^{-}} \frac{f(\xi)}{\xi - 2023} \textrm{d} \xi
= - \frac{2\pi i}{2022!}
$$

## $\cot \pi z$ 的有界性

我们将证明以下命题：

> 对于任意给定的正整数 $n$，在圆周 $|z| = n + \dfrac{1}{2}$ 上 $\cot z$ 一致有界。

记 $z = x + iy$，不难验证此时必然有 $|y| > 1$ 或 $|x| > n + \dfrac{1}{4}$。

当 $|y| > 1$ 时有

$$
\begin{equation*}
  |\cot \pi z|
  = \left| \frac{e^{i \pi z} + e^{-i \pi z}}{e^{i \pi z} - e^{-i \pi z}} \right|
  \leq \frac{|e^{i \pi z}| + |e^{-i \pi z}|}{||e^{i \pi z}| - |e^{-i \pi z}||}
  = \frac{e^{2\pi |y|} + 1}{e^{2\pi |y|} - 1}
  \leq \frac{e^{2\pi} + 1}{e^{2\pi} - 1}
\end{equation*}
$$

而当 $|x| > n + \dfrac{1}{4}$ 时，$\cos (2\pi x) < 0$，进而

$$
\begin{align*}
  |\cot \pi z|
  &= \left| \frac{e^{i \pi z} + e^{-i \pi z}}{e^{i \pi z} - e^{-i \pi z}} \right|
  \leq 1 + \frac{2}{|e^{2i \pi z} - 1|} \\\\
  &\leq 1 + \frac{2}{|\operatorname{Re} (e^{2i \pi z} - 1)|}
  = 1 + \frac{2}{1 - e^{-2\pi y} \cos (2\pi x)} < 3
\end{align*}
$$

## 习题解答

下面给出第三章 Exercises 1-22 的解答。

{{< embed-pdf url="/post/stein-chapter-3/chpt-3-ex.pdf" hidePaginator="false" >}}
