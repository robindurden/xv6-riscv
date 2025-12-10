# 04 Linux
## CDC-NCM
Communications Device Class — Network Control Model

`ifconfig`
```bash
ifconfig

en12: flags=8863<UP,BROADCAST,SMART,RUNNING,SIMPLEX,MULTICAST> mtu 1500
	options=404<VLAN_MTU,CHANNEL_IO>
	ether 8e:87:e6:a5:46:5a
	inet6 fe80::4cf:1b4f:fabc:9dc6%en12 prefixlen 64 secured scopeid 0x24 
	inet 192.168.42.218 netmask 0xffffff00 broadcast 192.168.42.255
	nd6 options=201<PERFORMNUD,DAD>
	media: autoselect (100baseTX <full-duplex>)
	status: active
```

`networksetup`
```bash
networksetup -listallhardwareports
Hardware Port: NCM
Device: en12
Ethernet Address: 8e:87:e6:a5:46:5a


robin@mbp ~  % networksetup -getinfo NCM
DHCP Configuration
IP address: 192.168.42.218
Subnet mask: 255.255.255.0
Router: (null)
Client ID: 
IPv6: Automatic
IPv6 IP address: none
IPv6 Router: none
Ethernet Address: 8e:87:e6:a5:46:5a
```
## ssh
```bash
ping 192.168.42.1
robin@mbp ~  % ssh root@192.168.42.1
root@192.168.42.1's password:  milkv

```
## linux
#### Milk-V DuoS System Configuration Summary

| Category | Item | Value |
|---------|------|-------|
| **CPU / Architecture** | Architecture | `riscv64` |
|  | Kernel | `Linux 5.10.4-tag` |
|  | Build Time | `Fri Nov 22 13:36:20 CST 2024` |
| **Memory** | Total RAM | `316 MB` |
|  | Free RAM | `~280 MB` |
|  | Swap | `None` |
| **Storage (SD Card)** | Device | `/dev/mmcblk0` |
|  | Size | `14.65 GiB` |
|  | `/boot` | 128 MB FAT32 (`/dev/mmcblk0p1`) |
|  | `/` | 768 MB ext4 (`/dev/mmcblk0p3`) |
| **USB Networking (CDC-NCM)** | USB Interface | `usb0` |
|  | IP Address | `192.168.42.1/24` |
|  | MAC Address | `1a:1b:e5:0f:6b:b7` |
|  | Link State | `UP, LOWER_UP` |
|  | Host-side (macOS) | Interface: `en12` / IP: `192.168.42.218` |
| **Ethernet (PHY)** | Interface | `eth0` |
|  | State | `NO-CARRIER` (cable not connected) |
|  | IP | none |
| **Wi-Fi** | Interface | `wlan0` |
|  | IP | `169.254.77.8` (link-local only, not connected) |
|  | MAC Address | `88:00:33:77:b0:54` |
| **Routing Table** | USB Network Route | `192.168.42.0/24 dev usb0 src 192.168.42.1` |
|  | Default Route | via WLAN (`169.254.77.8`, fallback only) |
| **Running Services** | SSH Server | `dropbear` |
|  | DHCP Client | `dhcpcd` |
|  | DNS | `dnsmasq` |
|  | Time Sync | `ntpd` |
| **System State** | Bootloader | SD card |
|  | Root FS | ext4 |
|  | USB Gadget Mode | CDC-NCM (active) |

#### Key Status Summary

