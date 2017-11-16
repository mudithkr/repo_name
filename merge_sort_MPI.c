//   PCA ASSIGNMENT
//   MPI PROGRAM implementing parallel merge sort 
//   NAME: CHITRESH SHARMA
//   ROLL: 14UCS034


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

void merge(int *, int *, int, int, int);
void mergeSort(int *, int *, int, int);

int main(int argc, char** argv) {
	
	//Create the array 
	printf("enter size of array\n");
	scanf("%d",&n);
	int *old_array = malloc(n * sizeof(int));
	int c;
	srand(time(NULL));
	
	printf("This array is  unsorted \n: ");
	for(c = 0; c < n; c++) {
		
		old_array[c] = rand() % n;
		printf("%d ", old_array[c]);
		
		}

	printf("\n");
	printf("\n");
	
	
	int world_rank;
	int world_size;
	
	MPI_INIT(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
		
	//dividing array
	int size = n/world_size;
	
	//distributing array ot processes
	int *sub_array = malloc(size * sizeof(int));
	MPI_Scatter(old_array, size, MPI_INT, sub_array, size, MPI_INT, 0, MPI_COMM_WORLD);
	
	//mergesorting
	int *tmp_array = malloc(size * sizeof(int));
	mergeSort(sub_array, tmp_array, 0, (size - 1));
	
	//gathering
	int *sorted = NULL;
	if(world_rank == 0) {
		
		sorted = malloc(n * sizeof(int));
		
		}
	
	MPI_Gather(sub_array, size, MPI_INT, sorted, size, MPI_INT, 0, MPI_COMM_WORLD);
	
	
	if(world_rank == 0) {
		
		int *other_array = malloc(n * sizeof(int));
		mergeSort(sorted, other_array, 0, (n - 1));
		
		
		printf("This is the sorted array: ");
		for(c = 0; c < n; c++) {
			
			printf("%d ", sorted[c]);
			
			}
			
		printf("\n");
		printf("\n");
			
		
		free(sorted);
		free(other_array);
			
		}
	
	free(old_array);
	free(sub_array);
	free(tmp_array);
        MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();	
	}

void merge(int *a, int *b, int l, int m, int r) {
	
	int h, i, j, k;
	h = l;
	i = l;
	j = m + 1;
	
	while((h <= m) && (j <= r)) {
		if(a[h] <= a[j]) {
			
			b[i] = a[h];
			h++;
			
			}
		else {
			b[i] = a[j];
			j++;
			
			}
		i++;
		}
	if(m < h) {
		for(k = j; k <= r; k++) {
			
			b[i] = a[k];
			i++;			
			}
		}
	else {
		
		for(k = h; k <= m; k++) {
			b[i] = a[k];
			i++;
			}
		}
	for(k = l; k <= r; k++) {
		
		a[k] = b[k];
		
		}		
	}

void mergeSort(int *a, int *b, int l, int r) {
	int m;
		if(l < r) {
		m = (l + r)/2;
		mergeSort(a, b, l, m);
		mergeSort(a, b, (m + 1), r);
		merge(a, b, l, m, r);
		}
}
