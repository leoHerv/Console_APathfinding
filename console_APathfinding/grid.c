#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grid.h"
#include "pathfinding.h"

void gameLoop(void)
{
	int aX = 3;
	int aY = 3;
	int bX = 8;
	int bY = 10;

	int joueurX = 7;
	int joueurY = 7;

	char gameGrid[GRIDMAX_X][GRIDMAX_Y];
	int* pt_aX = &aX;
	int* pt_aY = &aY;
	int* pt_bX = &bX;
	int* pt_bY = &bY;

	int* pt_joueurX = &joueurX;
	int* pt_joueurY = &joueurY;

	char action = ' ';

	initGrid(gameGrid, pt_aX, pt_aY, pt_bX, pt_bY, pt_joueurX, pt_joueurY);
	do
	{
		printGrid(gameGrid);
		instructionMove(&action);
		actionGrid(gameGrid, action, pt_aX, pt_aY, pt_bX, pt_bY, pt_joueurX, pt_joueurY);
		system("cls");
	}while(action != 'p');
	
}

/*///////////////////////////////////////////////////////////////////////////////*/

void initGrid(char grid[][GRIDMAX_Y], int* pt_aX, int* pt_aY, int* pt_bX, int* pt_bY, int* pt_joueurX, int* pt_joueurY)
{
	for(int y = 0; y < GRIDMAX_Y; y++)
	{
		for(int x = 0; x < GRIDMAX_X; x++)
		{
			if( y+1 == GRIDMAX_Y || y == 0)
			{
				grid[x][y] = '-';
			}
			else if(x+1 == GRIDMAX_X || x == 0)
			{
				grid[x][y] = '|';
			}
			else
			{
				grid[x][y] = ' ';
			}
		}
	}
	grid[*pt_aX][*pt_aY] = 'A';
	grid[*pt_bX][*pt_bY] = 'B';
	grid[*pt_joueurX][*pt_joueurY] = 'J';

}

/*///////////////////////////////////////////////////////////////////////////////*/

void printGrid(char grid[][GRIDMAX_Y])
{
	for(int y = GRIDMAX_Y-1; y >= 0; y--)
	{
		for(int x = 0; x < GRIDMAX_X; x++)
		{
			printf("%c", grid[x][y]);
		}
		printf("\n");
	}
}

/*///////////////////////////////////////////////////////////////////////////////*/

void instructionMove(char* action)
{
	printf("\'Deplacement\' = z : haut, s : bas, d : droite, q : gauche\n");
	printf("\'Pose d'un bloc\' = e : pose, r : retier bloc\n");
	printf("t : Trouver le chemin de A vers B, c :Effacer le chemin de A vers B\n");
	printf("Quitter : p\n");
	scanf("%c", action);
}

/*///////////////////////////////////////////////////////////////////////////////*/

void actionGrid(char grid[][GRIDMAX_Y], char action, int* pt_aX, int* pt_aY, int* pt_bX, int* pt_bY, int* pt_joueurX, int* pt_joueurY)
{
	if(action == 'z' || action == 's' || action == 'd' || action == 'q' || action == 'e' || action == 'r')
	{
		char elementGrid = grid[*pt_joueurX][*pt_joueurY];

		if(elementGrid == 'J' || elementGrid == ' ')
		{
			modifGrid(grid, ' ', *pt_joueurX, *pt_joueurY);
		}
		if(action == 'e')
		{
			modifGrid(grid, 'O', *pt_joueurX, *pt_joueurY);
		}
		else
		{
			if(action == 'z' && *pt_joueurY < GRID_Y)
			{
				movePos(pt_joueurX, pt_joueurY, 0, 1);
			}
			if(action == 's' && *pt_joueurY > 1)
			{
				movePos(pt_joueurX, pt_joueurY, 0, -1);
			}
			if(action == 'd' && *pt_joueurX < GRID_X)
			{
				movePos(pt_joueurX, pt_joueurY, 1, 0);
			}
			if(action == 'q' && *pt_joueurX > 1)
			{
				movePos(pt_joueurX, pt_joueurY, -1, 0);
			}
			if(action == 'r')
			{
				modifGrid(grid, ' ', *pt_joueurX, *pt_joueurY);
			}
			// Nouvelle pos pour le joueur.
			elementGrid = grid[*pt_joueurX][*pt_joueurY];
			if(elementGrid == ' ')
			{
				modifGrid(grid, 'J', *pt_joueurX, *pt_joueurY);
			}
		}
	}
	if(action == 't')
	{
		pNode path = returnPath(grid, *pt_aX, *pt_aY, *pt_bX, *pt_bY);
		printPath(grid, path);
	}
	if(action == 'c')
	{
		pNode path = returnPath(grid, *pt_aX, *pt_aY, *pt_bX, *pt_bY);
		clearPath(grid, path);
	}
}

/*///////////////////////////////////////////////////////////////////////////////*/

void movePos(int* pt_joueurX, int* pt_joueurY, int x, int y)
{
	*pt_joueurX += x;
	*pt_joueurY += y;
}

/*///////////////////////////////////////////////////////////////////////////////*/

void modifGrid(char grid[][GRIDMAX_Y], char caract, int x, int y)
{
	grid[x][y] = caract;
}