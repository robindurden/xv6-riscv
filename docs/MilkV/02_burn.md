# 02 Burn microSD card
## microSD Card Setup
### Check microSD card info
sdCard space must be larger than image size (1GB+)
```bash
#### diskutil
##### list                 (List the partitions of a disk)
```bash
robin@mbp ~  % diskutil list
/dev/disk8 (internal, physical):
   #:   |         TYPE NAME                                 SIZE       IDENTIFIER
   0:   └──   FDisk_partition_scheme                        *129.0 MB    disk8
   1:                 └── DOS_FAT_16 NO NAME                 129.0 MB    disk8s1
```
macOS default formats microSD card as FAT16 with a single partition
##### info[rmation]        (Get information on a specific disk or partition)
```bash
diskutil info disk8
```

##### optional zeroDisk             (Erase a disk, writing zeros to the media)
```bash
robin@mbp ~  % diskutil zeroDisk disk8
Started erase on disk8
Finished erase on disk8

robin@mbp ~  % diskutil list
/dev/disk8 (internal, physical):
   #:                       TYPE NAME                    SIZE       IDENTIFIER
   0:                                                   *129.0 MB   disk8
```
##### ls
```bash
robin@mbp ~  % ls -la /dev/disk8
brw-r-----  1 root  operator  0x1000014 Dec  9 18:06 /dev/disk8
```
- b → block device
- owner = root；group = operator
- 0x1000014 →  device number

## Image
https://milkv.io/docs/duo/getting-started/download
```bash
robin@mbp Downloads  % ls -la milkv-duos-sd-v1.1.4.img 
-rw-r--r--@ 1 robin  staff  941621760 Nov 22  2024 milkv-duos-sd-v1.1.4.img
```

```bash
robin@mbp Downloads  % hdiutil attach -nomount milkv-duos-sd-v1.1.4.img
/dev/disk4          	FDisk_partition_scheme         	
/dev/disk4s1        	Windows_FAT_32                 	/Volumes/boot
/dev/disk4s3        	Linux      
```

lz4 decompress
```
lz4 -d duos_sd.img.lz4
```
## Burn
##### unmountDisk
```shell
diskutil unmountDisk /dev/disk8

Unmount of all volumes on disk8 was successful
```
##### raw device
- 	/dev/disk8 = buffered device（slow）
- 	/dev/rdisk8 = raw device（fast 5～10x）
```bash
robin@mbp Downloads  % ls -la /dev/rdisk8
crw-r-----  1 root  operator  0x1000014 Dec  9 21:43 /dev/rdisk8
```
- c → character device
- 1 → link count
##### dd
dd = disk destroyer
```bash
dd if=milkv-duos-sd-v1.1.4.img of=/dev/rdisk8 bs=4m status=progress
```
- if = input file
- of = output file
- bs = block size
- status=progress → show progress

🔥Burn🔥
```bash
robin@mbp Downloads  % sudo dd if=milkv-duos-sd-v1.1.4.img of=/dev/rdisk8 bs=4m status=progress
Password:
dd: /dev/rdisk8: short write on character device25.263s, 4981 kB/s
dd: /dev/rdisk8: Input/output error

31+0 records in
30+1 records out
128974848 bytes transferred in 25.809307 secs (4997222 bytes/sec)
```
ensure all data is written to the disk
```bash
sync
```
#### Check
```bash
robin@mbp images  % diskutil list disk8
/dev/disk8 (internal, physical):
   #:                       TYPE NAME                    SIZE       IDENTIFIER
   0:     FDisk_partition_scheme                        *15.7 GB    disk8
   1:             Windows_FAT_32 boot                    134.2 MB   disk8s1
   2:                      Linux                         805.3 MB   disk8s3
                    (free space)                         14.8 GB    -
```
- patition 1: FAT32 boot
- partition 2: Linux ext4 rootfs


#### ejectDisk
```bash
diskutil eject /dev/disk8

Disk /dev/disk8 ejected
```