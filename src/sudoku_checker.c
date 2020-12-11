/**
 * @file: main.c
 * @author: Ayush Garg, 656665809, F20N01, CSCI 360, VIU
 * @version: 1.0.0
 * @modified: Dec 10, 2020
 *

 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <pthread.h>
 #include "sudoku_checker.h"


extern int puzzle[PUZZLE_SIZE+1][PUZZLE_SIZE+1];
extern int status_map[NUMBER_OF_THREADS];



void read_from_file(FILE* sudoku_file)
{
  for(int i = 0; i < PUZZLE_SIZE; i++)
  {
			for(int j = 0; j < PUZZLE_SIZE; j++)
      {
        fscanf( sudoku_file, "%d,",&puzzle[i][j]);
			}
	}
}



void show_puzzle()
{
  for(int i=0; i<PUZZLE_SIZE; i++)
  {
    for(int j=0; j<PUZZLE_SIZE; j++)
    {
      printf("%d ", puzzle[i][j]);
    }
    printf("\n");
  }
}



void* row_worker(void* param)
{
	parameters *params = (parameters*) param;
  int tempArr[10]={0};
	int row = params->x;
  int t_num = params->thread_no;
  printf("Thread %d is checking row %d\n",t_num, row);
  for (int i = 0; i < PUZZLE_SIZE; i++)
  {
		int n = puzzle[row][i];
		if (n < 1 || n > PUZZLE_SIZE || tempArr[n-1] == 1)
    {
			pthread_exit(NULL);
		}
    else
    {
			tempArr[n-1] = 1;
		}
	}
  printf("Status of row %d is 1 found by thread %d.\n",row,t_num);
	status_map[t_num] = 1;
	pthread_exit(NULL);
}



void *col_worker(void* param)
{
	parameters *params = (parameters*) param;
  int tempArr[10]={0};
	int col = params->y;
  int t_num = params->thread_no;
  printf("Thread %d is checking column %d\n",t_num, col);
  for (int i = 0; i < PUZZLE_SIZE; i++)
  {
		int n = puzzle[i][col];
		if (n < 1 || n > PUZZLE_SIZE || tempArr[n-1] == 1)
    {
			pthread_exit(NULL);
		}
    else
    {
			tempArr[n-1] = 1;
		}
	}
  printf("Status of column %d is 1 found by thread %d.\n",col,t_num);
	status_map[t_num] = 1;
	pthread_exit(NULL);
}



void* subgrid_worker(void* param)
{
  parameters *params = (parameters*) param;
	int row = params->x;
	int col = params->y;
  int t_num = params->thread_no;
  printf("Thread %d is checking subgrid with starting (row, column): (%d, %d)\n", t_num, row, col);
  int tempArr[10];
  for(int i = row; i < (row + 3) ; i++)
  {
    for(int j = col; j < (col + 3) ; j++)
    {
      int n = puzzle[i][j];
      if (n < 1 || n > 9 || tempArr[n-1] == 1)
      {
  			pthread_exit(NULL);
  		}
      else
      {
  			tempArr[n-1] = 1;
  		}
    }
  }
  printf("Status of subgrid (row, col): (%d, %d) is 1 found by thread %d.\n",row, col,t_num);
	status_map[t_num] = 1;
	pthread_exit(NULL);
}



int check_status_map()
{
  for(int i=0; i<27; i++)
  {
    if(status_map[i] != 1)
    {
      return 0;
    }
  }
  return 1;
}
