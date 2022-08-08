# 2022 Xilinx Summer School Project

## DFT（离散傅里叶变换）

### Repository Tree

```
.
├── dft.cpp              //源码框架
├── dft.h                //头文件
├── dft_test.cpp         //测试源码
├── coefficients1024.h   //系数文件
├── out.gold.dat         //标准输出
├── tcl_script.tcl       //tcl文件
├── directives.tcl       //hls编译指令 ***
└── README.md            //说明文件
```
### 实现

代码已经实现在 dft.cpp 中，其中包含了 baseline 代码和优化后代码。

注意：我添加了 directives.tcl，HLS 优化的编译指令都在这个文件当中，而不是在源代码中。这样做可以方便在 IDE 中调整和对比优化策略。

注意：没有使用快速傅里叶变换算法。
