#include "matmul.h"

#ifdef matrixmulFLP
void matrixmul_FLP(hls::stream<axis_data> &in_AB, hls::stream<axis_data> &out_C);
#endif

#ifdef matrixmulFXP
void matrixmul_FXP(hls::stream<axis_data> &in_AB, hls::stream<axis_data> &out_C);
#endif

void matrixmul_bm(Mat_Dtype input_A[MATSIZE][MATSIZE],Mat_Dtype input_B[MATSIZE][MATSIZE],Mat_Dtype output_C[MATSIZE][MATSIZE]);

int main()
{
	Mat_Dtype input_A[MATSIZE][MATSIZE];
	Mat_Dtype input_B[MATSIZE][MATSIZE];
	Mat_Dtype output_C_bm[MATSIZE][MATSIZE];
	Mat_Dtype output_C_hw[MATSIZE][MATSIZE];
	Mat_Dtype input_AB[MATSIZE*MATSIZE*2];
	Mat_Dtype output_C[MATSIZE*MATSIZE];
	hls::stream<axis_data> in_AB,out_C;

	int row, col,index;
	axis_data local_read, local_write;

	for(row=0;row<MATSIZE;row++)
	{
		for(col=0;col<MATSIZE;col++)
		{
			input_A[row][col] = ((float)rand() / (RAND_MAX / 5));
			input_B[row][col] = ((float)rand() / (RAND_MAX / 5));
		}
	}

	matrixmul_bm(input_A,input_B,output_C_bm);

	WA_L1:for(row =0;row<MATSIZE;row++)
	{
		WA_L2:for (col=0;col<MATSIZE;col++)
		{
			local_write.data = input_A[row][col];
			local_write.last =0;
			in_AB.write(local_write);
		}
	}
	WB_L1:for(row =0;row<MATSIZE;row++)
	{
		WB_L2:for (col=0;col<MATSIZE;col++)
		{
			local_write.data = input_B[row][col];
			if((row == MATSIZE-1)&& (col==MATSIZE-1))
				local_write.last = 1;
			else
				local_write.last =0;
			in_AB.write(local_write);
		}
	}


#ifdef matrixmulFLP
	matrixmul_FLP(in_AB,out_C);
#endif

#ifdef matrixmulFXP
	matrixmul_FXP(in_AB,out_C);
#endif

	RC_L1:for(row =0;row<MATSIZE;row++)
	{
		RC_L2:for (col=0;col<MATSIZE;col++)
		{
			local_read = out_C.read();
			output_C_hw[row][col]=local_read.data;
		}
	}


	Mat_Dtype diff;
	CMP_L1:for(row =0;row<MATSIZE;row++)
	{
		CMP_L2:for (col=0;col<MATSIZE;col++)
		{
			diff = fabs(output_C_hw[row][col] - output_C_bm[row][col]);
			if(diff > 0.01)
			{
				printf("ERROR");
				return 1;
			}
		}
	}
	printf("NO ERROR");
	return 0;
}




void matrixmul_bm(Mat_Dtype input_A[MATSIZE][MATSIZE],Mat_Dtype input_B[MATSIZE][MATSIZE],Mat_Dtype output_C[MATSIZE][MATSIZE])
{
	int row, col,index;
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
}
