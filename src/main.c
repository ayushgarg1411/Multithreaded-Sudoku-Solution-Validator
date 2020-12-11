/**
 * @file: main.c
 * @author: Ayush Garg, 656665809, F20N01, CSCI 360, VIU
 * @version: 1.0.0
 * @modified: Dec 10, 2020
 *
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "sudoku_checker.h"


int puzzle[PUZZLE_SIZE+1][PUZZLE_SIZE+1];
int status_map[NUMBER_OF_THREADS];

parameters* worker_params[NUMBER_OF_THREADS];
pthread_t workers[NUMBER_OF_THREADS];




int main(int argc, char** argv)
{

	FILE* fp;
	if(argc < 2)
	{
		printf("Usage: sudoku_checker <input_file_name>");
		return 0;
	}
	fp = fopen(argv[1], "r");
	read_from_file(fp);
	fclose(fp);
	int i, j, t_num=0;
	int t_index = 0;
	show_puzzle();

	for (i = 0; i < PUZZLE_SIZE; i++)
	{
		for (j = 0; j < PUZZLE_SIZE; j++)
		{
			if (j == 0)
			{
					worker_params[t_num] = (parameters *) malloc(sizeof(parameters));
					worker_params[t_num]->thread_no= t_num;
					worker_params[t_num] ->x = i;
					worker_params[t_num] ->y = j;
					pthread_create(&workers[t_index], NULL, row_worker, 	worker_params[t_num] );
					t_index++;
					t_num++;
				}

			if (i == 0)
			{
				worker_params[t_num] = (parameters *) malloc(sizeof(parameters));
				worker_params[t_num]->thread_no = t_num;
				worker_params[t_num]->x= i;
				worker_params[t_num]->y = j;
				pthread_create(&workers[t_index], NULL, col_worker, 	worker_params[t_num] );
				t_index++;
				t_num++;
			}

			if (i%3 == 0 && j%3 == 0)
			{
				worker_params[t_num]  = (parameters *) malloc(sizeof(parameters));
				worker_params[t_num]->thread_no= t_num;
				worker_params[t_num] ->x = i;
				worker_params[t_num] ->y = j;
				pthread_create(&workers[t_index], NULL, subgrid_worker, 	worker_params[t_num] );
				t_index++;
				t_num++;
			}
		}
	}

	for (i = 0; i < NUMBER_OF_THREADS; i++)
	{
		pthread_join(workers[i], NULL);
	}

	int status = check_status_map();
	printf("\n*******************************************************************************************\n");
	if(status)
	{
		printf("............................. Valid Solution ..............................................");
	}
	else
	{
		printf("............................. Invalid Solution ..............................................");
	}
	printf("\n*******************************************************************************************\n");

	return 0;

}
