#include "header.h"
#include"cnn_weights.h"
#include "templatedFuncs.h"

void read_input(hls::stream<axis_data> &inputPort, float mem1[1][28][28]){
	axis_data localRead;
	readLoop_row:for(int i_r=0;i_r<28;i_r++){
		readLoop_col:for(int i_c=0;i_c<28;i_c++){
#pragma HLS PIPELINE
			localRead = inputPort.read();
			mem1[0][i_r][i_c] = localRead.data;
		}
	}
}

void write_output(hls::stream<axis_data> &outputPort, float outputData[10]){
	axis_data localWrite;

	write_col:for(int o_c=0;o_c<10;o_c++){
	#pragma HLS PIPELINE
		localWrite.data = outputData[o_c];
		localWrite.last = (o_c==10-1)? 1:0;
		localWrite.keep = -1;
		outputPort.write(localWrite);
	}
}

void conv1(float mem_1[1][28][28],float mem_2[4][26][26]){
	Conv_func<1,28,4,26>( mem_1,mem_2,conv1_weight,conv1_bias);
}
void conv2(float mem_2[4][26][26],float mem_3[4][24][24]){
	Conv_func<4,26,4,24>( mem_2,mem_3,conv2_weight,conv2_bias);
}
void conv3(float mem_4[4][12][12],float mem_5[4][10][10]){
	Conv_func<4,12,4,10>( mem_4,mem_5,conv3_weight,conv3_bias);
}


void fc_layer1(float input[100],float output[16]){
	FC_layer<100,16,true>(input,output,fc1_weight,fc1_bias);
}
void fc_layer2(float input[16],float output[10]){
	FC_layer<16,10,false>(input,output,fc2_weight,fc2_bias);
}


void HW_accel(hls::stream<axis_data> &inputPort, hls::stream<axis_data> &outputPort){
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis register both port=outputPort
#pragma HLS INTERFACE axis register both port=inputPort

	#pragma HLS DATAFLOW

	float mem_1[1][28][28];
	float mem_2[4][26][26];
	float mem_3[4][24][24];
#pragma HLS ARRAY_PARTITION variable=mem_3 cyclic factor=2 dim=3
	float mem_4[4][12][12];
	float mem_5[4][10][10];
#pragma HLS ARRAY_PARTITION variable=mem_5 cyclic factor=2 dim=3
	float mem_6[4][5][5];
	float fc1_output[16];
#pragma HLS ARRAY_PARTITION variable=fc1_output complete
	float fc2_output[10];
#pragma HLS ARRAY_PARTITION variable=fc1_output complete

	read_input(inputPort, mem_1);

	conv1(mem_1,mem_2);
	conv2(mem_2,mem_3);
	maxPool<4,24,12>(mem_3,mem_4);
	conv3( mem_4,mem_5);
	maxPool<4,10,5>(mem_5,mem_6);
	float *x_flat = (float *)mem_6;  // Flatten the array
	fc_layer1(x_flat,fc1_output);
	fc_layer2(fc1_output,fc2_output);

	write_output(outputPort, fc2_output);
}

