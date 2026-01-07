#include "matmul.h"

#ifdef matrixmulFLP
void matrixmul_FLP(hls::stream<axis_data> &in_AB, hls::stream<axis_data> &out_C)
{
	#pragma HLS INTERFACE ap_ctrl_none port=return
	#pragma HLS INTERFACE axis register both port=in_AB
	#pragma HLS INTERFACE axis register both port=out_C

	Mat_Dtype input_A[MATSIZE][MATSIZE];
	Mat_Dtype input_B[MATSIZE][MATSIZE];
	Mat_Dtype output_C[MATSIZE][MATSIZE];
	int row, col,index;
	axis_data local_read, local_write;

	RA_L1:for(row =0;row<MATSIZE;row++)
	{
		RA_L2:for (col=0;col<MATSIZE;col++)
		{
			local_read = in_AB.read();
			input_A[row][col]=local_read.data;
		}
	}

	RB_L1:for(row =0;row<MATSIZE;row++)
	{
		RB_L2:for (col=0;col<MATSIZE;col++)
		{
			local_read = in_AB.read();
			input_B[row][col]=local_read.data;
		}
	}
	Mat_Dtype temp_res;
	MM_L1:for(row =0;row<MATSIZE;row++)
	{
		MM_L2:for (col=0;col<MATSIZE;col++)
		{
			temp_res = 0;
			MM_L3:for (index=0;index<MATSIZE;index++)
			{
				temp_res = temp_res + input_A[row][index]*input_B[index][col];
			}
			output_C[row][col] = temp_res;
		}
	}

	WC_L1:for(row =0;row<MATSIZE;row++)
	{
		WC_L2:for (col=0;col<MATSIZE;col++)
		{
			local_write.data = output_C[row][col];
			local_write.keep = -1;
			if((row == MATSIZE-1)&& (col==MATSIZE-1))
				local_write.last = 1;
			else
				local_write.last =0;
			out_C.write(local_write);
		}
	}

}
#endif


#ifdef matrixmulFXP
void matrixmul_FXP(hls::stream<axis_data> &in_AB, hls::stream<axis_data> &out_C)
{
	#pragma HLS INTERFACE ap_ctrl_none port=return
	#pragma HLS INTERFACE axis register both port=in_AB
	#pragma HLS INTERFACE axis register both port=out_C

	Mat_DtypeOp  input_A[MATSIZE][MATSIZE];
	Mat_DtypeOp  input_B[MATSIZE][MATSIZE];
	Mat_DtypeOp  output_C[MATSIZE][MATSIZE];
	int row, col,index;
	axis_data local_read, local_write;

	RA_L1:for(row =0;row<MATSIZE;row++)
	{
		RA_L2:for (col=0;col<MATSIZE;col++)
		{
			local_read = in_AB.read();
			input_A[row][col]=(Mat_DtypeOp) local_read.data;
		}
	}

	RB_L1:for(row =0;row<MATSIZE;row++)
	{
		RB_L2:for (col=0;col<MATSIZE;col++)
		{
			local_read = in_AB.read();
			input_B[row][col]=(Mat_DtypeOp)local_read.data;
		}
	}
	Mat_DtypeOp  temp_res;
	MM_L1:for(row =0;row<MATSIZE;row++)
	{
		MM_L2:for (col=0;col<MATSIZE;col++)
		{
			temp_res = 0;
			MM_L3:for (index=0;index<MATSIZE;index++)
			{
				temp_res = temp_res + input_A[row][index]*input_B[index][col];
			}
			output_C[row][col] = temp_res;
		}
	}

	WC_L1:for(row =0;row<MATSIZE;row++)
	{
		WC_L2:for (col=0;col<MATSIZE;col++)
		{
			local_write.data = (Mat_Dtype)output_C[row][col];
			local_write.keep = -1;
			if((row == MATSIZE-1)&& (col==MATSIZE-1))
				local_write.last = 1;
			else
				local_write.last =0;
			out_C.write(local_write);
		}
	}

}
#endif
