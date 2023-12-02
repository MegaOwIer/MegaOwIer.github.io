---
title: GAMES101 注记（一）：光栅化
slug: games101-1
date: 2023-10-07
tags:
  - GAMES101
categories:
  - SJTU
description: 主要还是 review 一下之前写的作业代码
draft: true
lastmod: 2023-12-03
---

## MVP 变换

借用课上的拍照的例子，Model 变换是拍照前摆弄一下被拍的物品，View 变换是保持**相机和物品相对位置**不变的情况下把相机挪到原点并且朝向 $-z$ 方向，Projection 变换则是按下快门拍照。

具体到作业一中，Model 变换负责处理按下 `A` 和 `D` 之后三角形的旋转。

Projection 所做的工作是透视投影，课上将其分成两个小步：先将远近平面之间所夹的棱台通过一个看上去很诡异的线性变换变成长方体，再把这个长方体经过平移和放缩变成 $[-1, 1]^3$。

由于作业框架内的远近平面都是用距离而非坐标表示，这就导致实际写的时候不能直接抄课件。前半部分直接加上负号即可，后半部分需要注意的一个事情是加负号之后区间 $[n, f]$ 变成 $[-n, -f]$ 是一个被翻转的区间，所以需要一个额外的负号把它翻回 $[-f, -n]$。

## 深度测试与 Super Sampling

深度测试本身没甚至好说的地方，这种思想在算法竞赛中太平凡了，写起来就和玩一样。

至于 Super Sampling，实现上需要注意的点在作业二文档中也写的很明确：「对于像素内的每一个样本都需要维护它自己的深度值」，因此写的时候需要微微调整一下相关数组的大小，顺带调整一堆初始化代码。

问题出现在「深度」上。

代码模板里关于深度插值的代码段大概长成这样

```c++
auto [alpha, beta, gamma] = computeBarycentric2D(x, y, t.v);
float w_reciprocal = 1.0 / (alpha / v[0].w() + beta / v[1].w() + gamma / v[2].w());
float z_interpolated = alpha * v[0].z() / v[0].w() + beta * v[1].z() / v[1].w() + gamma * v[2].z() / v[2].w();
z_interpolated *= w_reciprocal;

```

从第三行可以大概猜出来每个顶点 $z$ 坐标应该存的是深度信息，但最终深度 `z_interpolated` 并没有如预期那样严格按照重心坐标加权平均而来，而是在权重上做了点手脚。

## 重心坐标

我们再稍微回退一点。作业代码框架里的 `computeBarycentric2D` 函数为啥是对的？重心坐标本身又为啥是对的？

我们高中数学学过一个结论：

> 对 $\triangle ABC$ 及平面内一点 $P$，有
>
> $$ S_{\triangle PBC} \cdot \overrightarrow{PA} + S_{\triangle PCA} \cdot \overrightarrow{PB} + S_{\triangle PAB} \cdot \overrightarrow{PC} = \vec{0} $$

重心坐标的正确性可以直接从上述结论直接推出。

## 关于 Bonus

### 作业一

绕任意轴 $\vec{n}$ 的旋转矩阵的构造，本质上是要找两个向量 $\vec{x}$ 和 $\vec{y}$ 使得 $\vec{x}, \vec{y}$ 和 $\vec{n}$ 两两正交且成右手系。事实上，如果知道 $\vec{x}$ 和 $\vec{y}$，我们总是可以通过坐标变换把问题转换为绕 $z$ 轴旋转，进而通过相似矩阵构造出需要的旋转矩阵。

这里给出一种可能的构造方式，证明从略。

```c++
Eigen::Vector3f _x, _y;
if (_n.x() == 0) {
    _x << 0, -_n.z(), _n.y();
    _y = _n.cross(_x);
} else {
    _x << _n.y(), -_n.x(), 0;
    _y = _n.cross(_x);
}

```

Tips: 可以通过将 $\vec{x}, \vec{y}, \vec{n}$ 长度化为 $1$ 把求相似矩阵时必不可少的求逆操作简化为求转置，加速计算。
