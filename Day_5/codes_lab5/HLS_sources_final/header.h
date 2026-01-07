#include<stdio.h>
#include <hls_stream.h>
#include "ap_axi_sdata.h"


//typedef struct {
//	float data;
//	ap_uint<1> last;
//} axis_data;

typedef hls::axis<float, 0, 0, 0> axis_data;


