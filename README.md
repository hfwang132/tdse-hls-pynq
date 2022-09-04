# 2022 Xilinx Summer School Project

本仓库为 2022 Xilinx Summer School 的作业，目前实现了 DFT 和 TDSE。

## Repository Tree

```
.
├── README.md
├── dft
│   ├── jupyter
│   ├── overlay
│   ├── report
│   └── src
└── tdse
    ├── jupyter
    ├── overlay
    ├── report
    └── src

```

## DFT（离散傅里叶变换）

- 没有使用快速傅里叶变换算法
- 比软件实现快10倍

## TDSE（含时薛定谔方程）

- 采用 Trotter-Suzuki 方法
- 100x100 格点上
- 计算波包穿过小孔的衍射
- 比软件实现快 200+ 倍
- reference: De Raedt, Hans. "Computer simulation of quantum phenomena in nanoscale devices." Annual Reviews of Computational Physics IV (1996): 107-146.

## 注意

- HLS 优化的编译指令部分在`directives.tcl`当中，而非在源代码中。这样做可以方便在 IDE 中调整和对比优化策略。
- 本仓库的项目都基于 xc7z010clg400-1，而非 pynq-z2 所用的 xc7z020clg484-1
