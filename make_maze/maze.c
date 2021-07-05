#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void makeMaze(int **eller, char **maze,int* count, int N, int M)
{
	int i, j,k,l,tmp, set = N ;
	int inc = ((N < M) ? N : M) / 2;

	for (i = 0; i < N*M + 1; i++)
	{
		count[i] = 0;
	}

	for (i = 0; i < 2 * M + 1; i++)
	{
		for (j = 0; j < 2 * N + 1; j++)
		{
			if (i % 2 == 0 && j % 2 == 0)
				maze[i][j] = '+';
			else if (i % 2 == 0 && j % 2 == 1)
				maze[i][j] = '-';
			else if (i % 2 == 1 && j % 2 == 0)
				maze[i][j] = '|';
			else
				maze[i][j] = ' ';
		}
	}

	if (M == 1)
	{
		if (N == 1)
			return;
		else
		{
			for (i = 1; i < N; i++)
			{
				maze[1][i * 2] = ' ';
			}
		}
	}

	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			eller[i][j] = 0;
		}
	}

	for (i = 0; i < N; i++)
	{
		eller[0][i] = i + 1;
	}

	for (i = 0; i < M; i++)
	{
		if (i == 0)
		{
			for (j = 0; j < N - 1; j++)
			{
				if (eller[0][j] != eller[0][j + 1] && rand() % 2)
				{
					eller[0][j + 1] = eller[0][j];
					maze[1][2 * j + 2] = ' ';
				}
			}
			for (j = 0; j < N; j++)
			{
				count[eller[0][j]]++;
			}
			continue;
		}

		for (j = 0; j < N; j++)
		{
			if (rand() % 2)
			{
				eller[i][j] = eller[i - 1][j];
				maze[2 * i][2 * j + 1] = ' ';
			}
			else
			{
				eller[i][j] = 0;
				count[eller[i - 1][j]]--;
				if (count[eller[i - 1][j]] == 0)	
				{
					eller[i][j] = eller[i - 1][j];
					maze[2 * i][2 * j + 1] = ' ';
				}
			}
		}

		for (j = 0; j < N; j++)
		{
			if (eller[i][j] == 0)
			{
				eller[i][j] = ++set;
			}
		}
		
		
		for (j = 0; j < N - 1; j++)
		{
			if (eller[i][j] != eller[i][j + 1] && rand() % 2)
			{
				tmp = eller[i][j + 1];
				eller[i][j + 1] = eller[i][j];
				for (k = 0; k < M; k++)
				{
					for ( l = 0; l < N; l++)
					{
						if (eller[k][l] == tmp)
							eller[k][l] = eller[i][j];
					}
				}
				maze[2 * i + 1][2 * j + 2] = ' ';
			}
		}
		

		for (j = 0; j < N*M + 1; j++)
		{
			count[j] = 0;
		}
		
		for (j = 0; j < N; j++)
		{
			count[eller[i][j]]++;
		}
	}
	
	for (i = 0; i < N - 1; i++)
	{
		if (eller[M-1][i] != eller[M-1][i + 1])
		{
			tmp = eller[M-1][i + 1];
			eller[M-1][i + 1] = eller[M-1][i];
			for (j = 0; j < M; j++)
			{
				for (k = 0; k < N; k++)
				{
					if (eller[j][k] == tmp)
					{
						eller[j][k] = eller[M-1][i];
					}
				}
			}
			maze[2 * (M-1) + 1][2 * i + 2] = ' ';
		}
	}
	
	while (1)
	{
		if (inc == 0)
			break;
		for (i = 0; i < M; i++)
		{
			if (inc == 0)
				break;
			for (j = 0; j < N-1; j++)
			{
				if (inc == 0)
					break;
				if (maze[2 * i + 1][2 * (j + 1)] =='|' && rand() % 2)
				{
					maze[2 * i + 1][2 * (j + 1)] = ' ';
					inc--;
				}
				if (i < M - 1)
				{
					if (maze[2 * (i + 1)][2 * j + 1] == '-' && rand() % 2)
					{
						maze[2 * (i + 1)][2 * j + 1] = ' ';
						inc--;
					}
				}
			}
		}
	}

	/*
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			printf("%d ", eller[i][j]);
		}
		printf("\n");
	}
	for (i = 0; i < 2 * M+ 1; i++)
	{
		for (j = 0; j < 2 * N + 1; j++)
			printf("%c", maze[i][j]);
		printf("\n");
	}
	*/
	
	
}

int main()
{
	FILE* fp;
	fp = fopen("maze.maz", "w");
	srand(time(NULL));
	int N,M,i,j;
	int** eller = NULL;
	int* count = NULL;
	char** maze = NULL;
	printf("Make N*M size maze, input N : ");
	scanf("%d", &N);
	printf("input M : ");
	scanf("%d", &M);
	

	eller = (int**)malloc(sizeof(int*)*M);
	maze = (char**)malloc(sizeof(char*)*(2 * M + 1));
	count = (int*)malloc(sizeof(int)*(N*M + 1));

	for (i = 0; i < M; i++)
		eller[i] = (int*)malloc(sizeof(int)*N);

	
	for (i = 0; i < 2 * M + 1; i++)
		maze[i] = (char*)malloc(sizeof(char)*(2 * N + 1));

	makeMaze(eller, maze,count, N, M);

	for (i = 0; i < 2 * M + 1; i++)
	{
		for (j = 0; j < 2 * N + 1; j++)
		{
			fprintf(fp, "%c", maze[i][j]);
		}
		fprintf(fp,"\n");
	}
	for (i = 0; i < M; i++)
		free(eller[i]);
	for (i = 0; i < 2 * M + 1; i++)
		free(maze[i]);
	
	free(eller);
	free(maze);
	free(count);
	fclose(fp);

	return 0;
}