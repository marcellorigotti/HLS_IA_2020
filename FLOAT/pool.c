#include "lenet_cnn_float.h"

float max(float a, float b){
  if(a > b){
    return a;
  }
  else{
    return b;
  }
}

void Pool1_24x24x20_2x2x20_2_0(	float 	input[CONV1_NBOUTPUT][CONV1_HEIGHT][CONV1_WIDTH], 	    // IN
				                        float 	output[POOL1_NBOUTPUT][POOL1_HEIGHT][POOL1_WIDTH])
{
  float max_val = 0;
  for(int i = 0; i < CONV1_NBOUTPUT; i++){
    for(int j = 0; j < CONV1_HEIGHT; j = j + POOL1_DIM){
      for(int k = 0; k < CONV1_WIDTH; k = k + POOL1_DIM){
        max_val = 0;
        for(int x = 0; x < POOL1_DIM; x++){
          for(int y = 0; y < POOL1_DIM; y++){
            max_val = max(max_val, input[i][j+x][k+y]);
          }
        }
        output[i][j/POOL1_DIM][k/POOL1_DIM] = max_val;
      }
    }
  }
}


void Pool2_8x8x40_2x2x40_2_0(	float 	input[CONV2_NBOUTPUT][CONV2_HEIGHT][CONV2_WIDTH], 	    // IN
				                      float 	output[POOL2_NBOUTPUT][POOL2_HEIGHT][POOL2_WIDTH])
{
  float max_val = 0;
  for(int i = 0; i < CONV2_NBOUTPUT; i++){
    for(int j = 0; j < CONV2_HEIGHT; j = j + POOL2_DIM){
      for(int k = 0; k < CONV2_WIDTH; k = k + POOL2_DIM){
        max_val = 0;
        for(int x = 0; x < POOL2_DIM; x++){
          for(int y = 0; y < POOL2_DIM; y++){
            max_val = max(max_val, input[i][j+x][k+y]);
          }
        }
        output[i][j/POOL1_DIM][k/POOL1_DIM] = max_val;
      }
    }
  }
}
