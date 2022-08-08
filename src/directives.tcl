############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
############################################################
set_directive_top -name dft "dft"
set_directive_interface -mode s_axilite -name dft "real_sample"
set_directive_pipeline -II 1 "dft/loop2"
set_directive_interface -mode m_axi -depth 1024 -offset slave -bundle BUS_1 "dft" real_sample
set_directive_interface -mode m_axi -depth 1024 -offset slave -bundle BUS_2 "dft" imag_sample
set_directive_interface -mode m_axi -depth 1024 -offset slave -bundle BUS_1 "dft" real_op
set_directive_interface -mode m_axi -depth 1024 -offset slave -bundle BUS_2 "dft" imag_op
set_directive_interface -mode s_axilite "dft"
