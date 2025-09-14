SR-IOV
======

# 网卡

- 创建虚拟网卡

```
echo '4' > /sys/class/net/[Interface]/device/sriov_numvfs
```