| Feature | Status | Notes |
|---------|--------|-------|
| USB-C networking | ✔ Working | macOS ↔ DuoS over CDC-NCM |
| SSH over USB | ✔ Ready | `ssh root@192.168.42.1` |
| Ethernet | ⭕ Available but cable unplugged | `eth0` shows NO-CARRIER |
| Wi-Fi | ⭕ Not connected | Only link-local IP (169.254.x.x) |
| Storage | ✔ Healthy | Correct 3-partition layout |
| CPU / Kernel | ✔ Normal | RISC-V 64, 5.10 kernel |
```
[root@milkv-duo]~# uname -a
Linux milkv-duo 5.10.4-tag- #1 PREEMPT Fri Nov 22 13:36:20 CST 2024 riscv64 GNU/Linux
[root@milkv-duo]~# uname -m
riscv64
[root@milkv-duo]~# fdisk -l
Disk /dev/mmcblk0: 14.65 GiB, 15728640000 bytes, 30720000 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disklabel type: dos
Disk identifier: 0x00000000

Device         Boot  Start     End Sectors  Size Id Type
/dev/mmcblk0p1 *         1  262144  262144  128M  c W95 FAT32 (LBA)
/dev/mmcblk0p2      262145  266240    4096    2M  0 Empty
/dev/mmcblk0p3      266241 1839104 1572864  768M 83 Linux
[root@milkv-duo]~# lsblk
NAME        MAJ:MIN RM  SIZE RO TYPE MOUNTPOINT
mmcblk0     179:0    0 14.6G  0 disk 
|-mmcblk0p1 179:1    0  128M  0 part /boot
|-mmcblk0p2 179:2    0    2M  0 part 
`-mmcblk0p3 179:3    0  768M  0 part /
[root@milkv-duo]~# mount
/dev/root on / type ext4 (rw,relatime,errors=remount-ro)
devtmpfs on /dev type devtmpfs (rw,relatime,size=162136k,nr_inodes=40534,mode=755)
proc on /proc type proc (rw,relatime)
devpts on /dev/pts type devpts (rw,relatime,gid=5,mode=620,ptmxmode=666)
tmpfs on /dev/shm type tmpfs (rw,relatime,mode=777)
tmpfs on /tmp type tmpfs (rw,relatime)
tmpfs on /run type tmpfs (rw,nosuid,nodev,relatime,mode=755)
sysfs on /sys type sysfs (rw,relatime)
debug on /sys/kernel/debug type debugfs (rw,relatime)
/dev/mmcblk0p1 on /boot type vfat (rw,relatime,fmask=0022,dmask=0022,codepage=437,iocharset=iso8859-1,shortname=mixed,errors=remount-ro)
none on /tmp/usb type configfs (rw,relatime)
[root@milkv-duo]~# df -h
Filesystem      Size  Used Avail Use% Mounted on
/dev/root       752M  186M  525M  27% /
devtmpfs        159M     0  159M   0% /dev
tmpfs           159M     0  159M   0% /dev/shm
tmpfs           159M  116K  159M   1% /tmp
tmpfs           159M   36K  159M   1% /run
/dev/mmcblk0p1  128M  4.5M  124M   4% /boot
[root@milkv-duo]~# free -h
              total        used        free      shared  buff/cache   available
