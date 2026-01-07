// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2022.1 (win64) Build 3526262 Mon Apr 18 15:48:16 MDT 2022
// Date        : Tue Dec 23 15:39:29 2025
// Host        : DESKTOP-OO0S615 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               d:/IEP/Day_3_IEP/Day_3/Day_3.gen/sources_1/bd/design_1/ip/design_1_cm_top_0_0/design_1_cm_top_0_0_stub.v
// Design      : design_1_cm_top_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z020clg400-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "cm_top,Vivado 2022.1" *)
module design_1_cm_top_0_0(ap_clk, ap_rst_n, in_stream_TVALID, 
  in_stream_TREADY, in_stream_TDATA, in_stream_TLAST, in_stream_TKEEP, in_stream_TSTRB, 
  out_stream_TVALID, out_stream_TREADY, out_stream_TDATA, out_stream_TLAST, 
  out_stream_TKEEP, out_stream_TSTRB)
/* synthesis syn_black_box black_box_pad_pin="ap_clk,ap_rst_n,in_stream_TVALID,in_stream_TREADY,in_stream_TDATA[63:0],in_stream_TLAST[0:0],in_stream_TKEEP[7:0],in_stream_TSTRB[7:0],out_stream_TVALID,out_stream_TREADY,out_stream_TDATA[63:0],out_stream_TLAST[0:0],out_stream_TKEEP[7:0],out_stream_TSTRB[7:0]" */;
  input ap_clk;
  input ap_rst_n;
  input in_stream_TVALID;
  output in_stream_TREADY;
  input [63:0]in_stream_TDATA;
  input [0:0]in_stream_TLAST;
  input [7:0]in_stream_TKEEP;
  input [7:0]in_stream_TSTRB;
  output out_stream_TVALID;
  input out_stream_TREADY;
  output [63:0]out_stream_TDATA;
  output [0:0]out_stream_TLAST;
  output [7:0]out_stream_TKEEP;
  output [7:0]out_stream_TSTRB;
endmodule
