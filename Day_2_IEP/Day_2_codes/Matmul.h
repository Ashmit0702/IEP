#include <stdio.h>
#include <stdlib.h>
#include <hls_stream.h>
#include "ap_axi_sdata.h"
#define MATSIZE 20
#include <ap_int.h>
typedef float Mat_Dtype;
#include <string.h>
#define matrixmulFXP
#include <ap_fixed.h>

typedef hls::axis<Mat_Dtype, 0, 0, 0> axis_data;
typedef ap_fixed<24,11>  Mat_DtypeOp;


#ifdef matrixmulFLP
void matrixmul_FLP(hls::stream<axis_data> &in_AB, hls::stream<axis_data> &out_C);
#endif

#ifdef matrixmulFXP
void matrixmul_FXP(hls::stream<axis_data> &in_AB, hls::stream<axis_data> &out_C);
#endif

