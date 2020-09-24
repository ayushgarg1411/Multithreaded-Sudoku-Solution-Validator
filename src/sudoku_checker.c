/**
 * @file: sudoku_checker.c
 * @author: Name, Student Number, Section, CSCI 360, VIU
 * @version: 1.0.0
 * @modified: August 05, 2020
 *
 * Implements the functions required for sudoku checker application.
 *
 */

/*
 * Include all the header files.
 */


extern int puzzle[PUZZLE_SIZE+1][PUZZLE_SIZE+1]; 	// Im memory solutiona of a sudoku puzzle
extern int status_map[NUMBER_OF_THREADS];       	// Status maps updated by corresponding worker thread


