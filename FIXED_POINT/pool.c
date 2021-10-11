#include "lenet_cnn_float.h"

short max(short a, short b){
  if(a > b){
    return a;
  }
  else{
    return b;
  }
}

void Pool1_24x24x20_2x2x20_2_0(	short 	input[CONV1_NBOUTPUT][CONV1_HEIGHT][CONV1_WIDTH], 	    // IN
				                        short 	output[POOL1_NBOUTPUT][POOL1_HEIGHT][POOL1_WIDTH])
{

  unsigned short i,j,k,x,y;
  short max_val = 0;
  for(i = 0; i < CONV1_NBOUTPUT; i++){
    for(j = 0; j < CONV1_HEIGHT; j = j + POOL1_DIM){
      for(k = 0; k < CONV1_WIDTH; k = k + POOL1_DIM){
        max_val = 0;
        for(x = 0; x < POOL1_DIM; x++){
          for(y = 0; y < POOL1_DIM; y++){
		#pragma HLS pipeline II=1
            max_val = max(max_val, input[i][j+x][k+y]);
          }
        }
        output[i][j/POOL1_DIM][k/POOL1_DIM] = max_val;
      }
    }
  }
}


void Pool2_8x8x40_2x2x40_2_0(	short 	input[CONV2_NBOUTPUT][CONV2_HEIGHT][CONV2_WIDTH], 	    // IN
				                      short 	output[POOL2_NBOUTPUT][POOL2_HEIGHT][POOL2_WIDTH])
{

  unsigned short i,j,k,x,y;
  short max_val = 0;
  for(i = 0; i < CONV2_NBOUTPUT; i++){
    for(j = 0; j < CONV2_HEIGHT; j = j + POOL2_DIM){
      for(k = 0; k < CONV2_WIDTH; k = k + POOL2_DIM){
        max_val = 0;
        for(x = 0; x < POOL2_DIM; x++){
          for(y = 0; y < POOL2_DIM; y++){
			#pragma HLS pipeline II=1
            max_val = max(max_val, input[i][j+x][k+y]);
          }
        }
        output[i][j/POOL1_DIM][k/POOL1_DIM] = max_val;
      }
    }
  }
}
