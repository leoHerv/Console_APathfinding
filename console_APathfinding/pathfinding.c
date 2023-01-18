#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pathfinding.h"
#include "list_pathfinding.h"


/*///////////////////////////////////////////////////////////////*/

int calculHCost(int dX, int dY, int fX, int fY)
{
	return 10 * (abs(dX - fX) + abs(dY - fY));
}

/*///////////////////////////////////////////////////////////////*/

int calculGCost(int nX, int nY, node parentNode)
{
	if((nX != parentNode.x && nY == parentNode.y) || (nX == parentNode.x && nY != parentNode.y))
	{
		return parentNode.g + 10;
	}
	else
	{
		return parentNode.g + 14;
	}
}

/*///////////////////////////////////////////////////////////////*/

node initFirstNode(int x, int y, int finX, int finY)
{
	node firstNode;
	firstNode.parent = NULL;
	firstNode.x = x;
	firstNode.y = y;
	firstNode.g = 0;
	firstNode.h = calculHCost(x, y, finX, finY);
	firstNode.f = firstNode.h;
	return firstNode;
}

/*///////////////////////////////////////////////////////////////*/

node InitNeighbourNode(int x, int y, int finX, int finY, node parentNode)
{
	node neighbourNode;
	alloueNode(&(neighbourNode.parent), parentNode);
	neighbourNode.x = x;
	neighbourNode.y = y;
	neighbourNode.g = calculGCost(x, y, parentNode);
	neighbourNode.h = calculHCost(x, y, finX, finY);
	neighbourNode.f = neighbourNode.g + neighbourNode.h;
	return neighbourNode;
}

/*///////////////////////////////////////////////////////////////*/

