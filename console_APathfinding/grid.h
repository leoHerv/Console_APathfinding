#ifndef __GRID__H__
#define __GRID__H__
	
	#include "pathfinding.h"

	// La taille de la grille de deplacement.
	#define GRID_X 15
	#define GRID_Y GRID_Y_PATH
	// La taille de la grille max (avec les bordures).
	#define GRIDMAX_X GRID_X + 2
	#define GRIDMAX_Y GRID_Y + 2

	// Prototypes
	
	// Boucle de jeu.
	void gameLoop(void);
	// Initialise la grille avec les points A,B et le joueur.
	void initGrid(char grid[][GRIDMAX_Y], int* pt_aX, int* pt_aY, int* pt_bX, int* pt_bY, int* pt_joueurX, int* pt_joueurY);
	// Affiche la grille dans la console.
	void printGrid(char grid[][GRIDMAX_Y]);
	// Affiche les choses que l'on peut faire et demande un char (action).
	void instructionMove(char* action);
	// Donne une instruction en fonction du char en entree.
	void actionGrid(char grid[][GRIDMAX_Y], char action, int* pt_aX, int* pt_aY, int* pt_bX, int* pt_bY, int* pt_joueurX, int* pt_joueurY);
	// Modifie la position du joueur.
	void movePos(int* pt_joueurX, int* pt_joueurY, int x, int y);
	// Change une case de la grille par le char carat.
	void modifGrid(char grid[][GRIDMAX_Y], char caract, int x, int y);

#endif //__GRID__H__