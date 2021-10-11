############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
############################################################
open_project Float
set_top lenet_cnn
add_files conv.c
add_files fc.c
add_files lenet_cnn_float.c
add_files lenet_weights.hdf5
add_files pool.c
add_files utils.c -cflags "-l/usr/include/hdf5/serial/.-O3"
add_files -tb lenet_cnn_float.c -cflags "-l/usr/include/hdf5/serial/.-O3"
add_files -tb mnist
open_solution "solution1"
set_part {xa7a12tcsg325-1q}
create_clock -period 10 -name default
#source "./Float/solution1/directives.tcl"
csim_design -ldflags {-lhdf5_serial -lm} -clean
csynth_design
cosim_design -ldflags {-lhdf5_serial -lm}
export_design -format ip_catalog
