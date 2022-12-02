# cpu-utility

## Linux 计时函数gettimeofday()
Linux下可以使用gettimeofday()来查看当前时间，这个函数会计算从1970年1月1号00:00（UTC）到当前时间跨度。
gettimeofday()函数原型如下：
```
#include <sys/time.h>

// 调用成功返回0，失败返回-1
int gettimeofday(struct timeval *tv, struct timezone *tz);
```
该函数所算出的时间跨度会存放在第一个参数tv里，这个参数的类型定义如下：
```
struct timeval {
  time_t tv_sec;
  suseconds_t tv_usec;
  ...
};
```
time_t和suseconds_t实际类型是long int，日常使用时，只需传第一个参数，第二个参数传NULL（linux内核不使用这个参数）。
