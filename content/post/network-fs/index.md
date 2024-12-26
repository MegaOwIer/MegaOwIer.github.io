---
title: 挂载新硬盘并配置网络文件共享
slug: network-fs
date: 2022-11-13
lastmod: 2024-12-27
tags:
  - Network
  - NAS
categories:
  - DIY
description: 压榨吃灰树莓派的剩余价值（二）
draft: false
---


我手里的树莓派型号是 4B，内存 2G，装了一块 15G 的 SD 卡，外接一个 1T 的 HDD（本文中加装）。系统和上一篇一样仍然是 `Ubuntu Server 22.04.1 LTS`。今后如果没有特殊说明本系列中的设备硬件条件就都是这样了。

不管最终目的是私人影院，家庭监控，还是其他什么别的东西，网络文件共享都是不可绕过的一步。为方便不同设备的连接与使用，我一共装了两套工具：Samba 和 DLNA。

## 挂载硬盘

在此之前，树莓派 SD 卡那点小得可怜的存储空间显然支撑不起存储需求，所以得搞块硬盘。正好手里有一块不太用了的 1T 移动硬盘，就直接拿来用了。

硬盘插上去之后，理论上就能识别到了。

```sh
$ df -h
Filesystem      Size  Used Avail Use% Mounted on
tmpfs           185M  5.4M  180M   3% /run
/dev/mmcblk0p2   15G   13G  1.2G  92% /
tmpfs           923M     0  923M   0% /dev/shm
tmpfs           5.0M     0  5.0M   0% /run/lock
/dev/mmcblk0p1  253M  118M  135M  47% /boot/firmware
/dev/sda2       932G  233G  699G  25% 
tmpfs           185M  4.0K  185M   1% /run/user/1000
```

可以看到 `/dev/sda2` 就是我们的硬盘。直接挂载在某个地方就好了。我选择挂在 `/mnt/nas`，就是

```sh
sudo mount /dev/sda2 /mnt/nas
```

