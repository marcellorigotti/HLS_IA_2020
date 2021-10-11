############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
############################################################
open_project Fixed_Point
set_top lenet_cnn
add_files utils.c -cflags "-I/usr/include/hdf5/serial/. -O3"
add_files pool.c
add_files lenet_weights.hdf5
add_files lenet_cnn_float.c
add_files fc.c
add_files conv.c
add_files -tb mnist -cflags "-Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas"
add_files -tb lenet_cnn_float.c -cflags "-Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas"
open_solution "solution1"
set_part {xc7z020clg484-1}
create_clock -period 10 -name default
#source "./Fixed_Point/solution1/directives.tcl"
csim_design -ldflags {-lhdf5_serial -lm} -clean
csynth_design
cosim_design -ldflags {-lhdf5_serial -lm} -rtl vhdl
export_design -rtl vhdl -format ip_catalog
