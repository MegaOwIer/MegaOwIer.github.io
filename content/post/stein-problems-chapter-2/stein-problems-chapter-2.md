---
title: Stein Complex Analysis 复分析第二章问题（Problems）解答
slug: stein-problems-chapter-2
date: 2022-12-28

tags:
  - Complex Analysis
categories:
  - Mathematics
  - RUC

description: 复变课的作业记录以及期末习题课的笔记
draft: false

lastmod: 2023-1-6
---

## 问题解答

{{< embed-pdf url="/post/stein-problems-chapter-2/ch2-prob.pdf" hidePaginator="false" >}}

以上是第二章 Problems 1-5 的解答。对于部分问题的额外注记会在后文写出。

---

## Problem 1

对于 (b) 小问，书上给出的 Hint 应该指的是 Stein 傅里叶分析第四章的定理 3.1：

> **引理**：如果 $0 < \alpha < 1$，则函数
>
> $$ f_{\alpha}(x) = \sum_{n=0}^{\infty} 2^{-n\alpha} e^{i 2^n x} $$
>
> 连续但处处不可微。

而 Stein 随后指出上面的结论对 $\alpha = 1$ 也是成立的。

## Problem 3

所谓[磨光算子](https://en.wikipedia.org/wiki/Mollifier)是指满足下列要求的函数 $\alpha$：

+ $\alpha$ 无穷次连续可微，即 $\alpha \in \mathscr{C}^{\infty}(\mathbb{R}^n)$
+ $\displaystyle \int_{\mathbb{R}^n} \alpha \textrm{d}x = 1$
+ $\alpha \geq 0$，且对任意 $|x| \geq 1$ 有 $\alpha(x) = 0$

一个常见的例子是

$$
\alpha(x) = \begin{cases}
    A \cdot \exp \left( \dfrac{1}{|x|^2 - 1} \right), & |x| < 1 \newline
    0, & |x| \geq 1
\end{cases}
$$

然后我们就可以用卷积给出磨光变换

$$
\begin{align*}
  J_{\epsilon} : && \mathscr{L}^p_{loc} &\longrightarrow \mathscr{C}^{\infty}(\mathbb{R}^n) \newline
    && u &\longmapsto \alpha_{\epsilon} * u
\end{align*}
$$

我们不加证明地指出磨光变换的一些性质：

+ $\left( J_{\epsilon}(u) \right)^{(m)} = \alpha_{\epsilon}^{(m)} * u$
+ 如果 $u \in \mathscr{C}(\mathbb{R})$，则 $\left( J_{\epsilon}(u) \right)' = J_{\epsilon}(u')$
+ 对于开集 $\Omega \in \mathbb{R}^n$ 以及 $u \in \mathscr{L}^p(\Omega)$ 其中 $1 \leq p < \infty$，有
  1. $\\| J_{\epsilon}u \\|_p \leq \\| u \\|_p$
  2. $\\| J_{\epsilon}u - u \\|_p \to 0$ 当 $\epsilon \to 0$
+ 对于开集 $\Omega \in \mathbb{R}^n$ 以及 $u \in \mathscr{C}^0(\Omega)$，当 $\epsilon \to 0$ 时函数列 $J_{\epsilon}u$ 内闭一致收敛至 $u$

## Problem 5

这个题是 G. Birkhoff 在 1929 年提出的一个定理。原文标题为 Démonstration d'un théorème elémentaire sur les fonctions entiéres，有兴趣的同学可以自行找到原文（法语）阅读。

相较于上面文档中给出的证明，[这个链接](https://math.stackexchange.com/questions/663164/f-entire-with-lim-k-rightarrow-infty-fz-n-k-hz-for-every-h)中还给出了一个相对来说更加简短的证明。
