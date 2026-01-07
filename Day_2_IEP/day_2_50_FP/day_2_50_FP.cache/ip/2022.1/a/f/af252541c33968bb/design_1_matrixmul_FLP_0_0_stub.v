// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2022.1 (win64) Build 3526262 Mon Apr 18 15:48:16 MDT 2022
// Date        : Mon Dec 22 17:50:54 2025
// Host        : DESKTOP-OO0S615 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
//               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ design_1_matrixmul_FLP_0_0_stub.v
// Design      : design_1_matrixmul_FLP_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z020clg400-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "matrixmul_FLP,Vivado 2022.1" *)
module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix(ap_clk, ap_rst_n, in_AB_TVALID, in_AB_TREADY, 
  in_AB_TDATA, in_AB_TLAST, in_AB_TKEEP, in_AB_TSTRB, out_C_TVALID, out_C_TREADY, out_C_TDATA, 
  out_C_TLAST, out_C_TKEEP, out_C_TSTRB)
/* synthesis syn_black_box black_box_pad_pin="ap_clk,ap_rst_n,in_AB_TVALID,in_AB_TREADY,in_AB_TDATA[31:0],in_AB_TLAST[0:0],in_AB_TKEEP[3:0],in_AB_TSTRB[3:0],out_C_TVALID,out_C_TREADY,out_C_TDATA[31:0],out_C_TLAST[0:0],out_C_TKEEP[3:0],out_C_TSTRB[3:0]" */;
  input ap_clk;
  input ap_rst_n;
  input in_AB_TVALID;
  output in_AB_TREADY;
  input [31:0]in_AB_TDATA;
  input [0:0]in_AB_TLAST;
  input [3:0]in_AB_TKEEP;
  input [3:0]in_AB_TSTRB;
  output out_C_TVALID;
  input out_C_TREADY;
  output [31:0]out_C_TDATA;
  output [0:0]out_C_TLAST;
  output [3:0]out_C_TKEEP;
  output [3:0]out_C_TSTRB;
endmodule
