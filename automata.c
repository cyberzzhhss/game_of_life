#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

static int ** allocate_board(int size);
static void free_board(int ** board, int size);

int main (int argc, char * argv[]) {
	
	int ** current_board;
    int ** previous_board; 					  
    int ** temp;							  
    int t, i, j, neighbors;					  
    double start, end;
    int iterations = atoi(argv[1]) + 1;		  // X  current_board is 1 timestep behind before printing
    int size = atoi(argv[2]) + 2; 			  // Y
    int threads = atoi(argv[3]); 			  // Z
    FILE *input_file = fopen(argv[4], "r");   // input file
    current_board = allocate_board(size);	  // create board for current_board 
    previous_board = allocate_board(size); 	  // create board for previous_board 
    for (int i = 1; i < size - 1; i++) {      // read from the file
        for (int j = 1; j < size - 1; j++) {
            fscanf(input_file, "%d", &current_board[i][j]);
			previous_board[i][j] = current_board[i][j]; 
		}
    }
    fclose(input_file);
	start = omp_get_wtime();
	for (t = 0 ; t < iterations ; t++) {
		#pragma omp parallel num_threads (threads) private(i, j, neighbors)
		{
			#pragma omp for
			for (i = 1 ; i < size - 1 ; i++) {
				for (j = 1 ; j < size - 1 ; j++) {
                    neighbors = previous_board[i][j - 1] + previous_board[i][j + 1] + previous_board[i - 1][j - 1] + previous_board[i - 1][j] + previous_board[i - 1][j + 1] + previous_board[i + 1][j + 1] + previous_board[i + 1][j] + previous_board[i + 1][j - 1];
                    if ((neighbors + previous_board[i][j] == 3) || neighbors == 3) {
                        current_board[i][j] = 1;
					} else {
						current_board[i][j] = 0;
					}
				}
			}
		}
		temp = current_board;
		current_board = previous_board;
		previous_board = temp;
	}
	end = omp_get_wtime(); 
	printf("Time: %f seconds\n", end - start);
	char filename[128];                     //print the final board to the output_file
    sprintf(filename, "%s.out", argv[4]);   // filename.out
    FILE *output_file;
    output_file = fopen(filename, "w");
    for (int i = 1; i < size - 1; ++i) {        
        for (int j = 1; j < size - 1; ++j) {
            fprintf(output_file, "%d ", current_board[i][j]);
        }
        fprintf(output_file, "\n");
    }
    fclose(output_file);
	free_board(current_board, size);
	free_board(previous_board, size);
	return 0;
}

static int ** allocate_board(int size) {
	int ** board;
	int i, j;
	board = malloc(size * sizeof(int*));
	for (i = 0; i < size ; i++) {
		board[i] = malloc(size * sizeof(int));
	}
	for (i = 0; i < size ; i++){
		for (j = 0; j < size ; j++){
			board[i][j] = 0;
		}
	}
	return board;
}

static void free_board(int ** board, int size) {
	int i;
	for (i = 0 ; i < size ; i++){
		free(board[i]);
	} free(board);
}