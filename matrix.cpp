#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <iostream>

#define LM 6
#define LN 6
#define LP 6

#define M ( 1 << LM )
#define N ( 1 << LN )
#define P ( 1 << LP )


 void multiply_Arrays_hw(uint8_t a[M][N], uint8_t b[N][P], uint32_t result[M][P]){

	uint8_t bram_a[M][N];
	uint8_t bram_b[N][P];


	#pragma HLS ARRAY_PARTITION variable=bram_a cyclic factor=8 dim=2
	#pragma HLS ARRAY_PARTITION variable=bram_b cyclic factor=8 dim=1



	for (int i = 0 ; i < M ; i++){

		for(int j = 0 ; j < N ; j++){
			bram_a[i][j] = a[i][j];
		}
	}

	for (int i = 0 ; i < N ; i++){
		for(int j = 0 ; j < P ; j++){
			bram_b[i][j] = b[i][j];
		}
	}


	for(int i = 0; i < M; i++){
		for(int j = 0; j < P; j++){
            uint32_t r = 0;
			#pragma HLS PIPELINE IT=1
            for(int k = 0; k < N; k++){
			   	r += bram_a[i][k] * bram_b[k][j];
            }
            result[i][j] = r;
        }
    }
 }
