---
title: 挂载交换分区并安装 Home Assistant
slug: home-assistant
date: 2024-02-04
lastmod: 2024-02-05
tags:
  - HomeAssistant
  - Linux
categories:
  - DIY
description: 压榨吃灰树莓派的剩余价值（四）
draft: true
---

寒假回到家，突然意识到一个事情：如果我把树莓派单纯用来当 NAS，那两百块钱不到的工控机也可以做这件事，当初完全没必要花四五百买树莓派。

发现这个盲点之后，就在想怎么做才能搞一点只有树莓派才能做的事情，比如，在 GPIO 引脚上做做文章。正好最近智能家居那一套比较火，不如就先整一个温湿度传感器出来吧。

很快敲定了方案：搞一个 DHT22 温湿度传感器接到树莓派上，然后搓一个服务用来把温湿度数据提供给 Home Assistant。

## 交换分区

正当我打算安装 Home Assistant 的时候，发现了一个不太好的事实——树莓派 2G 的内存基本上跑满了。

内存不够用解决方案无非两种：加内存，或者搞 swap。众所周知，对于树莓派而言，扩充内存的代价比扩充外存代价略高，因此选择挂 4G swap 上去。考虑到原来那个抓来凑数用的 1T 机械移动硬盘前后总共服役了快七年了，这次索性顺带把硬盘也换上 SATA SSD。

### 创建分区

拿到新硬盘，通过扩展板接入树莓派，然后 `sudo fdisk -l` 一下发现新硬盘的设备叫 `/dev/sdb`。随后用 `fdisk` 在里面划一个 4G 的分区出来。

进入 `fdisk` 工具之后大概长这样：

```sh
$ sudo fdisk /dev/sdb

Welcome to fdisk (util-linux 2.37.2).

Changes will remain in memory only, until you decide to write them.
Be careful before using the write command.

Device does not contain a recognized partition table
Building a new DOS disklabel with disk identifier 0xdf6162ee

Command (m for help):
```

用 `n` 指令创建一个新的分区，分区类型、分区编号、分区起始位置如果没有特殊需要都保持默认即可。由于我们想要 4G 交换空间，所以在输入分区结束位置的时候可以直接输入 `+4G`。整个过程大概这样（注意高亮行的指令与参数输入）：

```sh {hl_lines=["1","5-7","9"]}
Command (m for help): n
Partition type:
   p   primary (0 primary, 0 extended, 4 free)
   e   extended
Select (default p): 
Partition number (1-4, default 1):
First sector (2048-195352516, default 2048): 
Using default value 2048
Last sector, +sectors or +size{K,M,G} (2048-195352516, default 195352516): +4G
Partition 1 of type Linux and of size 4 GiB is set

Command (m for help):
```

随后可以用 `p` 指令查看目前的分区情况。不出意外的话已经有了一个叫 `/dev/sdb1` 的分区，且这个分区的 `Id` 的值是 `83`。这个 `Id` 会用来告诉系统这个分区的作用，比如 `82` 代表 `Linux swap / Solaris`，`83` 代表 `Linux` 等等。你可以用 `l` 指令来查看全部的分区类型及其对应编号。

接下来，我们就需要用 `t` 指令将刚创建好的 `/dev/sdb1` 分区的类型设置为 `82`。

```sh {hl_lines=["2"]}
Command (m for help): t
Selected partition 1
Hex code (type L to list all codes): 82
Changed type of partition 'Linux' to 'Linux swap / Solaris'

Command (m for help):
```

如果你的硬盘此时已经有了多于一个分区，输入指令后的第一步（高亮处）会让你选择分区编号。

此时再用 `p` 检查一下是否符合预期，随后用 `w` 指令将对分区的修改落盘。

### 初始化并激活交换分区

创建好分区之后，我们需要用 `mkswap` 对其进行初始化，使其可以被用来存储从内存轮换出来的数据。这一步类似于创建常规分区之后初始化文件系统的步骤。

```sh
sudo mkswap /dev/sdb1
```

完成初始化后，分区 `/dev/sdb1` 已经可以被用作交换分区了。接下来只需要用 `swapon` 指令激活即可

```sh
sudo swapon /dev/sdb1
```

如果一切顺利，此时用 `free` 或者 `swapon -s` 指令就可以看到刚挂上去的 4G 交换空间了。

### 永久挂载

与之前[讲硬盘挂载的那篇文章]({{< ref "/network-fs" >}})类似，我们还需要在 `/etc/fstab` 里配置一下使得这个新的分区能在每次重启后挂载。`UUID` 参考前述文章获取，挂载点和文件系统都填 `swap`，最后两个参数都填 `0`。

## 安装 Home Assistant

现在我们可以假装有 6G 内存了，足够 Home Assistant 用了。直接用[官网](https://www.home-assistant.io/installation/alternative/#docker-compose)上提供的 `docker-compose.yaml` 安装即可。

```yaml
version: '3'
services:
  homeassistant:
    container_name: homeassistant
    image: "ghcr.io/home-assistant/home-assistant:stable"
    volumes:
      - ./config:/config
      - /etc/localtime:/etc/localtime:ro
      - /run/dbus:/run/dbus:ro
    restart: unless-stopped
    privileged: true
    network_mode: host
```

当然，由于众所周知的原因，通过直连 Github 下载镜像的网速不太理想。让 Docker Compose 走代理的设置方法可以参考 Stackoverflow 上的[这个回答](https://stackoverflow.com/a/54220188/11971817)。注意代理服务器的地址末尾要带上斜杠 `/`。

我本地试的时候只加上 `HTTP_PROXY` 不是很行，设了 `HTTPS_PROXY` 才有用，不过我网络苦手就没去深究到底是为啥。

至此 Home Assistant 就安装完了，你可以访问 8123 端口注册用户并且进行设置。至于文章开头提到的温湿度传感器，目前还在调试中，等没问题了之后再开贴。