Mem:         316.8M       22.6M      279.9M      152.0K       14.4M      286.6M
Swap:             0           0           0
[root@milkv-duo]~# ps
PID   USER     COMMAND
    1 root     init
    2 root     [kthreadd]
    3 root     [rcu_gp]
    4 root     [rcu_par_gp]
    7 root     [kworker/u2:0-ev]
    8 root     [mm_percpu_wq]
    9 root     [ksoftirqd/0]
   10 root     [rcu_preempt]
   11 root     [kdevtmpfs]
   12 root     [rcu_tasks_kthre]
   13 root     [oom_reaper]
   14 root     [writeback]
   15 root     [kcompactd0]
   34 root     [kblockd]
   35 root     [watchdogd]
   36 root     [kworker/0:1-eve]
   37 root     [kworker/0:1H-mm]
   38 root     [rpciod]
   39 root     [kworker/u3:0]
   40 root     [xprtiod]
   41 root     [cfg80211]
   42 root     [kswapd0]
   43 root     [nfsiod]
   45 root     [spi0]
   46 root     [stmmac_wq]
   47 root     [kworker/u2:1-ev]
   80 root     [irq/47-cviusb-o]
   81 root     [irq/48-cd-gpio-]
   82 root     [sdhci]
   83 root     [irq/24-mmc0]
   84 root     [kworker/0:2-eve]
   85 root     [sdhci]
   86 root     [irq/25-mmc1]
   87 root     [ion_system_heap]
   89 root     [mmc_complete]
   90 root     [ipv6_addrconf]
   91 root     [krfcommd]
   96 root     [jbd2/mmcblk0p3-]
   97 root     [ext4-rsv-conver]
  113 root     /sbin/syslogd -n
  117 root     /sbin/klogd -n
  141 dbus     dbus-daemon --system
  150 root     [kworker/0:2H]
  159 dhcpcd   dhcpcd: [master] [ip4] [ip6]
  160 root     dhcpcd: [privileged actioneer]
  161 dhcpcd   dhcpcd: [network proxy]
  162 dhcpcd   dhcpcd: [control proxy]
  181 root     /usr/sbin/ntpd -g -p /var/run/ntpd.pid
  189 root     /usr/sbin/dropbear -R
  193 nobody   /usr/sbin/dnsmasq
  201 root     [cvitask_isp_pre]
  202 root     [cvitask_isp_bla]
  203 root     [cvitask_isp_err]
  205 root     [cvitask_vpss_0]
  206 root     [cvitask_vpss_1]
  208 root     [gdc_work]
  214 root     [cvitask_tpu_wor]
  221 root     {S99user} /bin/sh /etc/init.d/S99user start
  230 root     -sh
  295 root     [aicwf_bustx_thr]
  296 root     [aicwf_busrx_thr]
  297 root     [aicwf_pwrctl]
  298 root     [aicwf_bustx_thr]
  299 root     [aicwf_busrx_thr]
  300 root     [cmd_wq]
  301 root     [apmStaloss_wq]
  314 dhcpcd   dhcpcd: [BPF BOOTP] wlan0
  326 dhcpcd   dhcpcd: [BPF ARP] wlan0 169.254.77.8
 2369 root     /usr/sbin/dropbear -R
 2377 root     -sh
 2707 root     [kworker/u2:2-ev]
 2708 root     sleep 0.5
 2709 root     ps
[root@milkv-duo]~# ip addr
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: eth0: <NO-CARRIER,BROADCAST,MULTICAST,UP> mtu 1500 qdisc mq state DOWN qlen 1000
    link/ether 46:56:66:be:78:34 brd ff:ff:ff:ff:ff:ff
3: sit0@NONE: <NOARP> mtu 1480 qdisc noop state DOWN qlen 1000
    link/sit 0.0.0.0 brd 0.0.0.0
4: usb0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP qlen 1000
    link/ether 1a:1b:e5:0f:6b:b7 brd ff:ff:ff:ff:ff:ff
    inet 192.168.42.1/24 brd 192.168.42.255 scope global usb0
       valid_lft forever preferred_lft forever
    inet6 fe80::181b:e5ff:fe0f:6bb7/64 scope link 
       valid_lft forever preferred_lft forever
5: wlan0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc mq state UNKNOWN qlen 1000
    link/ether 88:00:33:77:b0:54 brd ff:ff:ff:ff:ff:ff
    inet 169.254.77.8/16 brd 169.254.255.255 scope global noprefixroute wlan0
       valid_lft forever preferred_lft forever
    inet6 fe80::7861:2d54:b0d8:f507/64 scope link 
       valid_lft forever preferred_lft forever
[root@milkv-duo]~# ip route
default dev wlan0 scope link  src 169.254.77.8  metric 1003005 
169.254.0.0/16 dev wlan0 scope link  src 169.254.77.8  metric 3005 
192.168.42.0/24 dev usb0 scope link  src 192.168.42.1 
[root@milkv-duo]~# cat /etc/resolv.conf 
# Generated by dhcpcd
# /etc/resolv.conf.head can replace this line
# /etc/resolv.conf.tail can replace this line
[root@milkv-duo]~# ls /sys/class/net
eth0  lo  sit0  usb0  wlan0

```

