echo "Booting xv6"

fatload mmc 0:1 0x80200000 kernel
go 0x80200000