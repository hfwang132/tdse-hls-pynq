# 注意

- c testbench 只输出结果，验证结果是否正确用的是 matlab （tdse_tb.m，TDSE_testforhls.m）。方法：在 matlab ide 中先运行 TDSE_testforhls.m，再运行 tdse_tb.m，对比结果
- 为了缩短开发流程，只进行了 c sim（结合 matlab），未进行 co sim
- 可以将 psi_re 和 psi_im bundle 到不同的总线上，内部循环的 II 由 4 降低到 2，latency 下降一半，但由于 z-7010 资源不够，无法布线，无法采用。