node findSmallestFCost(List l)
{
	List new_l = copie_List(l);

	if(len_List(new_l) <= 0)
	{
		fprintf(stderr, "Erreur findSmallestFCost: la liste est vide.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		node smallestFCostNode = fst_List(new_l);
	    new_l = rem_fst_List(new_l);
	    node tmpNode;

		while(!(is_empty_List(new_l)))
		{
			tmpNode = fst_List(new_l);
			new_l = rem_fst_List(new_l);

			if(smallestFCostNode.f > tmpNode.f)
			{
				smallestFCostNode = tmpNode;
			}
		}
		return smallestFCostNode;
	}
}

/*///////////////////////////////////////////////////////////////*/

bool is_nodes_equal(node n1, node n2)
{
	return ( (n1.parent == n2.parent) && (n1.x == n2.x) && (n1.y == n2.y) && (n1.g == n2.g) && (n1.h == n2.h) && (n1.f == n2.f) );
}

/*///////////////////////////////////////////////////////////////*/

bool is_posNodes_equal(node n1, node n2)
{
		return ((n1.x == n2.x) && (n1.y == n2.y));
}

/*///////////////////////////////////////////////////////////////*/

bool nodeInListPos(List l, node n)
{	
	List new_l = copie_List(l);

	if(len_List(new_l) == 0)
	{
		return false;
	}
	else if(len_List(new_l) == 1)
	{
		return is_posNodes_equal(fst_List(new_l), n);
	}
	else
	{
		int lenList = new_l->len;
		for(int i = 0; i < lenList; i++)
		{
			node parcoursNode = fst_List(new_l);
			new_l = rem_fst_List(new_l);

			//printf("test number: %d\n", i);
			//printf("comparaison : (x: %d, y: %d, g: %d, h: %d, f: %d)\n", parcoursNode.x, parcoursNode.y, parcoursNode.g, parcoursNode.h, parcoursNode.f);

			if(is_posNodes_equal(parcoursNode, n))
			{
				return true;
			}
			
			//printf("test number: %d\n", i);
		}
		return false;
	}
}

/*///////////////////////////////////////////////////////////////*/

node nodeInListPos_rNode(List l, node n)
{
	List new_l = copie_List(l);
	
	int lenList = new_l->len;
	for(int i = 0; i < lenList; i++)
	{
		node parcoursNode = fst_List(new_l);
		new_l = rem_fst_List(new_l);

		if(is_posNodes_equal(parcoursNode, n))
		{
			return parcoursNode;
		}
	}
	fprintf(stderr, "Erreur nodeInListPos_rNode: la node n'est pas dans la liste.\n");
	exit(EXIT_FAILURE);
}

/*///////////////////////////////////////////////////////////////*/

List removeNodeFormList(node nodeToRemove, List l)
{
	List copie_l = copie_List(l);

	if(is_empty_List(copie_l))
	{
		fprintf(stderr, "Erreur removeNodeFormList: la liste est vide.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		List new_l = empty_List();

		while(!(is_empty_List(copie_l)))
		{
			if(!(is_nodes_equal(fst_List(copie_l), nodeToRemove)) )
			{
				new_l = add_lst_List(new_l, fst_List(copie_l));
			}
			copie_l = rem_fst_List(copie_l);
		}
		return new_l;
	}
}

/*///////////////////////////////////////////////////////////////*/

List findAllNeighbour(char grid[][GRID_Y_PATH + 2], node parentNode, int aX, int aY)
{
	List neighbourList = empty_List();

	for(int x = -1; x <= 1; x++)
	{
		for(int y = -1; y <= 1; y++)
		{
			if(!(x == 0 && y == 0))
			{
				int newX = parentNode.x + x;
				int newY = parentNode.y + y;
				char posChar = grid[newX][newY];
				if(posChar== ' ' || posChar == 'A' || posChar == 'B' || posChar == 'J' || posChar == '.')
				{
					neighbourList = add_fst_List(neighbourList, InitNeighbourNode(newX, newY, aX, aY, parentNode));
				}
			}
		}
	}
	return neighbourList;
}

/*///////////////////////////////////////////////////////////////*/

pNode returnPath(char grid[][GRID_Y_PATH + 2], int dX, int dY, int aX, int aY)
{
	List open = empty_List();
	List closed = empty_List();

	node fstNode = initFirstNode(dX, dY, aX, aY);
	open = add_fst_List(open, fstNode);

	pNode actuel = NULL;

	do
	{
		alloueNode(&actuel, findSmallestFCost(open));

		// printf("parentNode : x: %d, y: %d, g: %d, h: %d, f: %d", actuel->x, actuel->y, actuel->g, actuel->h, actuel->f);
		// if(actuel->parent != NULL)
		// {
		// 	printf(" [parent : x: %d, y: %d, g: %d, h: %d, f: %d]", actuel->parent->x, actuel->parent->y, actuel->parent->g, actuel->parent->h, actuel->parent->f);
		// }
		// printf("\n");

		open = removeNodeFormList(*actuel, open);
		
		closed = add_fst_List(closed, *actuel);

		if(actuel->x == aX && actuel->y == aY)
		{
			return actuel;
		}
		// printf("\nListe closed :\n");
		// print_List(closed);
		// printf("\nListe open :\n");
		// print_List(open);

		List neighbourList = findAllNeighbour(grid, *actuel, aX, aY);

		// printf("\nneighbourList :\n");
		// print_List(neighbourList);

		while(!is_empty_List(neighbourList))
		{
			node neighbour = fst_List(neighbourList);
			
			if(!(nodeInListPos(closed, neighbour)))
			{
				if(!(nodeInListPos(open, neighbour)))
				{
					open = add_lst_List(open, neighbour);
				}
				else
				{
					node neighbourInOpen = nodeInListPos_rNode(open, neighbour);
					if(neighbourInOpen.f > neighbour.f)
					{
						open = removeNodeFormList(neighbourInOpen, open);
						open = add_lst_List(open, neighbour);
					}
				}	
			}
			neighbourList = rem_fst_List(neighbourList);
		}
		
	}while(!is_empty_List(open));

	return NULL;
}

/*///////////////////////////////////////////////////////////////*/

void printPath(char grid[][GRID_Y_PATH + 2], pNode arrive)
{
	if(arrive != NULL)
	{
		pNode newArrive = arrive->parent;

		while(newArrive->parent != NULL)
		{
		    grid[newArrive->x][newArrive->y] = '.';
			newArrive = newArrive->parent;
		}	
	}
	else
	{
		fprintf(stderr, "Erreur printPath: chemin impossible entre A et B.\n");
		exit(EXIT_FAILURE);
	}
}

/*///////////////////////////////////////////////////////////////*/

void clearPath(char grid[][GRID_Y_PATH + 2], pNode arrive)
{
	if(arrive != NULL)
	{
		pNode newArrive = arrive->parent;

		while(newArrive->parent != NULL)
		{
		    grid[newArrive->x][newArrive->y] = ' ';
			newArrive = newArrive->parent;
		}	
	}
	else
	{
		fprintf(stderr, "Erreur clearPath: chemin impossible entre A et B.\n");
		exit(EXIT_FAILURE);
	}
}

/*///////////////////////////////////////////////////////////////*/

void alloueNode(pNode* newNode, node nodeToAlloue)
{
	*newNode = (pNode) malloc(sizeof(node));

	(*newNode)->parent = nodeToAlloue.parent;
	(*newNode)->x = nodeToAlloue.x;
	(*newNode)->y = nodeToAlloue.y;
	(*newNode)->g = nodeToAlloue.g;
	(*newNode)->h = nodeToAlloue.h;
	(*newNode)->f = nodeToAlloue.f;
}