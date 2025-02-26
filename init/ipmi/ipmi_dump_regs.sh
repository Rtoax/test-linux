#!/bin/bash

# 此脚本可在任意能够访问BMC且机器安装ipmitool的机器上执行
# 使用时需要修改以下参数

bmc_user=''
bmc_passwd=''
bmc_ip=''


REG_TABLE=("0x2cb04fc8" "0x2cb04e00" "0x2cb04010" "0x2cb04050" \
           "0x2cb04090" "0x2cb040d0" "0x2cb04110" "0x2cb04150" "0x2cb04190" \
           "0x2cb041d0" "0x2cb04210" "0x2cb04250" "0x2cb04290" "0x2cb042d0" \
           "0x2cb04310" "0x2cb04350" "0x2cb04390" "0x2cb043d0" "0x2cb04410" \
           "0x2cb04450" "0x2cb04490" "0x2cb044d0" "0x2cb04510" "0x2cb04550" \
           "0x2cb04590" "0x2cb045d0" "0x2cb04610" "0x2cb04650" "0x2cb04690" \
           "0x2cb046d0" "0x2cb04710" "0x2cb04750" "0x2cb04790" "0x2cb047d0")

function dump_regs()
{
    socket_id=$1

    if [ $socket_id == "0" ]; then
        slave="0x18"
    else
        slave="0x19"
    fi

    for reg in "${REG_TABLE[@]}" ; do
        let reg_0=$(($reg & 0xFF))
        let reg_1=$(($reg >> 8 & 0xFF))
        let reg_2=$(($reg >> 16 & 0xFF))
        let reg_3=$(($reg >> 24 & 0xFF))

        #printf '0x%02x%02x%02x%02x\n' $reg_3 $reg_2 $reg_1 $reg_0
        #echo "timeout 10 ipmitool -I lanplus -H ${bmc_ip} -U ${bmc_user} -P ${bmc_passwd} raw 0x32 0x23 0x07 0x18 0x04 0x00 $reg_3 $reg_2 $reg_1 $reg_0 0x0"
        reg_val=`timeout 10 ipmitool -I lanplus -H ${bmc_ip} -U ${bmc_user} -P ${bmc_passwd} raw 0x32 0x23 0x07 $slave 0x04 0x00 $reg_3 $reg_2 $reg_1 $reg_0 0x0`
        echo "Socket[$socket_id] $reg val: $reg_val"
    done
}


for ((i=0; i<3; i++)); do
    echo "`date` ++ Dump Socket 0 -->"
    dump_regs 0

    echo "`date` ++ Dump Socket 1 -->"
    dump_regs 1

    sleep 1
    echo ""
done