这样挂载是一次性的，重启之后就就没了。为了让它持久下去，需要修改 `/etc/fstab` 文件。`fstab` 文件中各个字段的含义可以参考[官方文档](https://help.ubuntu.com/community/Fstab)，其中 UUID 可以通过 `blkid` 指令获得

```sh {hl_lines=["4"]}
$ blkid
/dev/mmcblk0p1: LABEL_FATBOOT="system-boot" LABEL="system-boot" UUID="5D5B-8026" BLOCK_SIZE="512" TYPE="vfat" PARTUUID="354db354-01"
/dev/mmcblk0p2: LABEL="writable" UUID="a7c221ca-e02d-4446-8229-6c6cbd888234" BLOCK_SIZE="4096" TYPE="ext4" PARTUUID="354db354-02"
/dev/sda2: LABEL="New Volume" BLOCK_SIZE="512" UUID="2E22053422050317" TYPE="ntfs" PARTLABEL="Basic data partition" PARTUUID="fb69c1f6-82c4-4e2f-b6f6-a4286142accb"
```

可以发现硬盘的 UUID 是 `2E22053422050317`，因此在 `/etc/fstab` 中加入一行

```plain
UUID=2E22053422050317   /mnt/nas        ntfs    defaults        0       2
```

文件系统采用 NTFS 而非 EXT4 主要因为原来用的时候里边就是 NTFS。如果要用 EXT4 或者其他文件系统记得改第三项。

## Samba

首先安装 Samba

```sh
sudo apt update
sudo apt install samba
```

安装好后 Samba 应该已经启动了，可以通过命令 `sudo systemctl status nmbd` 查看其运行状态。正常情况下输出应该大致长这样

```sh
$ sudo systemctl status nmbd
● nmbd.service - Samba NMB Daemon
     Loaded: loaded (/lib/systemd/system/nmbd.service; enabled; vendor preset: enabled)
     Active: active (running) since Fri 2024-02-02 14:13:05 UTC; 1 day 23h ago
       Docs: man:nmbd(8)
             man:samba(7)
             man:smb.conf(5)
   Main PID: 870 (nmbd)
     Status: "nmbd: ready to serve connections..."
      Tasks: 1 (limit: 2100)
     Memory: 3.3M
        CPU: 16.370s
     CGroup: /system.slice/nmbd.service
             └─870 /usr/sbin/nmbd --foreground --no-process-group

Feb 02 14:13:01 ubuntu systemd[1]: Starting Samba NMB Daemon...
```

装好之后，打开配置文件，把我们前面挂载好的 `/mnt/nas` 加入共享。在配置文件末尾追加

```plain
[nas]
   comment = NAS
   path = /mnt/nas
   browseable = yes
   read only = no
```

如果要设置分用户访问权限，需要在 ubuntu 系统中添加对应的用户之后再在 SMB 配置文件中设置。如果你想做更多限制（如限制访客访问），可以参考[官方文档](https://www.samba.org/samba/docs/current/man-html/smb.conf.5.html)添加字段。

一切配置妥当之后重启 SMB，就可以在局域网中的任何设备（PC、iPad、手机等）上连接并挂载共享目录了。

## DLNA

如果我们有播放网络文件系统中的音视频文件的需求，DLNA 就是一个很好的选择。

首先安装 `MiniDLNA`

```sh
sudo apt update
sudo apt install minidlna
```

然后按需设置配置文件 `/etc/minidlna.conf` 中的 `media_dir`，`log_dir` 以及 `db_dir`。配置文件中对这玩意该怎么写有比较详细的解释，在此不赘述。当然你也可以根据实际情况修改配置文件中的其他选项，比较常用的有 `friendly_name`（显示名称）和 `inotify`（新文件监控）。

设置好后重启 MiniDLNA，不出意外的话可以通过浏览器访问 8200 端口查看 MiniDLNA 状态信息。此后就可以通过 VLC 等支持 DLNA 的播放器播放网络中共享的音视频了。

## 配置防火墙

这里采用 `ufw` 防火墙。如果你出于某种原因一定要用 `iptables`，那你大概率也不需要我教你怎么设置防火墙了。

Samba 在安装时会自动在 `/etc/ufw/applications.d/` 路径下生成一个名为 `samba` 的文件，里面有一个 `Samba` 配置可以直接用。例如，如果我想限制仅限 `192.168.31.0/24` 子网中的设备访问 SMB，添加规则

```sh
sudo ufw allow from 192.168.31.0/24 to any app Samba
```

MiniDLNA 就没这么好心了，但我们可以照葫芦画瓢搞一个配置文件 `/etc/ufw/applications.d/minidlna` 出来

```plain
[MiniDLNA]
title=MiniDLNA
description=MiniDLNA
ports=8200/tcp|1900/udp
```

然后再更新 `ufw` 状态并且添加规则

```sh
sudo ufw app update MiniDLNA
sudo ufw allow from 192.168.31.0/24 to any app MiniDLNA
```

## 关于 NFS

最早的时候我的文件系统采用的是 NFS 而非 Samba，但是在配防火墙的时候发现 NFS 总共会运行 `nfs`，`portmapper`，`rquotad`，`mountd`，`nlockmgr` 等一堆服务，其中只有前两个端口的固定的，每次重启 NFS 都会导致端口变更。然后就需要改配置让它固定端口，搞得很恼火，索性决定爆破掉 NFS。

如果你一定要用 NFS，可以参考[这篇文章](https://chenyongjun.vip/articles/73)解决这个问题。

## 后记

这篇教程其实早就写好了（见发布时间），由于某些原因一直在本地 draft 着没往上传。2024 年寒假回到家又开始折腾树莓派了，正好把之前存货的教程修缮一下和这次新折腾的东西一起发出来。同时，也把之前写的 IPv6 代理服务器的那篇文章进行简单扩充之后并入本系列。
