SSE (Streaming SIMD Extensions)
===============================


# 介绍

- ssse3 是 sse3 的扩充


# Headers

## SSE2


```c
extern "C"
{
    #include <emmintrin.h>
    #include <mmintrin.h>
}
```


## SSE3

```c
extern "C"
{
    #include <pmmintrin.h>
    #include <immintrin.h>   // (Meta-header)
}
```


## SSE4

```c
extern "C"
{
    #include <smmintrin.h>
}
```


# Links

- https://en.wikipedia.org/wiki/SSE4
