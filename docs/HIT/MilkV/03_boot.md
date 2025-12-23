# 03 Boot Milk-V
## Boot from microSD Card
##### Insert microSD card into Milk-V board

##### Connect ttl to computer

##### screen ttl-usb serial port at 115200 baudrate
```bash
screen /dev/tty.wchusbserial5ACB0321921 115200
```
##### USB-C Power on Milk-V board

##### boot success
```bash
[root@milkv-duo]~# ls /
bin   dev  lib    libexec  lost+found  mnt  proc  run   sys  usr
boot  etc  lib64  linuxrc  media       opt  root  sbin  tmp  var
```
##### Turn off
```bash
sync
sync
poweroff # soft poweroff, watchdog will reboot automatically
halt  # Pull out line quickly before watchdog reboot!
```
Ctrl+A + K to exit screen
## Boot log
#### Update `screen` to latest version
```bash
robin@mbp ~  % screen -v          
Screen version 4.00.03 (FAU) 23-Oct-06

brew install screen

robin@mbp ~  % /opt/homebrew/bin/screen -v
Screen version 5.0.1 (build on 2025-05-15 15:05:07) 
```
#### Set latest `screen` to default
```bash
echo 'export PATH="/opt/homebrew/bin:/opt/homebrew/sbin:$PATH"' >> ~/.zshrc
source ~/.zshrc

robin@mbp ~  % which screen
/opt/homebrew/bin/screen
robin@mbp ~  % screen -v
Screen version 5.0.1 (build on 2025-05-15 15:05:07) 
```
#### Start logging
```bash
screen -L -Logfile bootlog.txt /dev/tty.wchusbserial5ACB0321921 115200

mv bootlog.txt bootlog.log
```
## First Boot log

#### Burn again
```bash
diskutil unmountDisk /dev/disk8
sudo dd if=milkv-duos-sd-v1.1.4.img of=/dev/rdisk8 bs=4m status=progress
diskutil eject /dev/disk8
``` 

## screen
```bash
screen -L -Logfile firstboot.txt /dev/tty.wchusbserial5ACB0321921 115200
```

### .screenrc
```bash
robin@mbp ~  % vim .screenrc  

defscrollback 50000
```
### copy mode
`Ctrl+A + [`

`Esc` to exit copy mode
