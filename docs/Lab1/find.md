```
mkdir dir

fs's disk device:1
size:32
file type:1 T_DIR
numbers of links to file:1
dirent inum:32 name:.
dirent inum:1 name:..
inode 32 (T_DIR)
  └── data block:
        [ {inum=32, name="."} ]
        [ {inum=1,  name=".."} ]
```
Optional challenge exercises:
Support regular expressions in name matching for find. grep.c has some primitive support for regular expressions. (easy)
```
$ find . .*t.* -exec echo hi
hi ./findtest.sh
hi ./sixfive.txt
hi ./cat
hi ./forktest
hi ./init
hi ./stressfs
hi ./usertests
hi ./logstress
hi ./uptime
```