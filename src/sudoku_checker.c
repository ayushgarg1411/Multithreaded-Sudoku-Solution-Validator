/**
 * @file: main.c
 * @author: Ayush Garg, 656665809, F20N01, CSCI 360, VIU
 * @version: 1.0.0
 * @modified: October 15, 2020
 *
 * Sudoku Checker application.
 *
 */

/*
 * Include all the header files.
 */
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <pthread.h>

 #include "sudoku_checker.h"



extern int puzzle[PUZZLE_SIZE+1][PUZZLE_SIZE+1]; 	// Im memory solutiona of a sudoku puzzle
extern int status_map[NUMBER_OF_THREADS];       	// Status maps updated by corresponding worker thread

void read_from_file(FILE* sudoku_file){
  char word;
  int i = 0, j = 0;
  while(fscanf(sudoku_file,"%c",word) != EOF) {
    if(word == "," || word == "\n")
      continue;
    else {
      puzzle[i][j]==atoi(word);
      j++;
      if(j == 8) {
        i++;
        j = 0;
      }
    }
  }
}


void show_puzzle(){
  for(int i=0; i<9; i++){
    for(int j=0; j<9; j++){
      printf("%d ", puzzle[i][j]);
    }
    printf("\n");
  }
}


void* row_worker(void* param){
	parameters *params = (parameters*) param;
  int thread_no = params->thread_no;
	int row = params->row;
	int col = params->column;
	if (row != 0 || col > 8) {
		pthread_exit(NULL); //Row or column invalid for this column section
	}

	int tempArr[9];
	for (int i = 0; i < 9; i++) {
		int n = puzzle[i][col];
		if (n < 1 || n > 9 || tempArr[n - 1] == 1) {
			pthread_exit(NULL);
		}
    else {
			tempArr[n - 1] = 1;
		}
	}
	// If everything is fine, enter 1 in status map at particular thread
	status_map[thread_no] = 1;
	pthread_exit(NULL);
}


void *col_worker(void* param) {
	parameters *params = (parameters*) param;
  int thread_no = params->thread_no;
	int row = params->row;
	int col = params->column;
	if (col != 0 || row > 8) {
		pthread_exit(NULL); //Row or column invalid for this column section
	}

	int tempArr[9];
	for (int i = 0; i < 9; i++) {
		int n = puzzle[row][i];
		if (n < 1 || n > 9 || tempArr[n - 1] == 1) {
			pthread_exit(NULL);
		}
    else {
			tempArr[n - 1] = 1;
		}
	}
	// If everything is fine, enter 1 in status map at particular thread
	status_map[thread_no] = 1;
	pthread_exit(NULL);
}


int check_status_map(){
  for(int i=0; i<27; i++){
    if(status_map[i] == 0)
      return 0;
  }
  return 1;
}
