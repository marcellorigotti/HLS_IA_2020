#include "lenet_cnn_float.h"
#include <math.h>
//@kintex7 haslo do gse5

void Fc1_40_400(	float 	input[POOL2_NBOUTPUT][POOL2_HEIGHT][POOL2_WIDTH], 			        // IN
    			        float 	kernel[FC1_NBOUTPUT][POOL2_NBOUTPUT][POOL2_HEIGHT][POOL2_WIDTH],	// IN
    			        float 	bias[FC1_NBOUTPUT],							                        // IN
    			        float 	output[FC1_NBOUTPUT]){
  float fc_sum = 0;
  for(int x = 0; x < FC1_NBOUTPUT; x++){
    fc_sum = 0;
    for(int i = 0; i < POOL2_NBOUTPUT; i++){
      for(int j = 0; j < POOL2_HEIGHT; j++){
        for(int k = 0; k < POOL2_WIDTH; k++){
          fc_sum += input[i][j][k] * kernel[x][i][j][k];
        }
      }
    }
    fc_sum += bias[x];
    if(fc_sum < 0){
      output[x] = 0;
    }
    else{
      output[x] = fc_sum;
    }
  }
}


void Fc2_400_10(	float 	input[FC1_NBOUTPUT], 			        // IN
    			        float 	kernel[FC2_NBOUTPUT][FC1_NBOUTPUT],	    // IN
    			        float 	bias[FC2_NBOUTPUT],			            // IN
    			        float 	output[FC2_NBOUTPUT]){
  float fc_sum = 0;
  for(int i = 0; i < FC2_NBOUTPUT; i++){
    fc_sum = 0;
    for(int j = 0; j < FC1_NBOUTPUT; j++){
      fc_sum += input[j] * kernel[i][j];
    }
    fc_sum += bias[i];
    if(fc_sum < 0){
      output[i] = 0;
    }
    else{
      output[i] = fc_sum;
    }
  }
}


void Softmax(float vector_in[FC2_NBOUTPUT], float vector_out[FC2_NBOUTPUT]){
    float soft_sum = 0;
    for(int i = 0; i < FC2_NBOUTPUT; i++){
      soft_sum += exp(vector_in[i]);
    }
    for(int j = 0; j < FC2_NBOUTPUT; j++){
      vector_out[j] = exp(vector_in[j]) / soft_sum;
    }
}
