#ifndef __PACHFINDING__H__
#define __PACHFINDING__H__
	
	#include <stdbool.h>
	
	#define GRID_Y_PATH 10

	typedef struct node
	{
		struct node* parent;
		int x;
		int y;
		int g;
		int h;
		int f;
	}node, *pNode;

	#include "list_pathfinding.h"

	// Prototypes :

	// fait le calcul pour le H cost.
	int calculHCost(int dX, int dY, int fX, int fY);
	// fait le calcul pour le G cost;
	int calculGCost(int nX, int nY, node parentNode);
	// crée la premiere node.
	node initFirstNode(int x, int y, int finX, int finY);
	// crée une node voisine;
	node InitNeighbourNode(int x, int y, int finX, int finY, node parentNode);
	// trouve la node de la liste avec le plus petit F cost;
	node findSmallestFCost(List l);
	// regarde si deux nodes sont idendique.
	bool is_nodes_equal(node n1, node n2);
	// regarde si la position de deux nodes sont egal.
	bool is_posNodes_equal(node n1, node n2);
	// regarde si il y a une node avec la même position dans la liste
	bool nodeInListPos(List l, node n);
	// regarde si il y a une node avec la même position dans la liste et retourne la node.
	node nodeInListPos_rNode(List l, node n);
	// enleve une node d'une liste de node.
	List removeNodeFormList(node nodeToRemove, List l);
	// trouve tout les voisins de la node parent et redonne une liste des voisins.
	List findAllNeighbour(char grid[][GRID_Y_PATH + 2], node parentNode, int aX, int aY);
	// retour le chemin de l'arrivé vers le depart.
	pNode returnPath(char grid[][GRID_Y_PATH + 2], int dX, int dY, int aX, int aY); //x et y de arrivé et depart (d et a)
	// affiche le chemin sur la grille
	void printPath(char grid[][GRID_Y_PATH + 2], pNode arrive);
	// efface le chemin sur la grille.
	void clearPath(char grid[][GRID_Y_PATH + 2], pNode arrive);
	// alloue de la memoire pour une node.
	void alloueNode(pNode* newNode, node nodeToAlloue);

#endif // __PACHFINDING__H__