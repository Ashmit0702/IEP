#include "header.h"
#include"input_tensor.h"
#include"f2_output.h"


void HW_accel(hls::stream<axis_data> &inputPort, hls::stream<axis_data> &outputPort);

int main()
{
    hls::stream<axis_data> in_stream;
    hls::stream<axis_data> out_stream;

    axis_data pkt;

    float output[10];

    // ---------------------------------------
    // Send input via AXI stream
    // ---------------------------------------
    for (int i = 0; i < 28; i++)
    {
        for (int j = 0; j < 28; j++)
        {
            pkt.data = input_tensor[0][i][j];
            pkt.last = (i == 27 && j == 27);

            in_stream.write(pkt);
        }
    }

    // ---------------------------------------
    // Call accelerator
    // ---------------------------------------

    HW_accel(in_stream, out_stream);

    // ---------------------------------------
    // Read output via AXI stream
    // ---------------------------------------

	for (int j = 0; j < 10; j++)
	{
		axis_data out_pkt = out_stream.read();
		output[j] = out_pkt.data;
	}

	for(int j=0;j<10;j++){
		printf("%f\t", output[j]);
	}
	printf("\n===== Diff =======\n");

	for(int j=0;j<10;j++){
		printf("%f\t", output[j]-f2_out_1[j]);
	}
	printf("\n");

	float diff=0;
	for(int j=0;j<10;j++){
		diff += (output[j]-f2_out_1[j])*(output[j]-f2_out_1[j]);
	}

	float MSE=diff/10;

	if(MSE>1){
		printf("Error. \n Total MSE = %f",MSE);
		return -1;
	}

		printf("Success!!!");
		return 0;
}
