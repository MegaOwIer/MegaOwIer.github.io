#!/bin/bash

# CHANGE THESE
auth_email="__1__"      # CloudFlare 账户邮箱
auth_key="__2__"        # cloudflare 的 Globel ID
zone_name="__3__"       # 根域名
record_name="__4__"     # 完整域名
record_type="AAAA"      # A for ipv4 and AAAA for ipv6

ip_index="internet"     # "internet" or "local",使用本地方式还是网络方式获取地址
eth_card="__5__"        # 使用本地方式获取ip绑定的网卡，默认为eth0，仅本地方式有效

ip_file="$HOME/.local/ddns/ip.txt"            #保存地址信息,save ip information in the ip.txt
id_file="$HOME/.local/ddns/cloudflare.ids"
log_file="$HOME/.local/ddns/cloudflare.log"


if [ $record_type = "AAAA" ];then
    if [ $ip_index = "internet" ];then
        ip=$(curl -6 ip.sb)
    elif [ $ip_index = "local" ];then
        if [ "$user" = "root" ];then
            ip=$(ifconfig $eth_card | grep 'inet6'| grep -v '::1'|grep -v 'fe80' | cut -f2 | awk '{ print $2}' | head -1)
        else
            ip=$(/sbin/ifconfig $eth_card | grep 'inet6'| grep -v '::1'|grep -v 'fe80' | cut -f2 | awk '{ print $2}' | head -1)
        fi
    else
        echo "Error IP index, please input the right type"
        exit 0
    fi
elif [ $record_type = "A" ];then
    if [ $ip_index = "internet" ];then
        ip=$(curl -4 ip.sb)
    elif [ $ip_index = "local" ];then
        if [ "$user" = "root" ];then
            ip=$(ifconfig $eth_card | grep 'inet'| grep -v '127.0.0.1' | grep -v 'inet6'|cut -f2 | awk '{ print $2}')
        else
            ip=$(/sbin/ifconfig $eth_card | grep 'inet'| grep -v '127.0.0.1' | grep -v 'inet6'|cut -f2 | awk '{ print $2}')
        fi
    else
        echo "Error IP index, please input the right type"
        exit 0
    fi
else
    echo "Error DNS type"
    exit 0
fi

# 日志 log file
log() {
    if [ "$1" ]; then
        echo -e "[$(date)] - $1" >> $log_file
    fi
}

# SCRIPT START
# log "Check Initiated"

#判断ip是否发生变化,check the ip had been changed?
if [ -f $ip_file ]; then
    old_ip=$(cat $ip_file)
    if [ $ip == $old_ip ]; then
        echo "IP has not changed."
        exit 0
    fi
fi

#获取域名和授权 get the domain and authentic
if [ -f $id_file ] && [ $(wc -l $id_file | cut -d " " -f 1) == 2 ]; then
    zone_identifier=$(head -1 $id_file)
    record_identifier=$(tail -1 $id_file)
else
    zone_identifier=$(curl -s -X GET "https://api.cloudflare.com/client/v4/zones?name=$zone_name" \
        -H "X-Auth-Email: $auth_email" \
        -H "X-Auth-Key: $auth_key" \
        -H "Content-Type: application/json" | grep -Po '(?<="id":")[^"]*' | head -1 )
    record_identifier=$(curl -s -X GET "https://api.cloudflare.com/client/v4/zones/$zone_identifier/dns_records?type=${record_type}&name=$record_name" \
        -H "X-Auth-Email: $auth_email" \
        -H "X-Auth-Key: $auth_key" \
        -H "Content-Type: application/json"  | grep -Po '(?<="id":")[^"]*')
    echo "$zone_identifier" > $id_file
    echo "$record_identifier" >> $id_file
fi

#更新DNS记录 update the dns
update=$(curl -s -X PUT "https://api.cloudflare.com/client/v4/zones/$zone_identifier/dns_records/$record_identifier" \
    -H "X-Auth-Email: $auth_email" \
    -H "X-Auth-Key: $auth_key" \
    -H "Content-Type: application/json" \
    --data "{\"type\":\"$record_type\",\"name\":\"$record_name\",\"content\":\"$ip\",\"ttl\":300,\"proxied\":false}")


#反馈更新情况 gave the feedback about the update statues
if [[ $update == *"\"success\":true"* ]]; then
    message="IP changed to: $ip"
    echo "$ip" > $ip_file
    log "$message"
    echo "$message"
else
    message="API UPDATE FAILED. DUMPING RESULTS:\n$update"
    log "$message"
    echo -e "$message"
    exit 1
fi
