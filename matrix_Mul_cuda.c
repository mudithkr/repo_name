//   PCA ASSIGNMENT
//   CUDA Program for Matrix  Multiplication 
//   NAME: CHITRESH SHARMA
//   ROLL: 14UCS034

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define TILE_WIDTH 2

__global__ void MatrixMul( float *Md , float *Nd , float *Pd , const int WIDTH )
{


           unsigned int col = TILE_WIDTH*blockIdx.x + threadIdx.x ;
           unsigned int row = TILE_WIDTH*blockIdx.y + threadIdx.y ;

         for (int k = 0 ; k<WIDTH ; k++ )
          {
           Pd[row*WIDTH + col]+= Md[row * WIDTH + k ] * Nd[ k * WIDTH + col] ;
          }
}

int main ()
{
   int WIDTH = 8 ;
   float array1_h[WIDTH][WIDTH] ,array2_h[WIDTH][WIDTH], result_array_h[WIDTH][WIDTH] ,M_result_array_h[WIDTH][WIDTH]  ; //host array
   float *array1_d , *array2_d ,*result_array_d  ,*M_result_array_d ; // device array
 
  int i,j;

  //input in host array
  srand(time(NULL));	
  for ( i = 0 ; i<WIDTH ; i++ )
  {
     for (j = 0 ; j<WIDTH ; j++ )
     {
        array1_h[i][j] = rand()%10 ; //this will be Md
        array2_h[i][j] = rand()%10 ; //this will be Nd
     }
  }

  cudaMalloc((void **) &array1_d , WIDTH*WIDTH*sizeof (int) ) ;
  cudaMalloc((void **) &array2_d , WIDTH*WIDTH*sizeof (int) ) ;

  cudaMemcpy ( array1_d , array1_h , WIDTH*WIDTH*sizeof (int) , cudaMemcpyHostToDevice ) ;
  cudaMemcpy ( array2_d , array2_h , WIDTH*WIDTH*sizeof (int) , cudaMemcpyHostToDevice ) ;

  cudaMalloc((void **) &result_array_d , WIDTH*WIDTH*sizeof (int) ) ;
  cudaMalloc((void **) &M_result_array_d , WIDTH*WIDTH*sizeof (int) ) ;

  dim3 dimGrid ( WIDTH/TILE_WIDTH , WIDTH/TILE_WIDTH ,1 ) ;
  dim3 dimBlock( TILE_WIDTH, TILE_WIDTH, 1 ) ;

  MatrixMul <<<dimGrid,dimBlock>>> ( array1_d , array2_d ,M_result_array_d , WIDTH) ;

  cudaMemcpy(M_result_array_h , M_result_array_d , WIDTH*WIDTH*sizeof(int) , cudaMemcpyDeviceToHost) ;

  //printing the resultant matrix
  for ( i = 0 ; i<WIDTH ; i++ )
  {
      for ( j = 0 ; j < WIDTH ; j++ )
     {
        printf ("%f   ",M_result_array_h[i][j] ) ;
     }
 printf ("\n") ;
}
return 0;
}

