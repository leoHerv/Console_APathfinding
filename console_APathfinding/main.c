#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

int main(void)
{	
	gameLoop();
	return 0;
}

/*
 Algo pour le Pathfinding : (A* Pathfinding)

G = +10 sur les cotes et +14 sur les diagonals
H = ABS(DX - AX) + ABS(DY - AY) , (ABS = valeur absolu)
F = H + G


OPEN les cases a evaluer
CLOSED les case qui sont deja evaluer

ajouter la premiere case à la liste OPEN

boucle
	actuel = la case de OPEN avec le plus petit F
	enleve actuel de OPEN
	ajoute actuel a CLOSED

	if actuel = arrivé
		break;

	pour tout les voisins d'actuel
		if voisins est un mur OU que voisins est dans CLOSED
			faire un autre voisins

		if le nouveau chemin vers le voisin est plus rapide (donc dans OPEN)
			OU le voisin n'est pas dans OPEN

			faire le F du voisin (avec le nouveau G)
			mettre le parent du voisin au actuel

			if le voisin n'est pas dans OPEN
				ajouter voisin dans OPEN 
*/





