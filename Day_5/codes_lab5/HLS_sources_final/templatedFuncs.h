#ifndef _TEMPLATED_FUNC_
#define _TEMPLATED_FUNC_



// Function to load filter corresponding to a particular output channel in a IN_CHx3x3 Kernel
// The kernel is then completely partitioned (in conv2D block) which allows to compute multiplications in parallel

template<
	int IN_CH,
	int K
> void load_filters(
    const float conv_weight[IN_CH * K * K],
    float kernel[IN_CH][K][K]
)
{
//#pragma HLS INLINE off
Fil_load_ch:
    for (int kch = 0; kch < IN_CH; kch++)
    {

    Fil_load_r:
        for (int kh = 0; kh < K; kh++)
        {
        Fil_load_c:
            for (int kw = 0; kw < K; kw++)
            {
#pragma HLS PIPELINE
                int kidx = (kch * K * K) + (kh * K) + kw;
                kernel[kch][kh][kw] = conv_weight[kidx];
            }
        }
    }
}



// This function loads a 2D ifmap in a window of size 3x3
// This allows the window to be completely partitioned
// This window will then be convolved with a 3x3 kernel parallely
template<
	int IN_CH,
	int IN_DIM
>
void load_input_window(float window[3][3],float ifmap[IN_CH][IN_DIM][IN_DIM], int iR, int iC, int kch){
//#pragma HLS INLINE off

	loadWin1:
		for (int wi = 0; wi < 3; wi++) {
			for (int wj = 0; wj < 3; wj++) {
#pragma HLS PIPELINE
				window[wi][wj] = ifmap[kch][iR+wi][iC+wj];
			}
		}
}



// ReLU implementation
float relu_func(float input){
	return (input<0?0:input);
}



// This function performs 2D convolution of a 3x3 kernel and 3x3 ifmap window.
// The convolution is performed in 2 steps.
//     1. Partial products are generated in parallel by element-wise multiplication of krnel and ifmap window.
//     2. The partial products are added using a multi-stage adder tree.
// The convolution is computed per input channel.
// For the final input channel, ReLU is applied.

template<
	int IN_CH
>
float conv2D(int kch,int ow, int oh,float kernel[IN_CH][3][3],float conv_bias,float window[3][3],float prev_sum){
//#pragma HLS INLINE off


	float sum;
	float pmul[3][3];
//	float prev_sum;

//	prev_sum=(kch==0)? conv_bias:ofmap[oh][ow];
//	if(kch==0) prev_sum=conv_bias;

#pragma HLS ARRAY_PARTITION variable=pmul complete dim=0

	#pragma HLS PIPELINE
		for (int kh = 0; kh < 3; kh++)
		{
			for (int kw = 0; kw < 3; kw++)
			{
				pmul[kh][kw]= window[kh][kw] *
					   kernel[kch][kh][kw];
			}
		}

	float s0 = pmul[0][0] + pmul[0][1];
	float s1 = pmul[0][2] + pmul[1][0];
	float s2 = pmul[1][1] + pmul[1][2];
	float s3 = pmul[2][0] + pmul[2][1];

	float s4 = prev_sum + pmul[2][2];

	float s5 = s0 + s1;
	float s6 = s2 + s3;

	float s7 = s5 + s6;
	sum = s7 + s4;

	return sum;

//	if(kch==IN_CH-1){
//		ofmap[n_f][oh][ow] = relu_func(sum);
////		prev_sum = relu_func(sum);
//	}
//	else{
//		ofmap[n_f][oh][ow] = sum;
////		prev_sum =(sum);
//	}

}



template<
	int IN_CH,
	int IN_DIM,
	int OUT_CH,
	int OUT_DIM
