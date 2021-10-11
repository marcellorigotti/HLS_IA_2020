#include "lenet_cnn_float.h"
#include <math.h>
//@kintex7 haslo do gse5

short fc_sum(short DIM_X, short DIM_Y, short p_of_matrix[DIM_X][DIM_Y], short kernel[DIM_X][DIM_Y]){
  unsigned short x,y;
	int fc_sum = 0;

	for(y = 0; y < DIM_X; y++){
		for(x = 0; x < DIM_Y; x++){
			#pragma HLS pipeline II=1
			fc_sum += (p_of_matrix[y][x]*kernel[y][x]);
		}
	}
	return SHORT2FLOAT(fc_sum);
}

void Fc1_40_400(	short 	input[POOL2_NBOUTPUT][POOL2_HEIGHT][POOL2_WIDTH], 			        // IN
					short 	kernel[FC1_NBOUTPUT][POOL2_NBOUTPUT][POOL2_HEIGHT][POOL2_WIDTH],	// IN
					short 	bias[FC1_NBOUTPUT],							                        // IN
					short 	output[FC1_NBOUTPUT]){
  short sum;
  unsigned int x, i = 0;


  for(x = 0; x < FC1_NBOUTPUT; x++){
	#pragma HLS pipeline II=1
    sum = 0;
    for(i = 0; i < POOL2_NBOUTPUT; i++){
      sum += fc_sum(POOL2_HEIGHT, POOL2_WIDTH, input[i], kernel[x][i]);
    }
    sum += bias[x];
    output[x] = RELU_F(sum);
  }
}


void Fc2_400_10(	short 	input[FC1_NBOUTPUT], 			        // IN
					short 	kernel[FC2_NBOUTPUT][FC1_NBOUTPUT],	    // IN
					short 	bias[FC2_NBOUTPUT],			            // IN
					short 	output[FC2_NBOUTPUT]){
  int sum;

  unsigned short i, j = 0;
  for(i = 0; i < FC2_NBOUTPUT; i++){

	  sum = 0;
    for(j = 0; j < FC1_NBOUTPUT; j++){
	  #pragma HLS pipeline II=1
      sum += input[j] * kernel[i][j];
    }
	sum += bias[i];
//    output[i] = RELU_F(sum/ (1 << FIXED_POINT));
    //output[i] = RELU_F(sum >> FIXED_POINT);
    output[i] = sum >> FIXED_POINT;
    if(sum < 0){
    	output[i] = 0;
    }
  }
}


void Softmax(short vector_in[FC2_NBOUTPUT], float vector_out[FC2_NBOUTPUT]){
    float soft_sum = 0;
    unsigned short i, j = 0;

    for(i = 0; i < FC2_NBOUTPUT; i++){
      vector_out[i] = expf(SHORT2FLOAT(vector_in[i]));
      soft_sum += vector_out[i];
    }
    for(j = 0; j < FC2_NBOUTPUT; j++){
      vector_out[j] = vector_out[j] / soft_sum;
    }
}
