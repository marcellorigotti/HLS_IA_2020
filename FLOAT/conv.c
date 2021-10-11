#include "lenet_cnn_float.h"
#include <stdio.h>

void Conv1_28x28x1_5x5x20_1_0(	float 			  input[IMG_DEPTH][IMG_HEIGHT][IMG_WIDTH], 	                // IN
								                float 		    kernel[CONV1_NBOUTPUT][IMG_DEPTH][CONV1_DIM][CONV1_DIM], 	// IN
								                float 		    bias[CONV1_NBOUTPUT],						                // IN
								                float 		    output[CONV1_NBOUTPUT][CONV1_HEIGHT][CONV1_WIDTH]){
   float conv_sum = 0;
	 for(int i = 0; i < CONV1_NBOUTPUT; i++){
		 for(int j = 0; j < CONV1_HEIGHT; j++){
			 for(int k = 0; k < CONV1_WIDTH; k++){
				 conv_sum = 0;
				 for(int x = 0; x < CONV1_DIM; x++){
					 for(int y = 0; y < CONV1_DIM; y++){
						 conv_sum = kernel[i][0][x][y] * input[0][x+j][y+k] + conv_sum;
					 }
				 }
				 output[i][j][k] = conv_sum + bias[i];
				 if(output[i][j][k] < 0){
					 output[i][j][k] = 0;
				 }

			 }
		 }
	 }
}


void Conv2_12x12x20_5x5x40_1_0(	float input[POOL1_NBOUTPUT][POOL1_HEIGHT][POOL1_WIDTH], 	            // IN
								                float kernel[CONV2_NBOUTPUT][POOL1_NBOUTPUT][CONV2_DIM][CONV2_DIM], 	// IN
								                float bias[CONV2_NBOUTPUT], 						                    // IN
								                float output[CONV2_NBOUTPUT][CONV2_HEIGHT][CONV2_WIDTH]){
	float conv_sum = 0;
	for(int i = 0; i < CONV2_NBOUTPUT; i++){
			for(int k = 0; k < CONV2_HEIGHT; k++){
				for(int l = 0; l < CONV2_WIDTH; l++){
          conv_sum = 0;
          for(int j = 0; j < POOL1_NBOUTPUT; j++){
  					for(int x = 0; x < CONV2_DIM; x++){
  						for(int y = 0; y < CONV2_DIM; y++){
  							conv_sum = (kernel[i][j][x][y] * input[j][x+k][y+l]) + conv_sum;
  						}
            }
          }
          output[i][k][l] = conv_sum + bias[i];
          if(output[i][k][l] < 0){
            output[i][k][l] = 0;
          }
				}
  		}
  	}
  }
