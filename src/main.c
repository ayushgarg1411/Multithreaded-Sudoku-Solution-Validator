/**
 * @file: main.c
 * @author: Name, Student Number, Section, CSCI 360, VIU
 * @version: 1.0.0
 * @modified: August 05, 2020
 *
 * Sudoku Checker application.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "sudoku_checker.h"


int puzzle[PUZZLE_SIZE+1][PUZZLE_SIZE+1]; 	// In memory solutiona of a sudoku puzzle
int status_map[NUMBER_OF_THREADS];       	// Status maps updated by corresponding worker thread

parameters* worker_params[NUMBER_OF_THREADS]; 	// Array of worker thread parameter pointers
pthread_t workers[NUMBER_OF_THREADS];		// Array of worker threads


int main(int argc, char** argv) {
	//Read the sudoku solution from	the file specified by command line argumant
	//Display the solution to the scree.
	//Create and run all the column threads with appropriate thread paramaters to verify the columns of the solution.
	//Create and run all the row threads with appropriate thread parameters to verify the rows of the solution.
	//Create and run all the subgrid threads with appropariate thread parameters to verify the subgrids of the solution.
	//Wait for all thread to complete.
	//Check the results from all threads through status map.
	//Display whether the solution is valid or not.

	return 0;
}
	
