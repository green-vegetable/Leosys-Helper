# Leosys-Helper

[北师大图书馆预约](http://seat.lib.bnu.edu.cn)助手，自用

#### 环境

1. win10_64 & [codeblocks-20.03mingw-setup](http://www.codeblocks.org/downloads/26)

2. *\CodeBlocks\MinGW 添加到path

#### 编译

``` mingw32-make```

#### 运行

main.exe

#### 日常编辑

main.cpp中：

1. 日期：第二天的年月日。

2. 座位号：需要找到真正的座位号。

   浏览器打开[北师大图书馆空间预约系统](http://seat.lib.bnu.edu.cn)、找到想要的座位、右键检查元素、"seat_xxxx"（见下图"seat_48918"）中的xxxx就是真正的座位号。

   <img src="https://raw.githubusercontent.com/green-vegetable/Leosys-Helper/master/src/seat.PNG?token=AIOBXHURGNOXBRIFUP4FLV27XRXF4" style="zoom: 50%;" />

3. JSESSIONID:  本次网页登陆的标志。

   浏览器打开[北师大图书馆空间预约系统](http://seat.lib.bnu.edu.cn)、F12调出页面工具、网络（Network）、刷新页面、找到GET seat.lib.bnu.edu.cn项、找到GET中的Cookies、Cookies里面的JSESSIONID（见下图"678CF2E96C113A4C4F7370F758F369C3"）。

   <img src="https://raw.githubusercontent.com/green-vegetable/Leosys-Helper/master/src/jsessionid.PNG?token=AIOBXHTN5OU53V34HV6THHC7XRXJ2" style="zoom:67%;" />

   



