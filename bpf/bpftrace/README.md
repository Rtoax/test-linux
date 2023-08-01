bpftrace
============


# sys fs

* `/sys/kernel/btf/vmlinux`
* `/sys/kernel/debug/tracing/available_filter_functions`
* `/sys/kernel/debug/tracing/available_events`
* `/sys/devices/system/cpu/possible`


# make-and-install

```bash
#!/bin/bash
mkdir -p build
cd build
cmake \
	-DCMAKE_INSTALL_PREFIX=/usr/ \
	-DCMAKE_BUILD_TYPE=Debug \
	-DBUILD_TESTING=OFF \
	-DVENDOR_GTEST=OFF \
	..
make -j$(nproc)
sudo make install
```

