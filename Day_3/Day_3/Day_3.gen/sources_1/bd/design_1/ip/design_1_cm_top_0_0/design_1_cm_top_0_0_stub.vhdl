-- Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2022.1 (win64) Build 3526262 Mon Apr 18 15:48:16 MDT 2022
-- Date        : Tue Dec 23 15:39:29 2025
-- Host        : DESKTOP-OO0S615 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               d:/IEP/Day_3_IEP/Day_3/Day_3.gen/sources_1/bd/design_1/ip/design_1_cm_top_0_0/design_1_cm_top_0_0_stub.vhdl
-- Design      : design_1_cm_top_0_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7z020clg400-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity design_1_cm_top_0_0 is
  Port ( 
    ap_clk : in STD_LOGIC;
    ap_rst_n : in STD_LOGIC;
    in_stream_TVALID : in STD_LOGIC;
    in_stream_TREADY : out STD_LOGIC;
    in_stream_TDATA : in STD_LOGIC_VECTOR ( 63 downto 0 );
    in_stream_TLAST : in STD_LOGIC_VECTOR ( 0 to 0 );
    in_stream_TKEEP : in STD_LOGIC_VECTOR ( 7 downto 0 );
    in_stream_TSTRB : in STD_LOGIC_VECTOR ( 7 downto 0 );
    out_stream_TVALID : out STD_LOGIC;
    out_stream_TREADY : in STD_LOGIC;
    out_stream_TDATA : out STD_LOGIC_VECTOR ( 63 downto 0 );
    out_stream_TLAST : out STD_LOGIC_VECTOR ( 0 to 0 );
    out_stream_TKEEP : out STD_LOGIC_VECTOR ( 7 downto 0 );
    out_stream_TSTRB : out STD_LOGIC_VECTOR ( 7 downto 0 )
  );

end design_1_cm_top_0_0;

architecture stub of design_1_cm_top_0_0 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "ap_clk,ap_rst_n,in_stream_TVALID,in_stream_TREADY,in_stream_TDATA[63:0],in_stream_TLAST[0:0],in_stream_TKEEP[7:0],in_stream_TSTRB[7:0],out_stream_TVALID,out_stream_TREADY,out_stream_TDATA[63:0],out_stream_TLAST[0:0],out_stream_TKEEP[7:0],out_stream_TSTRB[7:0]";
attribute X_CORE_INFO : string;
attribute X_CORE_INFO of stub : architecture is "cm_top,Vivado 2022.1";
begin
end;
