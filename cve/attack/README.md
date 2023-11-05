Attack
======

# 攻击

## 时间违规(temporal violation)

典型代表为Use-After-Free（UAF）漏洞，即在释放内存后，再次对该内存进行访问。


## 空间违规(spatial violation)

典型代表为栈溢出（stack overflow）漏洞，即在栈上分配的内存空间不足以存放当前的数据。


## 攻击类型

> 下面三个都是空间违规的攻击手段

- ROP (Return-oriented programming)
- JOP (Jump-Oriented Programming)
- COP (Call-Oriented Programming)


# 应对

- Intel CET (Control-Flow Enforcement Technology)
- ARM PAC (Pointer Authentication)


# Links

- https://zhuanlan.zhihu.com/p/39695776
- https://iamywang.github.io/2023/03/23/rop-1/

