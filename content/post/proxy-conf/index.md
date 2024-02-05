---
title: 校园网 IPv6 免流量上网配置过程
slug: proxy-conf
date: 2022-10-11
lastmod: 2024-02-04
tags:
  - Network
  - Linux
categories:
  - DIY
description: 压榨吃灰树莓派的剩余价值（一）
draft: false
---

根据 RUC 校园网计费规则，通过 IPv6 访问互联网无论上传还是下载均不收费。一个自然的想法是合理利用这个规则来节省高达 $100 \\%$ 的网费。运营商正好给我家分配了公网 v6 地址，所以我 19 年就买了个树莓派搭了代理服务器。

今年暑假我闲得没事想在树莓派上搭一个 QQbot 结果玩崩了，现在正巧又赶上因为疫情回不了学校，心想着索性把树莓派上的代理服务器之类的东西全部推倒重搭一遍。

系统采用的是 `Ubuntu Server 22.04.1 LTS`。在云服务器上配置操作同理。

## 安装 Shadowsocks

首先安装 `pip`，然后通过 `pip` 安装 `shadowsocks` 模块。

```sh
sudo apt install python3-pip
sudo pip install shadowsocks
```

这个过程中可能 `pip` 会报警告劝你不要用管理员权限运行 `pip`。但是由于 `shadowsocks` 运行时需要管理员权限，为了图省事还是直接 `sudo` 了。当然这里相对更好的办法是新建一个用户，给上管理员权限，禁掉登录之后专门用来跑 `ssserver`，虽然也就三四行指令，但我懒得搞。

完成后可以运行 `ssserver -help` 检查是否已经安装成功。这之后需要创建 Shadowsocks 的配置文件。我的配置文件大概长这个样子：

```json {linenos=table}
{
    "server": "server-name",
    "port_password": {
        "port": "password"
    },
    "local_address": "127.0.0.1",
    "local_port": 1080,
    "timeout": 300,
    "method": "aes-256-cfb",
    "fast_open": false
}
```

如果想多用户分开端口的话可以在 `port_password` 中添加。配置文件的具体写法可以参考 Shadowsocks 在 Github 上的 [Wiki](https://github.com/shadowsocks/shadowsocks/wiki/Configuration-via-Config-File)。

之后直接启动即可。

```sh
sudo ssserver -c ~/.local/shadowsocks/config.json -d start
```

根据几年前的使用经验，这个 `ssserver` 运行时间过长会寄掉，原因不明，因此我还在 `crontab` 里设置了每天定期重启代理服务器。

至此代理服务器配置完成，在代理软件客户端设置连接即可。如果连接不上，先检查一下机器是否开了防火墙，如果开了记得添加相应端口的放行规则。

## 脚本兼容性

由于我的系统是 `Ubuntu 22.04`，预装的 python 版本是 `3.10.6`，其中个别 API 与 `shadowsocks` 模块的调用不一致，需要进行调整。

在运行 `ssserver` 时可能会遇到如下报错：

```sh {hl_lines=["9-11"]}
$ ssserver --help
Traceback (most recent call last):
  File "/usr/local/bin/ssserver", line 5, in <module>
    from shadowsocks.server import main
  File "/usr/local/lib/python3.10/dist-packages/shadowsocks/server.py", line 27, in <module>
    from shadowsocks import shell, daemon, eventloop, tcprelay, udprelay, \
  File "/usr/local/lib/python3.10/dist-packages/shadowsocks/udprelay.py", line 71, in <module>
    from shadowsocks import encrypt, eventloop, lru_cache, common, shell
  File "/usr/local/lib/python3.10/dist-packages/shadowsocks/lru_cache.py", line 34, in <module>
    class LRUCache(collections.MutableMapping):
AttributeError: module 'collections' has no attribute 'MutableMapping'
```

解决方案是将 `/usr/local/lib/python3.10/dist-packages/shadowsocks/lru_cache.py` 中的全部 `collections.MutableMapping` 替换为 `collections.abc.MutableMapping`。

另外还有可能遇到类似 `undefined symbol: EVP_CIPHER_CTX_cleanup` 的错误，解决方案是将对应文件中的 `EVP_CIPHER_CTX_cleanup()` 全部替换为 `EVP_CIPHER_CTX_reset()`。

上述两个问题都是由使用的系统/软件版本过新导致，并不影响使用。

参考文献：[Ubuntu 18.04 下解决 shadowsocks 服务报错问题](https://floperry.github.io/2019/02/24/2018-06-25-Ubuntu-18.04-%E4%B8%8B%E8%A7%A3%E5%86%B3-shadowsocks-%E6%9C%8D%E5%8A%A1%E6%8A%A5%E9%94%99%E9%97%AE%E9%A2%98/)

## DDNS

出于安全考虑，运营商分配的公网地址大概率不是静态的，为了保证长期相对稳定的使用体验还需要配一下 DDNS。

相关教程网上一搜一大堆，我自己用的基于 Cloudflare 的方案，至于脚本早就忘了从哪个教程贴偷的了。贴到这里供有需要的人使用。

{{< highlight-content file="ddns-cloudflare.sh" lang="sh" >}}

使用时候注意修改前几行的信息即可。至于 `zone_name` 和 `record_name` 的区别，举个例子，假设你的域名是 `example.com`，然后你打算给你的代理服务器分配 `proxy.example.com`，则 `zone_name` 填 `example.com`，`record_name` 填 `proxy.example.com`。

## 后记

随着本科毕业，成功升学可以免费使用千兆网络的 SJTU，树莓派上的代理服务器也完成了其历史使命，光荣退休。