>
void Conv_func(float ifmap[IN_CH][IN_DIM][IN_DIM],float ofmap[OUT_CH][OUT_DIM][OUT_DIM], const float conv_weight[OUT_CH][IN_CH*3*3],const float conv_bias[OUT_CH]){

	float kernel[IN_CH][3][3];
#pragma HLS ARRAY_PARTITION variable=kernel complete dim=0

	float window[3][3];
#pragma HLS ARRAY_PARTITION variable=window complete dim=0

	float prev_sum=0.0f;
	float sum;

	C1_fil_load:for(int n_f=0;n_f<OUT_CH;n_f++){
		load_filters<IN_CH, 3>(conv_weight[n_f], kernel);

    	inCh:
		for (int kch = 0; kch < IN_CH; kch++)
		{
			VS:for (int oh = 0; oh < OUT_DIM; oh++)
			{
				HS:for (int ow = 0; ow < OUT_DIM; ow++)
				{
		        	load_input_window<IN_CH,IN_DIM>(window,ifmap,oh,ow,kch);

					prev_sum=(kch==0)? conv_bias[n_f]:ofmap[n_f][oh][ow];
					sum=conv2D<IN_CH>(kch,ow,oh,kernel,conv_bias[n_f],window,prev_sum);

					if(kch==IN_CH-1){
						ofmap[n_f][oh][ow] = relu_func(sum);
					}
					else{
						ofmap[n_f][oh][ow] = sum;
					}
				}

	        }
	    }
	}
}

// Max Pooling Operation
template<
	int IN_CH,
	int IN_DIM,
	int OUT_DIM
>
void maxPool(float ifmap[IN_CH][IN_DIM][IN_DIM],float ofmap[IN_CH][OUT_DIM][OUT_DIM]){
	float max_0[OUT_DIM];
	float max_1[OUT_DIM];
	MP_ch:for(int och=0;och<IN_CH;och++){
		MP_r:for(int oh=0;oh<IN_DIM;oh+=2){
			MP_c:for(int ow=0;ow<IN_DIM;ow+=2){
#pragma HLS PIPELINE
				max_0[ow/2] = (ifmap[och][oh][ow]>ifmap[och][oh][ow+1])?ifmap[och][oh][ow]:ifmap[och][oh][ow+1];
				max_1[ow/2] = (ifmap[och][oh+1][ow]>ifmap[och][oh+1][ow+1])?ifmap[och][oh+1][ow]:ifmap[och][oh+1][ow+1];

				ofmap[och][oh/2][ow/2] = (max_0[ow/2]>max_1[ow/2])?max_0[ow/2]:max_1[ow/2];
			}
		}
	}

}


//float relu_func_2(float input){
//	return (input<0?0:input);
//}


template<
	int inFeatures,
	int outFeatures,
	bool reluEn
>
void FC_layer(float input[inFeatures],float output[outFeatures],const float fc_weight[outFeatures][inFeatures],const float fc_bias[outFeatures]){

	float pmul[outFeatures];
#pragma HLS ARRAY_PARTITION variable=pmul complete
	float pmul_prev[outFeatures];
#pragma HLS ARRAY_PARTITION variable=pmul_prev complete

	out_loop:for(int turn=0;turn<2;turn++){
#pragma HLS PIPELINE off

		for(int i_index=0;i_index<inFeatures;i_index++){
			float ip = input[i_index];
			init:for(int o_index=0;o_index<outFeatures/2;o_index++){
		#pragma HLS UNROLL
				if(i_index==0){
					pmul_prev[o_index] = fc_bias[turn*(outFeatures/2)+o_index];
				}
				else{
					pmul_prev[o_index] = pmul[o_index];
				}
			}

			n_mul:for(int o_index=0;o_index<outFeatures/2;o_index++){
	#pragma HLS UNROLL
				pmul[o_index] = pmul_prev[o_index] + ip*fc_weight[turn*(outFeatures/2)+o_index][i_index];
			}

			out_write:for(int o_index=0;o_index<outFeatures/2;o_index++){
		#pragma HLS UNROLL
		//		output[o_index] = (pmul[o_index]) ;
				if (reluEn){
					output[turn*(outFeatures/2)+o_index] = relu_func(pmul[o_index]) ;
				}
				else{
					output[turn*(outFeatures/2)+o_index] = (pmul[o_index]) ;
				}

			}
		}
	}
}





#endif
