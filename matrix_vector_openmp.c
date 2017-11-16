//   PCA ASSIGNMENT
//   OPENMP program for Matrix Vector Multiplication using Column Decomposition technique
//   NAME: CHITRESH SHARMA
//   ROLL: 14UCS034



#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<omp.h>
#include<math.h>
void main()
{
	int order;
        // Taking Order of  the square Matrix from user
        printf("\nEnter the size of the Matrix which will have random values automatically: ");
        scanf("%d",&order);

        // Input : a Matrix and b Vector
        // Output: c Vector

        int mat[order][order],a_vector[order],sol_vector[order];
	

        // Taking a Matrix and b Vector Input from user

        int i,j;
	srand(time(NULL));	//to seed with current time so that every time new matrix generated

	//initialize the output vector with 0	
	for (i =0;i<order;i++)
	{	
		sol_vector[i]=0;
	}
	//initializing matrix with random values
	 for(i=0;i<order;i++)
        {
            for(j=0;j<order;j++)
		mat[i][j]=rand()%10;//for nos 0-9
        }
	
        printf("\nRandomly Generated Matrix of order %d : \n",order);

        for(i=0;i<order;i++)
        {
            for(j=0;j<order;j++)
                printf("%d\t\t",mat[i][j]);

            printf("\n");
        }

	
        printf("\nEnter the %d Vector elements ,enter 0 for autofill, or give any other value to manually fill: \n",order);
	int opt;
	scanf("%d",&opt);
	if(opt==0)
	{
	 for(j=0;j<order;j++)
		a_vector[j]=rand()%10 + 1;//for nos 0-9
	for(j=0;j<order;j++)
                printf("%d\t\t",a_vector[j]);
	}
	else{
		printf("\n\n Manually Enter vector elements:\t");
        	for(i=0;i<order;i++)
       		 {
       		     scanf("%d",&a_vector[i]);
        	}
	}
        // Multiplying Column Wise

        omp_set_num_threads(order);
	//setting the number of threads equal to the number of columns

        #pragma omp parallel private(i) 

        {
            int thread_id=omp_get_thread_num();
            for(i=0;i<order;i++)
		{                	
			sol_vector[i]+=mat[i][thread_id]*a_vector[thread_id];

		}
        }

        // Displaying Result Vector C

        printf("\n Solution Vector C is: \n");

        for(i=0;i<order;i++)
            printf("%d\n",sol_vector[i]);

}
