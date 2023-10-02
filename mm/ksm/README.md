KSM - Kernel SamePage Merging
=============================

# KSM sysfs

* Enable ksm

```
echo 1 > /sys/kernel/mm/ksm/run
```
* Check ksm info

```
cat /sys/kernel/mm/ksm/pages_sharing
cat /sys/kernel/mm/ksm/pages_shared
cat /sys/kernel/mm/ksm/pages_unshared
```

# ksmtuned

```
# cat /etc/ksmtuned.conf
```

