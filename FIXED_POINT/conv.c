#include "lenet_cnn_float.h"
#include <stdlib.h>

short conv_sum(short DIM_Y, short DIM_X, short p_of_matrix[DIM_Y][DIM_X], short kernel[DIM_Y][DIM_X]){
	unsigned short x,y;
	int conv_sum = 0;
	int tmp;

	for(y = 0; y < DIM_Y; y++){

		for(x = 0; x < DIM_X; x++){
			tmp = (p_of_matrix[x][y] * kernel[x][y]);
#pragma HLS pipeline II=1
			#pragma HLS RESOURCE variable=tmp core=MulnS latency=1
			conv_sum += tmp;
		}
	}
	return SHORT2FLOAT(conv_sum);
}

void Conv1_28x28x1_5x5x20_1_0(	short 			  input[IMG_DEPTH][IMG_HEIGHT][IMG_WIDTH], 	                // IN
								short 		    kernel[CONV1_NBOUTPUT][IMG_DEPTH][CONV1_DIM][CONV1_DIM], 	// IN
								short 		    bias[CONV1_NBOUTPUT],						                // IN
								short 		    output[CONV1_NBOUTPUT][CONV1_HEIGHT][CONV1_WIDTH]){
	unsigned short i,j,k,x,y;
	short matrix_sum[CONV1_DIM][CONV1_DIM];
	short sum = 0;
//
	#pragma HLS RESOURCE variable=kernel core=RAM_1P_LUTRAM
	#pragma HLS RESOURCE variable=output core=RAM_1P_LUTRAM

	#pragma HLS_ARRAY_PARTITION variable=input complete dim=3
	for(i = 0; i < CONV1_NBOUTPUT; i++){
	 for(j = 0; j < CONV1_HEIGHT; j++){
		 for(k = 0; k < CONV1_WIDTH; k++){
//			#pragma HLS pipeline
			 for(x = 0; x < CONV1_DIM; x++){
				 for(y = 0; y < CONV1_DIM; y++){

					 matrix_sum[x][y] = input[0][k+x][j+y];
				 }
			 }
			 sum = conv_sum(CONV1_DIM, CONV1_DIM, matrix_sum,kernel[i][0]) + bias[i];

			 //output[i][k][j] = RELU_F(sum);
			 output[i][k][j] = sum;
			if(output[i][k][j] < 0){
				output[i][k][j] = 0;
			}
		 }
	 }
	}
}


void Conv2_12x12x20_5x5x40_1_0(	short input[POOL1_NBOUTPUT][POOL1_HEIGHT][POOL1_WIDTH], 	            // IN
								                short kernel[CONV2_NBOUTPUT][POOL1_NBOUTPUT][CONV2_DIM][CONV2_DIM], 	// IN
								                short bias[CONV2_NBOUTPUT], 						                    // IN
								                short output[CONV2_NBOUTPUT][CONV2_HEIGHT][CONV2_WIDTH]){
	unsigned short i,k,l,j,x,y;
	short matrix_sum[CONV2_DIM][CONV2_DIM];
	short sum = 0;
//	#pragma HLS RESOURCE variable=kernel core=RAM_2P_BRAM
//	#pragma HLS RESOURCE variable=output core=RAM_2P_BRAM
//	#pragma HLS_ARRAY_PARTITION variable=input complete dim=3
//	#pragma HLS RESOURCE variable=kernel core=RAM_1P_LUTRAM



	for(i = 0; i < CONV2_NBOUTPUT; i++){
		for(k = 0; k < CONV2_HEIGHT; k++){
			for(l = 0; l < CONV2_WIDTH; l++){
//				#pragma HLS pipeline
				sum = 0;
				for(j = 0; j < POOL1_NBOUTPUT; j++){

					for(x = 0; x < CONV2_DIM; x++){
  						for(y = 0; y < CONV2_DIM; y++){
								matrix_sum[x][y] = input[j][l+x][k+y];
  						}}
						int conv_sum = 0;
						int tmp;

						for(short t = 0; t < CONV2_DIM; t++){

							for(short g = 0; g < CONV2_DIM; g++){
								tmp = ((short)matrix_sum[g][t] * kernel[g][t]);
								//#pragma HLS pipeline II=1
								//			#pragma HLS RESOURCE variable=tmp core=MulnS latency=1
								conv_sum += tmp;
							}
						}
						sum += SHORT2FLOAT(conv_sum);



				}
				sum += bias[i];
				output[i][l][k] = sum;
				//output[i][l][k] = RELU_F(sum);
				if(output[i][l][k] < 0){
					output[i][l][k] = 0;
				}
			}
		}
	}
 }
