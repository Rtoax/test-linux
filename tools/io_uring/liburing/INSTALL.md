
# CentOS

```
yum install liburing liburing-devel
```

# Ubuntu | CentOS

```bash
# https://blog.csdn.net/rong_toa/article/details/107999919
wget  https://github.com/axboe/liburing/archive/liburing-0.2.zip
unzip liburing-0.2.zip
cd liburing-liburing-0.2/
./configure --libdir=/usr/lib64 
make CFLAGS=-std=gnu99 && make install
```


